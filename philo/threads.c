/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:45:01 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/31 18:51:40 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	size_t			time;

	printf("in ft_print ft_get_time: %zu\n", ft_get_time());
	time = ft_get_time() - philo->start_time;
	printf("in ft_print time = ft_get_time() - philo->start_time: %zu\n", time);
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

void	*routine(void *philo_)
{
	t_philo	*philo;

	philo = (t_philo *)philo_;
	philo->start_time = ft_get_time();
	// avoid deadlock / manage proper order
	//odd id goes first
	if (!(philo->philo_id % 2))
		usleep(500);
	while (1)
	{
		//routine
		//eat
		ft_eat(philo);
		philo->lst_meal_rt = ft_get_time();//get time of lst meal after eating
		//sleep
		ft_print(philo, "is sleeping");
		ft_usleep(philo->input.time_sleep);
		//think
		ft_print(philo, "is thinking");// just print, not specified how long!
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
	j = -1;
	while (++j < i)
	{
		if (pthread_join(philo[i].thread_id, NULL) != 0 && errno != 0)
		{
			printf("j: %zu and i: %zu errno: %d\n", j, i, errno);
			perror("pthread_join");
			return (write(2, "pthread_join fail\n", 19), -1);
		}
	}
	return (0);
}
