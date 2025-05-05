/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:00:19 by marvin            #+#    #+#             */
/*   Updated: 2025/05/05 15:00:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILISECOND) - philo->table->start_simulation;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (philo->full)
		return ;
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf(W"%-6ld"C" %d is eating\n"RST, elapsed, philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf(RED"%-6ld %d died\n"RST, elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
