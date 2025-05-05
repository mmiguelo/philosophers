/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:40:25 by marvin            #+#    #+#             */
/*   Updated: 2025/05/04 14:40:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdio.h>
# include <errno.h>

/*=============================================================================#
#                                   DEFINES                                    #
#=============================================================================*/

#define DEBUG_MODE 0

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;

typedef enum e_timecode
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}			t_timecode;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_status;

/*
** ANSI color codes for terminal output
** Usage:
** 		printf(RED "This text is red" RST);
** 		printf(G "This text is green" RST);
** Remember to reset the color after using it with RST.
*/
# define RST	"\033[0m"		// reset color
# define RED	"\033[1;31m"	// bold red
# define G		"\033[1;32m"	// bold green
# define Y		"\033[1;33m"	// bold yellow
# define B		"\033[1;34m"	// bold blue
# define M		"\033[1;35m"	// bold magenta
# define C		"\033[1;36m"	// bold cyan
# define W		"\033[1;37m"	// bold white

/*=============================================================================#
#                                   STRUCTS                                    #
#=============================================================================*/

typedef pthread_mutex_t	t_mtx;

typedef struct s_table	t_table;

typedef struct s_fork	t_fork;

typedef struct s_philo
{
	int			id;
	long		meal_counter;
	bool		full;
	long		last_meal_time; // time passed from last meal
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id; //a philo is a thread
	t_mtx		philo_mutex;
	t_table		*table;
}				t_philo;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}				t_fork;

// ./philo 5 800 300 200 [7]

typedef struct s_table
{
	long	philo_nbr; // 5
	long	time_to_die; // 800
	long	time_to_eat; // 300
	long	time_to_sleep; // 200
	long	nbr_limit_meals; // [7] | FLAG if -1
	long	start_simulation; // time of start of simulation
	bool	end_simulation; // a philo dies or all philo full
	bool	all_threads_ready; // syncro philospphers
	t_mtx	table_mutex; // avoid races while reading from table
	t_mtx	write_mutex;
	t_fork	*forks; // array of forks
	t_philo	*philos; // array of philos
}				t_table;

/*=============================================================================#
#                                   FUNCTIONS                                  #
#=============================================================================*/

void	parse_input(t_table *table, char **av);
void	error_msg(const char *error);
void	data_init(t_table *table);
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
			t_opcode opcode);
void	dinner_start(t_table *table);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
bool	simulation_finished(t_table *table);
void	wait_all_threads(t_table *table);
long	gettime(t_timecode time_code);
void	precise_usleep(long usec, t_table *table);
void	write_status(t_status status, t_philo *philo);

#endif