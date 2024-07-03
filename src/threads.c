/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:05:00 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/03 11:09:49 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error("No resources to create another thread.\n");
	else if (EPERM == status)
		error("The caller does note have appropriate permission.\n");
	else if (status == EINVAL && opcode == CREATE)
		error("The value specified by attr is invalid.\n");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error("The value specified by thread not joinable.\n");
	else if (status == ESRCH)
		error("No thread could be found corresponding \
			to that specified by the given thread ID.\n");
	else if (status == EDEADLK)
		error("A deadlock was detected or the value \
			of thread specifies the calling thread.\n");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), \
	void *data, t_opcode e_opcode)
{
	if (CREATE == e_opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), \
			e_opcode);
	else if (JOIN == e_opcode)
		handle_thread_error(pthread_join(*thread, NULL), e_opcode);
	else if (DETACH == e_opcode)
		handle_thread_error(pthread_detach(*thread), e_opcode);
	else
		error("Wrong opcode for thread handle: \
				use <CREATE>, <JOIN> or <DETACH>.");
}
