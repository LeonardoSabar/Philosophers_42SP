/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:33:35 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/03 10:45:28 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_test_args(t_table *table)
{
	printf("philo_nbr: %ld\n", table->philo_nbr);
	printf("time_to_die: %ld\n", table->time_to_die);
	printf("time_to_eat: %ld\n", table->time_to_eat);
	printf("time_to_sleep: %ld\n", table->time_to_sleep);
	printf("limit_meals: %ld\n", table->limit_meals);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_args(&table, argv);

		if (table.philo_nbr <=  200)
		{
			init_table(&table);

			// start_dinner(&table);

			// clean(&table); // Quando todos os fil ósofos terminarem de comer ou um morrer, "limpar a mesa"
		}
		print_test_args(&table);
	}
	else
		error("Invalid number of arguments");
}
