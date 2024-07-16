/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:11:15 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/15 20:01:28 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILLISECOND) - get_long(&philo->philo_mutex, \
			&philo->last_meal_time);
	time_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_simulation(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, \
			&table->threads_running_nbr, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_action(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}
