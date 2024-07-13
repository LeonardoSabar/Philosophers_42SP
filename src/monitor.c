/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:11:15 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/13 19:13:47 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_simulation(void *data)
{
	int		i;
	t_table	*table;
	bool	debug;

	debug = DEBUG;
	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, &table->threads_running_nbr, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr)
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_action(DIED, table->philos + i, debug);
				break ;
			}
		}
	}
}
