/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:33:35 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/15 19:59:49 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_args(&table, argv);
		if ((table.philo_nbr >= 1) && (table.philo_nbr <= 200))
		{
			init_table(&table);
			start_dinner(&table);
			clean(&table);
		}
	}
	else
		error("Invalid number of arguments");
}
