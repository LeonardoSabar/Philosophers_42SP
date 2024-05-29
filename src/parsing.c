/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:38:14 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/29 13:25:53 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

const char	*philo_valid_input(const char *str_arg)
{
	while (*str_arg)
	{
		if (*str_arg < '0' || *str_arg > '9')
			error(" Invalid argument. Only numbers are allowed.");
		str_arg++;
	}
	return (str_arg);
}

int	negative_nbr(long nbr)
{
	if (nbr < 0)
		error("Negative numbers are not allowed.");
	return (0);
}

void	parse_args(t_table *table, char **av)
{
	table->philo_nbr = philo_atol(av[1]);
	table->time_to_die = philo_atol(av[2]);
	table->time_to_eat = philo_atol(av[3]);
	table->time_to_sleep = philo_atol(av[4]);
	if (av[5])
		table->limit_meals = philo_atol(av[5]);
	else
		table->limit_meals = -1;
}
