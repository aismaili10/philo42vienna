/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:48:24 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/30 17:35:25 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>

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
	//shared
	bool			*philo_died;//shared
	//individual
	t_input			*input;
	size_t			philo_id;//what is the purpose of this id?
	size_t			last_meal;//individual
	size_t			meals_enjoyed;//individual
	pthread_t		*thread_id;//to store the ID of the thread: used to join the thread with the main thread
	//mutexes for the shared recources and writing
	pthread_mutex_t	*fork_mutex;//one fork is used by two philo/threads
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*write_mutex;
}	t_philo;

int		man_input(int ac, char *av[], t_input *input);
size_t	philo_ato_size_t(char *str, int	*overflow);
void	print_usage(void);

#endif