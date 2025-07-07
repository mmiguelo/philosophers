/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:36:28 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/06/01 22:36:28 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if (parse_input(&table, av) == -1)
			return(-1);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
		return (error_msg("Wrong input:\n"
			G"Correct is ./philo 5 800 200 200 [7] for example"RST), -1);
	return (0);
}
