/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:36:32 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/06/01 22:36:32 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	ft_isspace(char c)
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
		return (error_msg("Invalid input: negative number not allowed\n"), NULL);
	if (!ft_isdigit(*str))
		return (error_msg("Invalid input: not a number\n"), NULL);
	number = str;
	while (ft_isdigit(*str++))
		++len;
	if (len > 10)
		return (error_msg("Invalid input: number too large\n"), NULL);
	return (number);
}

static long	ft_atol(const char *str)
{
	long	nbr;

	nbr = 0;
	//str = valid_input(str);
	while (ft_isdigit(*str))
		nbr = (nbr * 10) + (*str++ - 48);
	if (nbr > INT_MAX)
		return (error_msg("Invalid input: number too large\n"), -1);
	return (nbr);
}

int	parse_input(t_table *table, char **av)
{
	static int i;
	while (++i <= 4)
		if (valid_input(av[i]))
			continue;
		else
			return (-1);
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		return (error_msg("Invalid input: timestamps too small\n"), -1);
	if (av[5] && valid_input(av[5]))
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
	return (0);
}
