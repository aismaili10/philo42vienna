/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:45:01 by aismaili          #+#    #+#             */
/*   Updated: 2024/04/03 18:52:01 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->write_mutex);
	printf("%zu %zu %s\n", ft_get_time() - philo->start_time, philo->philo_id, str);
	pthread_mutex_unlock(philo->write_mutex);
}

int	grabbing_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->own_fork_mutex);
	if (!still_alive(philo))
		return (pthread_mutex_unlock(philo->own_fork_mutex), 1);
	ft_print(philo, "has taken a fork");
	if (!still_alive(philo))
		return (pthread_mutex_unlock(philo->own_fork_mutex), 1);
	pthread_mutex_lock(philo->next_fork_mutex);
	if (!still_alive(philo))
		return (2);
	ft_print(philo, "has taken a fork");
	if (!still_alive(philo))
		return (2);
	return (0);
}

int	grabbing_forks_even(t_philo *philo)
{
	pthread_mutex_lock(philo->next_fork_mutex);
	if (!still_alive(philo))
		return (pthread_mutex_unlock(philo->next_fork_mutex), 1);
	ft_print(philo, "has taken a fork");
	if (!still_alive(philo))
		return (pthread_mutex_unlock(philo->next_fork_mutex), 1);
	pthread_mutex_lock(philo->own_fork_mutex);
	if (!still_alive(philo))
		return (2);
	ft_print(philo, "has taken a fork");
	if (!still_alive(philo))
		return (2);
	return (0);
}

void	ft_eat(t_philo *philo)
{
	int	ret;

	if (philo->philo_id % 2 == 1)
		ret = grabbing_forks_odd(philo);
	else
		ret = grabbing_forks_even(philo);
	if (ret)
	{
		if (ret == 1)
			return ;
		pthread_mutex_unlock(philo->next_fork_mutex);
		pthread_mutex_unlock(philo->own_fork_mutex);
		return ;
	}
	ft_print(philo, "is eating");// always print first
	ft_usleep(philo->input.time_eat, philo);// implement own usleep funtion
	pthread_mutex_lock(philo->meals_mutex);
	philo->meals_enjoyed++;
	philo->lst_meal_rt = ft_get_time();// get time of lst meal after eating
	pthread_mutex_unlock(philo->meals_mutex);
	pthread_mutex_unlock(philo->next_fork_mutex);
	pthread_mutex_unlock(philo->own_fork_mutex);
}

bool	still_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->philo_died == false)
	{
		pthread_mutex_unlock(philo->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(philo->death_mutex);
	return (false);
}

int	check_for_death(t_philo *philo)
{
	pthread_mutex_lock(philo->meals_mutex);
	if (ft_get_time() - philo->lst_meal_rt >= philo->input.time_die)
	{
		pthread_mutex_unlock(philo->meals_mutex);
		pthread_mutex_lock(philo->death_mutex);
		*philo->philo_died = true;
		pthread_mutex_unlock(philo->death_mutex);
		ft_print(philo, "died");
		return (1);
	}
	pthread_mutex_unlock(philo->meals_mutex);
	return (0);
}

void	*routine(void *philo_)
{
	t_philo	*philo;

	philo = (t_philo *)philo_;
	//philo->start_time = ft_get_time();
	if (!(philo->philo_id % 2))// even
		usleep(500);
	while (still_alive(philo))
	{
		ft_eat(philo);
		if (!still_alive(philo))
			break ;
		ft_print(philo, "is sleeping");
		ft_usleep(philo->input.time_sleep, philo);
		if (!still_alive(philo))
			break ;
		ft_print(philo, "is thinking");// just print, not specified how long!
		if (philo->philo_id % 2 && still_alive(philo))// odd
		{
			if (philo->input.time_eat >= philo->input.time_sleep)
				usleep(1000 * (philo->input.time_eat - philo->input.time_sleep) + 500);
			else
				usleep(1000 * (philo->input.time_sleep - philo->input.time_eat) + 500);
		}
	}
	return (NULL);
}

void	ft_monitor(t_philo *philo, t_input *input)
{
	size_t	i;

	while (1)
	{
		usleep(100);
		i = -1;
		while (++i < input->num_philo)
			if (check_for_death(&philo[i]))
				break ;
		if (!still_alive(philo))
			break ;
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
			pthread_mutex_unlock(philo->death_mutex);
			break ;
		}
	}
}

void	*one_routine(void *philo_)
{
	t_philo	*philo;

	philo = (t_philo *)philo_;
	pthread_mutex_lock(philo->own_fork_mutex);
	if (!still_alive(philo))
		return (NULL);
	ft_print(philo, "has taken a fork");
	pthread_mutex_unlock(philo->own_fork_mutex);
	while (still_alive(philo))
	{}
	return (NULL);
}

int	case_one_philo(t_philo *philo)
{
	if (pthread_create(&philo->thread_id, NULL, one_routine, &philo[0]) != 0)
	{
		write(2, "pthread_create fail\n", 21);
		return (-1);
	}
	ft_monitor(philo, &philo->input);//check for meals_enjoyed and death
	if (pthread_join(philo->thread_id, NULL) != 0)
	{
		write(2, "pthread_join fail\n", 19);
		return (-1);
	}
	return (0);
}

int	case_multi_philo(t_philo *philo)
{
	size_t	i;
	size_t	j;

	i = -1;
	//j = ft_get_time();
	while (++i < philo->input.num_philo)
	{
		if (pthread_create(&philo[i].thread_id, NULL, routine,
				(void *)&philo[i]) != 0)
		{
			write (2, "pthread_create fail\n", 21);
			break ;
		}
		philo[i].start_time = ft_get_time();
	}
	ft_monitor(philo, &philo->input);//check for meals_enjoyed
	j = -1;
	while (++j < i)
	{
		if (pthread_join(philo[j].thread_id, NULL) != 0 && errno != 0)
			return (write(2, "pthread_join fail\n", 19), -1);
	}
	return (0);
}

int	create_threads(t_philo *philo)
{
	size_t	ret;

	ret = 0;
	if (philo->input.num_philo == 1)
		ret = case_one_philo(philo);
	else
		ret = case_multi_philo(philo);
	clean_up(philo);
	return (ret);
}
