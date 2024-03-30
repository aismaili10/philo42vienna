/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:48:24 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/30 17:35:25 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_input
{
	size_t		num_philo;
	size_t		time_die;
	size_t		time_eat;
	size_t		time_sleep;
	size_t		meals_to_eat;
}	t_input;

typedef struct s_philo
{
	size_t		meals_had;
	bool		*philo_died;
	pthread_t	*philo;
}	t_philo;


int		man_input(int ac, char *av[], t_input *input);
size_t	philo_ato_size_t(char *str, int	*overflow);


#endif