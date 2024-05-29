/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:33:35 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/29 13:32:35 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_args(&table, argv);

		// init_table(&table);

		// start_dinner(&table);

		// clean(&table); // Quando todos os filósofos terminarem de comer ou um morrer, "limpar a mesa"

	}
	else
		error("Invalid number of arguments");
}
