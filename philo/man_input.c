/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   man_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:31:50 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/30 18:06:51 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	assign_num(char *str, int i, t_input *input)
{
	size_t	tmp;
	int		overflow;

	overflow = 0;
	tmp = philo_ato_size_t(str, &overflow);
	if (i == 1)
		input->num_philo = tmp;
	else if (i == 2)
		input->time_die = tmp;
	else if (i == 3)
		input->time_eat = tmp;
	else if (i == 4)
		input->time_sleep = tmp;
	else if (i == 5)
		input->meals_to_eat = tmp;
	if (overflow)
		return (write(2, "size_t overflow\n", 17), -1);
	if (tmp == 0)
		return (write(2, "0 not accepted as input\n", 25), -1);
	return (1);
}

static int	check_numeric(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i == 0 && str[i] == '+')
			continue ;
		if (str[i] < '0' || str[i] > '9')
		{
			write(2, "Invalid Input\n", 15);
			return (1);
		}
	}
	return (0);
}

int	man_input(int ac, char *av[], t_input *input)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (check_numeric(av[i]))
			return (-2);
		if (assign_num(av[i], i, input) < 0)
			return (-2);
	}
	if (ac != 6)
		input->meals_to_eat = 0;
	return (0);
}
