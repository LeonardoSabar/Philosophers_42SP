/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:10:23 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/03 11:10:56 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error("The value specified by mutex is invalid.");
	else if (status == EINVAL && opcode == INIT)
		error("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		error("A deadlock would occur if the thread \
			blocked waiting for the mutex.");
	else if (status == EPERM)
		error("The current thread does not hold a \
			lock on the mutex.");
	else if (status == ENOMEM)
		error("The process cannot allocate enough \
			memory to create another mutex.");
	else if (status == EBUSY)
		error("Mutex is locked.");
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
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error("Invalid mutex opcode.");
}
