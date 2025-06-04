/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:03:04 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/06/04 13:04:52 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_dinner(void *data)
{
	t_table	*table;
	
	table = (t_table *)data;
	while (!all_threads_running())
	return (NULL);
}