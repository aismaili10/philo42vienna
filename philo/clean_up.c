/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:16:45 by aismaili          #+#    #+#             */
/*   Updated: 2024/04/03 12:31:07 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(pthread_mutex_t *forks, size_t num_philo)
{
	size_t	i;

	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

void	clean_up(t_philo *philo)
{
	size_t	i;

	i = -1;
	destroy_forks(philo->own_fork_mutex, philo->input.num_philo);
	free(philo->philo_died);
	pthread_mutex_destroy(philo->death_mutex);
	pthread_mutex_destroy(philo->write_mutex);
	pthread_mutex_destroy(philo->meals_mutex);
	free(philo->death_mutex);
	free(philo);
}
