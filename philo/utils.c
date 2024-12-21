/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:55:05 by aismaili          #+#    #+#             */
/*   Updated: 2024/04/05 13:36:09 by aismaili         ###   ########.fr       */
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

size_t	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (1);
	return (((size_t)tv.tv_sec * 1000) + ((size_t)tv.tv_usec / 1000));
}

int	init_forks(pthread_mutex_t *fork_mutex, t_input *input)
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

int	ft_usleep(size_t sleep_time, t_philo *philo)
{
	size_t	beg_time;
	size_t	time_slept;
	size_t	curr_time;

	beg_time = ft_get_time();
	if (beg_time == 1)
		return (print_err_msg(philo, "gettimeofday fail\n"),
			set_philo_died(philo), 1);
	while (1)
	{
		if (!still_alive(philo))
			return (1);
		curr_time = ft_get_time();
		if (curr_time == 1)
			return (print_err_msg(philo, "gettimeofday fail\n"),
				set_philo_died(philo), 1);
		time_slept = curr_time - beg_time;
		if (time_slept >= sleep_time)
			break ;
		usleep(50);
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
