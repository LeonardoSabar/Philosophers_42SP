/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:34:18 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/29 17:09:47 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//****************************************************************************//
//                                  Includes                                  //
//****************************************************************************//

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h> // mutex: destroy, init, lock, unlock
# include <sys/time.h> // gettimeofday
# include <limits.h> // INT_MAX

//****************************************************************************//
//                                  Colors.                                   //
//****************************************************************************//

# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */

//****************************************************************************//
//                                  Structs                                   //
//****************************************************************************//

//mutex structure
typedef pthread_mutex_t	t_mtx;

typedef struct s_table	t_table;

//fork structure
typedef struct fork
{
	t_mtx		fork;
	int			fork_id;
}				t_fork;


//philosopher structure
typedef struct	s_philo
{
int				id;
	int			eat_count;
	bool		full;
	long		time_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id; //A philo is a thread
	t_table		*table;
}				t_philo;

//Table structure

struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	limit_meals;
	long	start_time;
	bool	end_simulation;
	t_philo	*philos;
	t_fork	*forks;
};

//****************************************************************************//
//                                 Functions                                  //
//****************************************************************************//

const char	*philo_valid_input(const char *str_arg);
void		error(char *msg);
long		philo_atol(const char *str_arg);
int			valid_nbr(long nbr);
void		parse_args(t_table *table, char **av);

#endif
