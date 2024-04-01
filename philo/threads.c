/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:45:01 by aismaili          #+#    #+#             */
/*   Updated: 2024/04/01 18:40:22 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	/* size_t	time;

	printf("in ft_print ft_get_time: %zu\n", ft_get_time());
	time = ft_get_time() - philo->start_time;
	printf("in ft_print time = ft_get_time() - philo->start_time: %zu\n", time); */
	pthread_mutex_lock(philo->write_mutex);
	printf("%zu %zu %s\n", ft_get_time() - philo->start_time, philo->philo_id, str);
	pthread_mutex_unlock(philo->write_mutex);
}

void	grabbing_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->own_fork_mutex);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->next_fork_mutex);
	ft_print(philo, "has taken a fork");
}

void	ft_eat(t_philo *philo)
{
	grabbing_forks(philo);
	ft_print(philo, "is eating");// always print first 
	ft_usleep(philo->input.time_eat);// implement own usleep funtion
	pthread_mutex_unlock(philo->next_fork_mutex);
	pthread_mutex_unlock(philo->own_fork_mutex);// is this the right order putting back
}

bool	still_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->philo_died == false)
	{
		//printf("in still alive: philo_died: %d\n", (*philo->philo_died));
		pthread_mutex_unlock(philo->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(philo->death_mutex);
	return (false);
}

void	*routine(void *philo_)
{
	t_philo	*philo;

	philo = (t_philo *)philo_;
	philo->start_time = ft_get_time();
	// avoid deadlock
	// odd id goes first
	if (!(philo->philo_id % 2))
		usleep(500);
	while (still_alive(philo))
	{
			ft_eat(philo);
			pthread_mutex_lock(philo->meals_mutex);
			// increment meals_enjoyed
			philo->meals_enjoyed++;
			pthread_mutex_unlock(philo->meals_mutex);
			philo->lst_meal_rt = ft_get_time();// get time of lst meal after eating
			// sleep
			ft_print(philo, "is sleeping");
			ft_usleep(philo->input.time_sleep);
			// think
			ft_print(philo, "is thinking");// just print, not specified how long!
	}
	return (NULL);
}

void	ft_monitor(t_philo *philo, t_input *input)
{
		size_t	i;

	// printf("in monitor\n");
	while (still_alive(philo))
	{
		i = -1;
		while (++i < input->num_philo)
		{
			pthread_mutex_lock(philo->meals_mutex);
			if (philo[i].meals_enjoyed >= input->meals_to_eat && input->meals_to_eat != 0)
				philo[i].enjoyed_all = true;
			pthread_mutex_unlock(philo->meals_mutex);
		}
		i = -1;
		while (++i < input->num_philo)
		{
			if (!philo[i].enjoyed_all)
				break ;
		}
		if (i == input->num_philo)
		{
			pthread_mutex_lock(philo->death_mutex);
			*philo->philo_died = true;
			printf("setting philo_died to true: %d\n", (*philo->philo_died));
			pthread_mutex_unlock(philo->death_mutex);
			break ;
		}
	}
}

int	create_threads(t_philo *philo)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < philo->input.num_philo)
	{
		if (pthread_create(&philo[i].thread_id, NULL, routine,
				(void *)&philo[i]) != 0)
		{
			write (2, "pthread_create fail\n", 21);
			break ;
		}
	}
	ft_monitor(philo, &philo->input);//check for meals_enjoyed
	j = -1;
	while (++j < i)
	{
		if (pthread_join(philo[j].thread_id, NULL) != 0 && errno != 0)
		{
			printf("j: %zu and i: %zu errno: %d\n", j, i, errno);
			perror("pthread_join");
			return (write(2, "pthread_join fail\n", 19), -1);
		}
	}
	return (0);
}
