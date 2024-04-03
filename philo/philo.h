/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:48:24 by aismaili          #+#    #+#             */
/*   Updated: 2024/04/03 12:31:15 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <errno.h>

typedef enum e_mutex
{
	DEATH,
	WRITE,
	MEAL,
}	t_muxex;

typedef struct s_input
{
	size_t		num_philo;
	size_t		time_die;
	size_t		time_eat;
	size_t		time_sleep;
	size_t		meals_to_eat;
}	t_input;

typedef struct s_philo
{
	// shared
	bool			*philo_died;// shared and accessed by diff threads, malloced
	size_t			meals_enjoyed;// individual, but shared with the monitoring thread, 
	// individual
	t_input			input;
	size_t			philo_id;// for printing
	size_t			lst_meal_rt;// individual
	bool			enjoyed_all;// flag for each individual philo
	size_t			start_time;// needed for the timestamps: when to init?
	pthread_t		thread_id;// to store the ID of the thread: used to join the thread with the main thread
	// mutexes for the shared recources and writing
	pthread_mutex_t	*own_fork_mutex;// one fork is used by two philo/threads
	pthread_mutex_t	*next_fork_mutex;// each must have access to the fork of the next philo
	pthread_mutex_t	*death_mutex;// for all the death checks
	pthread_mutex_t	*write_mutex;// for each writing
	pthread_mutex_t	*meals_mutex;// for each writing
}	t_philo;

// man_input.c
int		man_input(int ac, char *av[], t_input *input);

// prep_create_t.c
int 	prep_create_t(t_input *input, t_philo *philo);

// threads.c
int		create_threads(t_philo *philo);
bool	still_alive(t_philo *philo);

// utils.c
size_t	philo_ato_size_t(char *str, int	*overflow);
void	print_usage(void);
size_t	ft_get_time(void);
int	 	init_forks(pthread_mutex_t *fork_mutex, t_input *input);
void	ft_usleep(size_t sleep_time, t_philo *philo);

// clean_up.c
void	destroy_forks(pthread_mutex_t *forks, size_t num_philo);
void	clean_up(t_philo *philo);

#endif