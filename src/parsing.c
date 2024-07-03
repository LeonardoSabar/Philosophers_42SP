/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:38:14 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/03 09:17:18 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	parse_args(t_table *table, char **argv)
{
	table->philo_nbr = arg_convert(argv[1]);
	table->time_to_die = arg_convert(argv[2]) * 1e3;
	table->time_to_eat = arg_convert(argv[3]) * 1e3;
	table->time_to_sleep = arg_convert(argv[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error("Invalid argument. The minimum value is 60ms.");
	if (argv[5])
		table->limit_meals = arg_convert(argv[5]);
	else
		table->limit_meals = -1;
}
