/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:39:47 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/13 17:43:51 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Retirar funcao write_status_debug e retirar macro DEBUG do arquivo philosophers.h

void	write_status_debug(t_philo *philo, t_status status, long elapsed)
{
	if (TAKE_RIGHT_FORK == status && !simulation_finished(philo->table))
		printf(G"%6ld"RST" %d has taken a first fork " "\t\tnº"B"[ %d ]\n"RST, elapsed, philo->id, philo->first_fork->fork_id);
	else if (TAKE_LEFT_FORK == status && !simulation_finished(philo->table))
		printf(G"%6ld"RST" %d has taken a second fork " "\t\tnº"B"[ %d ]\n"RST, elapsed, philo->id, philo->second_fork->fork_id);
	else if (EATING == status)
		printf(B"%6ld"RST" %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == status)
		printf(Y"%6ld"RST" %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status)
		printf(C"%6ld"RST" %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED"%6ld"RST" %d died\n", elapsed, philo->id);
}
void	thinking(t_philo *philo)
{
	bool	debug;
	debug = DEBUG;

	write_action(THINKING, philo, debug);
}

void	eat(t_philo *philo)
{
	bool	debug;
	debug = DEBUG;

	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_action(TAKE_RIGHT_FORK, philo, debug);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_action(TAKE_LEFT_FORK, philo, debug);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECOND));
	philo->meals_count++;
	write_action(EATING, philo, debug);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->limit_meals > 0 && philo->meals_count == philo->table->limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

// void	thinking(t_philo *philo, bool debug)
// {
// 	write_action(THINKING, philo, debug);
// 	precise_usleep(philo->table->time_to_think, philo->table);
// }

void	write_action(t_status status, t_philo *philo, bool debug) // Retirar debug
{
	long	elapsed;

	elapsed = get_time(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(philo, status, elapsed);     //retirar ese "if"
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
