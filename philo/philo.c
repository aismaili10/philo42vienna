/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:47:17 by aismaili          #+#    #+#             */
/*   Updated: 2024/04/05 10:49:34 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_input	input;
	t_philo	*philo;

	if (ac < 5 || ac > 6)
		return (print_usage(), 1);
	if (man_input(ac, av, &input) == -2)
		return (2);
	philo = malloc(sizeof(t_philo) * input.num_philo);
	if (!philo)
		return (3);
	if (prep_create_t(&input, philo) == -1)
		return (free(philo), 4);
	return (create_threads(philo));
}
