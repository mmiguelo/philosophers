/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:36:38 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/06/01 22:36:38 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		return (error_msg("Error with malloc\n"), NULL);
	return (ret);
}

static int	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return (0);
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode
			|| DESTROY == opcode))
		return (error_msg("The value specified by mutex is invalid.\n"), -1);
	else if (EINVAL == status && INIT == opcode)
		return (error_msg("The value specified by attr is invalid.\n"), -1);
	else if (EDEADLK == status)
		return (error_msg("A deadlock would occur if thread blocked waiting for\
			 mutex.\n"), -1);
	else if (EPERM == status)
		return (error_msg("The current thread does not hold a lock mutex.\n"), -1);
	else if (ENOMEM == status)
		return (error_msg("The process cannot allocate enough memory to create\
			 another mutex.\n"), -1);
	else if (EBUSY == status)
		return (error_msg("Mutex is locked.\n"), -1);
	return (0);
}

int	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		return (error_msg("Wrong opcode for mutex handle.\n"), -1);
	return (0);
}

static int	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return (0);
	if (EAGAIN == status)
		return (error_msg("No resources to create another thread.\n"), -1);
	else if (EPERM == status)
		return (error_msg("The caller does not have appropriate permission.\n"), -1);
	else if (EINVAL == status && CREATE == opcode)
		return (error_msg("The value specified by attr is invalid.\n"), -1);
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		return (error_msg("The value specified by thread is not joinable.\n"), -1);
	else if (ESRCH == status)
		return (error_msg("No thread could be found corresponding to that\
			specified by the given thread ID, thread.\n"), -1);
	else if (EDEADLK == status)
		return (error_msg("A deadlock was detected or the value of\
			thread specifies the calling thread.\n"), -1);
	return (0);
}

int	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		return (error_msg("Wrong opcode for thread handle: \
			use: CREATE, JOIN, DETACH.\n"), -1);
	return (0);
}
