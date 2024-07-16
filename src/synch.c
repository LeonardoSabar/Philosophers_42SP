/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:55:42 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/15 20:01:01 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_all_threads_created(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_created))
		;
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}

bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

long	get_time(t_time_code time_code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error("Gettimeofday failed.");
	if (time_code == SECOND)
		return (time.tv_sec + (time.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((time.tv_usec / 1e3) + (time.tv_sec * 1e3));
	else if (time_code == MICROSECOND)
		return (time.tv_usec + (time.tv_sec * 1e6));
	else
		error("Invalid input to get_time.");
	return (1337);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
			while (get_time(MICROSECOND) - start < usec)
				;
	}
}
