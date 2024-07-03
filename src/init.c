/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:54:31 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/03 11:53:08 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->left_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->right_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &forks[philo_position];
		philo->left_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_count = 0;
		philo->table = table;
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
	wait_all_threads();
}

void	star_dinner(t_table *table)
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
}
