/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:39:47 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/05 16:53:17 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	write_status_debug(t_philo *philo, t_status status, long elapsed)
// {
// 	if (TAKE_RIGHT_FORK == status && !simulation_finished(philo->table))
// 		printf(G"%-6ld"RST" %d has taken a right fork\n", elapsed, philo->id);
// 	else if (TAKE_LEFT_FORK == status && !simulation_finished(philo->table))
// 		printf(G"%-6ld"RST" %d has taken a left fork\n", elapsed, philo->id);
// 	else if (EATING == status)
// 		printf(B"%-6ld"RST" %d is eating\n", elapsed, philo->id);
// 	else if (SLEEPING == status)
// 		printf(Y"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
// 	else if (THINKING == status)
// 		printf(C"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
// 	else if (DIED == status)
// 		printf(RED"%-6ld"RST" %d died\n", elapsed, philo->id);
// }

void	write_action(t_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND);
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_RIGHT_FORK == status || TAKE_LEFT_FORK == status)
			&& !simulation_finished(philo->table))
			printf(G"%-6ld"RST" %d has taken a fork\n",elapsed, philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf(B"%-6ld"RST" %d is eating\n", elapsed, philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf(Y"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && !simulation_finished(philo->table))
			printf(C"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf(RED"%-6ld"RST" %d died\n", elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
