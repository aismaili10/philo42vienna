/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_create_t.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:56:56 by aismaili          #+#    #+#             */
/*   Updated: 2024/04/05 12:30:54 by aismaili         ###   ########.fr       */
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

static void	init_philos_locks_meal(t_philo *philo, pthread_mutex_t *locks)
{
	philo->death_mutex = &locks[DEATH];
	philo->write_mutex = &locks[WRITE];
	philo->meals_mutex = &locks[MEAL];
	philo->meals_enjoyed = 0;
	philo->enjoyed_all = false;
}

int	init_philos_input_forks(t_philo *philo, t_input *input,
		pthread_mutex_t *fork_mutex, size_t i)
{
	philo->input.num_philo = input->num_philo;
	philo->input.time_die = input->time_die;
	philo->input.time_eat = input->time_eat;
	philo->input.time_sleep = input->time_sleep;
	philo->input.meals_to_eat = input->meals_to_eat;
	philo->philo_id = i + 1;
	philo->lst_meal_rt = ft_get_time();
	if (philo->lst_meal_rt == 1)
		return (write(2, "gettimeofday fail\n", 19), 1);
	philo->own_fork_mutex = &fork_mutex[i];
	if (i == input->num_philo -1)
		philo->next_fork_mutex = &fork_mutex[0];
	else
		philo->next_fork_mutex = &fork_mutex[i + 1];
	return (0);
}

static int	init_philos(pthread_mutex_t *fork_mutex, t_input *input,
		t_philo *philo)
{
	size_t			i;
	size_t			time;
	bool			*philo_died_ptr;
	pthread_mutex_t	*locks;

	i = -1;
	philo_died_ptr = malloc(sizeof(bool));
	if (!philo_died_ptr)
		return (-1);
	*philo_died_ptr = false;
	time = ft_get_time();
	if (time == 1)
		return (write(2, "gettimeofday fail\n", 19), free(philo_died_ptr), -1);
	locks = malloc(sizeof(pthread_mutex_t) * 3);
	if (init_prep(locks) == -1)
		return (free(philo_died_ptr), -1);
	while (++i < input->num_philo)
	{
		philo[i].philo_died = philo_died_ptr;
		philo[i].start_time = time;
		if (init_philos_input_forks(&philo[i], input, fork_mutex, i))
			return (free(philo_died_ptr), destroy_dwm_mutex(locks), -1);
		init_philos_locks_meal(&philo[i], locks);
	}
	return (0);
}

int	prep_create_t(t_input *input, t_philo *philo)
{
	pthread_mutex_t	*fork_mutex;

	fork_mutex = malloc(sizeof(pthread_mutex_t) * input->num_philo);
	if (!fork_mutex)
		return (-1);
	if (init_forks(fork_mutex, input) == -1)
		return (free(fork_mutex), -1);
	if (init_philos(fork_mutex, input, philo) == -1)
		return (destroy_forks(fork_mutex, input->num_philo), -1);
	return (0);
}
