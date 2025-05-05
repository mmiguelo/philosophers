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

static inline bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_msg("Invalid input: negative number not allowed\n");
	if (!ft_isdigit(*str))
		error_msg("Invalid input: not a number\n");
	number = str;
	while (ft_isdigit(*str++))
		++len;
	if (len == 10)
		error_msg("Invalid input: number too large\n");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	nbr;

	nbr = 0;
	str = valid_input(str);
	while (ft_isdigit(*str))
		nbr = (nbr * 10) + (*str++ - '0');
	if (nbr > INT_MAX)
		error_msg("Invalid input: number too large\n");
	return (nbr);
}

void	parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_msg("Invalid input: timestamps too small\n");
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
}
