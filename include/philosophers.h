/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:34:18 by leobarbo          #+#    #+#             */
/*   Updated: 2024/07/13 18:46:19 by leobarbo         ###   ########.fr       */
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
# include <errno.h> // errno

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
# define O		"\001\033[38;5;208m\002" /* Orange */

//****************************************************************************//
//                                   Enums                                    //
//****************************************************************************//


# define DEBUG 1;  // Retirar essa macro  antes de entregar

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_RIGHT_FORK,
	TAKE_LEFT_FORK,
	DIED,
}	t_status;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;


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
	int			id;
	long		meals_count;
	bool		full;
	long		last_meal_time;
	t_fork		*second_fork;
	t_fork		*first_fork;
	t_table		*table;
	pthread_t	thread_id; //A philo is a thread
	t_mtx		philo_mutex;
}				t_philo;

//Table structure
struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		limit_meals;
	long		start_simulation;
	long		threads_running_nbr;
	bool		end_simulation;
	bool		all_threads_created; // to synch philos
	pthread_t	monitor;
	t_mtx		table_mutex; // avoid races while reading from tables
	t_mtx		write_mutex;
	t_philo		*philos;
	t_fork		*forks;
};

//****************************************************************************//
//                                 Functions                                  //
//****************************************************************************//

// action.c
void		write_action(t_status status, t_philo *philo, bool debug);// tirar debug
void		write_status_debug(t_philo *philo, t_status status, long elapsed);
void		eat(t_philo *philo); // tirar debug
void		thinking(t_philo *philo, bool pre_sim);
void		sleeping(t_philo *philo);

//dinner.c
void		*dinner_simulation(void *data);
void		start_dinner(t_table *table);

//get_set.c
void		set_bool(t_mtx *mutex, bool *dest, bool value);
bool		get_bool(t_mtx *mutex, bool *value);
void		set_long(t_mtx *mutex, long *dest, long value);
long		get_long(t_mtx *mutex, long *value);
void		increase_long(t_mtx *mutex, long *value);

//init.c
void		assign_forks(t_philo *philo, t_fork *forks, int philo_position);
void		philo_init(t_table *table);
void		init_table(t_table *table);

//main.c
int			main(int argc, char **argv);

//monitor.c
bool		philo_died(t_philo *philo);
void		*monitor_simulation(void *data);

//mutex.c
void		handle_mutex_error(int status, t_opcode opcode);
void		safe_mutex_handle(t_mtx *mutex, t_opcode opcode);

//one_philo.c
void		*lone_philo(void *data);

//parsing.c
const char	*philo_valid_input(const char *str_arg);
void		parse_args(t_table *table, char **av);

//synch.c
void		wait_all_threads_created(t_table *table);
bool		simulation_finished(t_table *table);
bool		all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
long		get_time(t_time_code time_code);
void		precise_usleep(long usec, t_table *table);

//threads.c
void		handle_thread_error(int status, t_opcode opcode);
void		safe_thread_handle(pthread_t *thread, \
				void *(*foo)(void *), void *data, t_opcode e_opcode);

//utils.c
void		error(char *msg);
void		*safe_malloc(size_t bytes);
long		philo_atol(const char *str_arg);
long		arg_convert(const char *str_arg);
void		clean(t_table *table);

#endif
