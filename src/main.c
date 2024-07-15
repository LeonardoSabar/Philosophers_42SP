/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:33:35 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/11 12:21:40 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	print_test_args(t_table *table)   //Retirar essa função
// {
	// printf("philo_nbr: %ld\n", table->philo_nbr);
	// printf("time_to_die: %ld\n", table->time_to_die);
	// printf("time_to_eat: %ld\n", table->time_to_eat);
	// printf("time_to_sleep: %ld\n", table->time_to_sleep);
	// printf("limit_meals: %ld\n", table->limit_meals);
// }

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_args(&table, argv);

		if (table.philo_nbr <=  200)
		{
			init_table(&table);
			start_dinner(&table);
			clean(&table);
		}
		// print_test_args(&table);
	}
	else
		error("Invalid number of arguments");
}
