/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:16:45 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/31 16:29:55 by aismaili         ###   ########.fr       */
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
