/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:42:23 by marvin            #+#    #+#             */
/*   Updated: 2025/05/04 15:42:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc == 5)
	{
		if (!parse_args(argv))
			printf("Invalid numeric arguments.\n");
	}
	else if (argc == 6)
		parse_opt_args(argv);
	else
		error_msg("Wrong input:\n"
			G"Correct is ./philo 5 800 200 200 [7] for example"RST);
	return (0);
}
