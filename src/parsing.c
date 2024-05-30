/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:38:14 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/30 18:48:32 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

const char	*philo_valid_input(const char *str_arg)
{
	while (*str_arg)
	{
		if (*str_arg < '0' || *str_arg > '9')
			error("Invalid argument. Only positives numbers are allowed.");
		str_arg++;
	}
	return (str_arg);
}

int	valid_nbr(long nbr)
{
	if (nbr < 0)
		error("Negative numbers are not allowed.");
	return (0);
}

void	parse_args(t_table *table, char **argv)
{
	table->philo_nbr = philo_atol(argv[1]);
	table->time_to_die = philo_atol(argv[2]);
	table->time_to_eat = philo_atol(argv[3]);
	table->time_to_sleep = philo_atol(argv[4]);
	if (argv[5])
		table->limit_meals = philo_atol(argv[5]);
	else
		table->limit_meals = -1;
}
