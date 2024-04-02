/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:55:05 by aismaili          #+#    #+#             */
/*   Updated: 2024/04/02 13:26:15 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	philo_ato_size_t(char *str, int	*overflow)
{
	int		i;
	size_t	res;
	size_t	old_res;

	if (!str)
		return (0);
	i = 0;
	res = 0;
	old_res = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		old_res = res;
		res = res * 10 + (str[i] - '0');
		if (res < old_res)
			*overflow = 1;
		i++;
	}
	return (res);
}

void	print_usage(void)
{
	write(2, "Usage:\n./philo num_of_philos time_to_die ", 42);
	write(2, "time_to_eat time_to_sleep (num_of_meals_each)\n", 47);
}

size_t	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		write(2, "gettimeofday fail\n", 19);
		return (1);
	}
	return (((size_t)tv.tv_sec * 1000) + ((size_t)tv.tv_usec / 1000));
}

int init_forks(pthread_mutex_t *fork_mutex, t_input *input)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < input->num_philo)
	{
		if (pthread_mutex_init(&fork_mutex[i], NULL) != 0)
		{
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&fork_mutex[j]);
			write(2, "pthread_mutex_init fail\n", 25);
			return (-1);
		}
	}
	return (0);
}

void	ft_usleep(size_t sleep_time, t_philo *philo)
{
	size_t	start_time;
	size_t	time_slept;

	start_time = ft_get_time();
	time_slept = 0;
	while (time_slept <= sleep_time)
	{
		usleep(1000);
		pthread_mutex_lock(philo->death_mutex);
		if (*philo->philo_died == true)// how di differenciate between died, because of starvation and died, because of eaten enough? --> introduce new variable for eaten_enough?
		{
			pthread_mutex_unlock(philo->death_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->death_mutex);
		time_slept = ft_get_time()
				 - start_time;
	}
}
