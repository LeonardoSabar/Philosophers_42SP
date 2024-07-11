/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:54:31 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/11 12:25:28 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if ((philo->id % 2) == 0)
	{
		philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
		philo->second_fork = &forks[philo_position];
	}
	else
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;  // verificar esta variavel
		philo->id = i + 1;
		philo->full = false;
		philo->meals_count = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
	}
}

void	init_table(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->all_threads_created = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->write_mutex, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (++i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads_created(philo->table);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		thinking(philo);
		// sleeping(philo);
	}
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int		i;

	i = -1;
	if (table->limit_meals == 0)
		return ;
	// else if (table->philo_nbr == 1) // fazer funcao para lidar com este caso!!!
	// {
	// 	usleep(table->time_to_die);
	// 	printf("%ld %d died\n", get_time() - table->start_simulation, 1);
	// 	return ;

	// }
	else
	{
		while (++i < table->philo_nbr)
		{
			safe_thread_handle(&table->philos[i].thread_id, \
				&dinner_simulation, &table->philos[i], CREATE);
		}
	}
	table->start_simulation = get_time(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_created, true);
	i = -1;
	while (++i < table->philo_nbr)
	{
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	}
}
