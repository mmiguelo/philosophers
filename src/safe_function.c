/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:13:12 by marvin            #+#    #+#             */
/*   Updated: 2025/05/04 22:13:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error_msg("Error with malloc\n");
	return (ret);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode
			|| DESTROY == opcode))
		error_msg("The value specified by mutex is invalid.\n");
	else if (EINVAL == status && INIT == opcode)
		error_msg("The value specified by attr is invalid.\n");
	else if (EDEADLK == status)
		error_msg("A deadlock would occur if thread blocked waiting for\
			 mutex.\n");
	else if (EPERM == status)
		error_msg("The current thread does not hold a lock mutex.\n");
	else if (ENOMEM == status)
		error_msg("The process cannot allocate enough memory to create\
			 another mutex.\n");
	else if (EBUSY == status)
		error_msg("Mutex is locked.\n");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_attr_destroy(mutex), opcode);
	else
		error_msg("Wrong opcode for mutex handle");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EAGAIN == status)
		error_msg("No resources to create another thread.\n");
	else if (EPERM == status)
		error_msg("The caller does not have appropriate permission.\n");
	else if (EINVAL == status && CREATE == opcode)
		error_msg("The value specified by attr is invalid.\n");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_msg("The value specified by thread is not joinable.\n");
	else if (ESRCH == status)
		error_msg("No thread could be found corresponding to that\
			specified by the given thread ID, thread.\n");
	else if (EDEADLK == status)
		error_msg("A deadlock was detected or the value of\
			thread specifies the calling thread.\n");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_msg("Wrong opcode for thread handle: \
			use: CREATE, JOIN, DETACH.\n");
}
