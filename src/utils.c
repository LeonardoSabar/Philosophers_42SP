/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:21:15 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/01 17:58:20 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error(char *msg)
{
	printf(RED"Error: %s\n"RST, msg);
	exit(EXIT_FAILURE);
}

void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error("The value specified by mutex is invalid.");
	else if (status == EINVAL && opcode == INIT)
		error("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		error("A deadlock would occur if the thread blocked waiting for the mutex.");
	else if (status == EPERM)
		error("The current thread does not hold a lock on the mutex.");
	else if (status == ENOMEM)
		error("The process cannot allocate enough memory to create another mutex.");
	else if (status == EBUSY)
		error("Mutex is locked.");


}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error("Malloc failed.");
	return (ret);
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if	(LOCK == opcode)
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

void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error("No resources to create another thread.\n");
	else if (EPERM == status)
		error("The caller does note have appropriate permission.\n");
	else if (status == EINVAL && opcode == CREATE)
		error( "The value specified by attr is invalid.\n");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error("The value specified by thread not joinable.\n");
	else if (status == 	ESRCH)
		error("No thread could be found corresponding to that specified by the given thread ID.\n");
	else if (status == EDEADLK)
		error("A deadlock was detected or the value of thread specifies the calling thread.\n");
}
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode e_opcode)
{
	if (CREATE == e_opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), e_opcode);
	else if (JOIN == e_opcode)
		handle_thread_error(pthread_join(*thread, NULL), e_opcode);
	else if (DETACH == e_opcode)
		handle_thread_error(pthread_detach(*thread), e_opcode);
	else
		error("Wrong opcode for thread handle: use <CREATE>, <JOIN> or <DETACH>.");
}

long	philo_atol(const char *str_arg)
{
	long	nbr;
	int		sign;
	const char	*str;

	str = str_arg;
	nbr = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	nbr = nbr * sign;
	return (nbr);
}
long	arg_convert(const char *str_arg)
{
	long		nbr;

	philo_valid_input(str_arg);
	nbr = philo_atol(str_arg);
	if (nbr > INT_MAX)
		error("Invalid argument. Number is too big.");
	return (nbr);
}
