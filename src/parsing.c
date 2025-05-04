/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:25:54 by marvin            #+#    #+#             */
/*   Updated: 2025/05/04 17:25:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	parse_last_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '[')
		return (FALSE);
	while (ft_isdigit(arg[i]))
		i++;
	if (arg[i] != ']')
		return (FALSE);
	return (arg[i + 1] == '\0');
}

void	parse_opt_args(char **argv)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (!parse_args(&argv[i]))
		{
			printf("Invalid numeric arguments: %s\n", argv[i]);
			return ;
		}
		i++;
	}
	if (!parse_last_arg(argv[i]))
		printf("Invalid optional argument format: %s\n", argv[i]);
}
