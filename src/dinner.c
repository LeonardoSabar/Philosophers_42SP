/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:39:47 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/15 16:38:21 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads_created(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, \
		get_time(MILLISECOND));
	increase_long(&philo->table->table_mutex, \
		&philo->table->threads_running_nbr);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		sleeping(philo);
		thinking(philo, false);
	}
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int		i;

	i = -1;
	if (table->limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		safe_thread_handle(&table->philos[0].thread_id, \
			lone_philo, &table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
		{
			safe_thread_handle(&table->philos[i].thread_id, \
				dinner_simulation, &table->philos[i], CREATE);
		}
	}
	safe_thread_handle(&table->monitor, monitor_simulation, table, CREATE);
	table->start_simulation = get_time(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_created, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
