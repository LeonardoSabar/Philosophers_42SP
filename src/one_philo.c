/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:39:47 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/15 19:58:21 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*lone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads_created(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, \
			get_time(MILLISECOND));
	increase_long(&philo->table->table_mutex, \
			&philo->table->threads_running_nbr);
	write_action(TAKE_RIGHT_FORK, philo);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}
