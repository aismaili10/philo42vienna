/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:45:01 by aismaili          #+#    #+#             */
/*   Updated: 2024/04/05 13:35:48 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	case_one_philo(t_philo *philo)
{
	if (pthread_create(&philo->thread_id, NULL, one_routine, &philo[0]) != 0)
	{
		print_err_msg(philo, "pthread_create fail\n");
		return (1);
	}
	ft_monitor(philo, &philo->input);
	if (pthread_join(philo->thread_id, NULL) != 0)
	{
		print_err_msg(philo, "pthread_join fail\n");
		return (1);
	}
	return (0);
}

static int	joining_threads(t_philo *philo, size_t i)
{
	size_t	j;
	int		ret;

	ret = 0;
	j = -1;
	while (++j < i)
	{
		if (pthread_join(philo[j].thread_id, NULL) != 0)
		{
			print_err_msg(philo, "pthread_join fail\n");
			ret = 1;
			continue ;
		}
	}
	return (ret);
}

static int	assign_lst_meal_rt(t_philo *philo, size_t i)
{
	pthread_mutex_lock(philo->meals_mutex);
	philo[i].lst_meal_rt = ft_get_time();
	if (philo[i].lst_meal_rt == 1)
	{
		pthread_mutex_unlock(philo->meals_mutex);
		print_err_msg(philo, "gettimeofday fail\n");
		set_philo_died(philo);
		return (1);
	}
	pthread_mutex_unlock(philo->meals_mutex);
	return (0);
}

static int	case_multi_philo(t_philo *philo)
{
	size_t	i;
	int		ret;

	ret = 0;
	i = -1;
	while (++i < philo->input.num_philo)
	{
		if (pthread_create(&philo[i].thread_id, NULL, routine,
				(void *)&philo[i]) != 0)
		{
			print_err_msg(philo, "pthread_create fail\n");
			set_philo_died(philo);
			ret = 1;
			break ;
		}
		ret = assign_lst_meal_rt(philo, i);
		if (ret)
			break ;
	}
	ft_monitor(philo, &philo->input);
	return (ret + joining_threads(philo, i));
}

int	create_threads(t_philo *philo)
{
	size_t	ret;

	if (philo->input.num_philo == 1)
		ret = case_one_philo(philo);
	else
		ret = case_multi_philo(philo);
	clean_up(philo);
	return (ret);
}
