/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:47:17 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/30 17:39:21 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//./philo num_of_philos time_to_die time_to_eat time_to_sleep (num_of_meals_each)

/*
int	prep_create_t()
{
	//which variables are needed
	//locks are the forks
	//
	//
}*/

int	main(int ac, char *av[])
{
	//int			ret;
	t_input		input;


	if (ac < 5 || ac > 6)
		return (print_usage(), 1);
	if (man_input(ac, av, &input) == -2)
		return (2);
	//prep_create_t(&input);
	//create_threads();
}





	//test input checks
	//printf("%zu\n%zu\n%zu\n%zu\n%zu\n", input.num_philo, input.time_die, input.time_eat, input.time_sleep, input.meals_to_eat);

/*
	What to print:

	Any state change of a philosopher must be formatted as follows:
	◦ timestamp_in_ms X has taken a fork
	◦ timestamp_in_ms X is eating
	◦ timestamp_in_ms X is sleeping
	◦ timestamp_in_ms X is thinking
	◦ timestamp_in_ms X died
	
	Replace timestamp_in_ms with the current timestamp in milliseconds
	and X with the philosopher number.

*/