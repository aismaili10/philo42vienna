/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_create_t.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:56:56 by aismaili          #+#    #+#             */
/*   Updated: 2024/04/02 13:45:16 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_prep(pthread_mutex_t *locks)
{
	if (!locks)
		return (write(2, "malloc fail\n", 13), -1);
	if (pthread_mutex_init(&locks[DEATH], NULL) != 0)
		return (write(2, "pthread_mutex_init fail\n", 25), free(locks), -1);
	if (pthread_mutex_init(&locks[WRITE], NULL) != 0)
	{
		pthread_mutex_destroy(&locks[DEATH]);
		return (write(2, "pthread_mutex_init fail\n", 25), free(locks), -1);
	}
	if (pthread_mutex_init(&locks[MEAL], NULL) != 0)
	{
		pthread_mutex_destroy(&locks[WRITE]);
		pthread_mutex_destroy(&locks[DEATH]);
		return (write(2, "pthread_mutex_init fail\n", 25), free(locks), -1);
	}
	return (0);
}

static void	init_philos_mutex(t_philo *philo, pthread_mutex_t *locks)
{
	philo->death_mutex = &locks[DEATH];
	philo->write_mutex = &locks[WRITE];
	philo->meals_mutex = &locks[MEAL];
}

void	init_philos_input(t_philo *philo, t_input *input)
{
	philo->input.num_philo = input->num_philo;
	philo->input.time_die = input->time_die;
	philo->input.time_eat = input->time_eat;
	philo->input.time_sleep = input->time_sleep;
	philo->input.meals_to_eat = input->meals_to_eat;
}

static int init_philos(pthread_mutex_t *fork_mutex, t_input *input, t_philo *philo)
{
	size_t 			i;
	size_t			time;
	bool			*philo_died_ptr;
	pthread_mutex_t	*locks;

	i = -1;
	philo_died_ptr = malloc(sizeof(bool));
	if (!philo_died_ptr)
		return (-1);
	*philo_died_ptr = false;
	time = ft_get_time();
	locks = malloc(sizeof(pthread_mutex_t) * 3);//protect
	if (init_prep(locks) == -1)
		return (-1);
	while (++i < input->num_philo)
	{
		philo[i].philo_died = philo_died_ptr; // shared
		philo[i].philo_id = i + 1;
		philo[i].start_time = time;
		init_philos_input(&philo[i], input);
		philo[i].lst_meal_rt = ft_get_time();
		philo[i].meals_enjoyed = 0;
		philo[i].enjoyed_all = false;
		init_philos_mutex(&philo[i], locks);
		philo[i].own_fork_mutex = &fork_mutex[i];
		if (i == input->num_philo -1)
			philo[i].next_fork_mutex = &fork_mutex[0];
		else
			philo[i].next_fork_mutex = &fork_mutex[i + 1];
	}
	return (0);
}

int prep_create_t(t_input *input, t_philo *philo)
{
	pthread_mutex_t	*fork_mutex;
	// forks are the mutex_locks
	fork_mutex = malloc(sizeof(pthread_mutex_t) * input->num_philo);
	if (!fork_mutex)
		return (-1);
	if (init_forks(fork_mutex, input) == -1)
		return (free(fork_mutex), -1);
	if (init_philos(fork_mutex, input, philo) == -1)
		return (destroy_forks(fork_mutex, input->num_philo), -1);
	return (0);
}
