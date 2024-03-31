/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:55:05 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/30 18:06:22 by aismaili         ###   ########.fr       */
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
	write(2, "Usage: ./philo num_of_philos time_to_die ", 42);
	write(2, "time_to_eat time_to_sleep (num_of_meals_each)\n", 47);
}
