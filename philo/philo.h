/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:48:24 by aismaili          #+#    #+#             */
/*   Updated: 2024/04/05 13:23:20 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	bool			*philo_died;
	size_t			meals_enjoyed;
	t_input			input;
	size_t			philo_id;
	size_t			lst_meal_rt;
	bool			enjoyed_all;
	size_t			start_time;
	pthread_t		thread_id;
	pthread_mutex_t	*own_fork_mutex;
	pthread_mutex_t	*next_fork_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*meals_mutex;
}	t_philo;

// man_input.c
int		man_input(int ac, char *av[], t_input *input);

// prep_create_t.c
int		prep_create_t(t_input *input, t_philo *philo);

// threads.c
int		create_threads(t_philo *philo);

//monitor.c
void	ft_monitor(t_philo *philo, t_input *input);
int		set_philo_died(t_philo *philo);

//ft_eat.c
int		ft_eat(t_philo *philo);
void	ft_print(t_philo *philo, char *str);
bool	still_alive(t_philo *philo);

//routine.c
void	*routine(void *philo_);
void	*one_routine(void *philo_);

// utils.c
size_t	philo_ato_size_t(char *str, int	*overflow);
size_t	ft_get_time(void);
int		init_forks(pthread_mutex_t *fork_mutex, t_input *input);
int		ft_usleep(size_t sleep_time, t_philo *philo);
int		ft_strlen(char *str);

// utils_2.c
int		ft_strlen(char *str);

// clean_up_and_msg.c
void	destroy_forks(pthread_mutex_t *forks, size_t num_philo);
void	destroy_dwm_mutex(pthread_mutex_t *locks);
void	clean_up(t_philo *philo);
void	print_usage(void);
void	print_err_msg(t_philo *philo, char *str);

#endif