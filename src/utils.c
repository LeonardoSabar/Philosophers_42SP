/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:21:15 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/15 16:42:25 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error(char *msg)
{
	printf(RED"Error: %s\n"RST, msg);
	exit(EXIT_FAILURE);
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error("Malloc failed.");
	return (ret);
}

long	philo_atol(const char *str_arg)
{
	long		nbr;
	int			sign;
	const char	*str;

	str = str_arg;
	nbr = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	nbr = nbr * sign;
	return (nbr);
}

long	arg_convert(const char *str_arg)
{
	long		nbr;

	philo_valid_input(str_arg);
	nbr = philo_atol(str_arg);
	if (nbr > INT_MAX)
		error("Invalid argument. Number is too big.");
	return (nbr);
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = &table->philos[i];
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
