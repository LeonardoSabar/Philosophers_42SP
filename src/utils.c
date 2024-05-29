/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:21:15 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/29 13:25:33 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error(char *msg)
{
	printf(RED"Error: %s\n"RST, msg);
	exit(EXIT_FAILURE);
}

long	philo_atol(const char *str_arg)
{
	long	nbr;
	int		sign;
	const char	*str;

	str = philo_valid_input(str_arg);
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
	negative_nbr(nbr);
	return (nbr);
}
