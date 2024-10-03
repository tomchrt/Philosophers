/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <tchareto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:37:14 by tchareto          #+#    #+#             */
/*   Updated: 2024/10/03 08:23:13 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rules	rules_init(int argc, char **argv)
{
	t_rules	rules;

	rules.philo_number = atoi(argv[1]);
	rules.time_to_die = atoi(argv[2]);
	rules.time_to_eat = atoi(argv[3]);
	rules.time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		rules.meals_to_eat = atoi(argv[5]);
	else
		rules.meals_to_eat = -1;
	return (rules);
}

int	dinner_init(t_dinner *dinner, int argc, char **argv)
{
	dinner->rules = rules_init(argc, argv);
	dinner->dead = 0;
	dinner->ready = 0;
	dinner->start_time = 0;
	dinner->philo = NULL;
	if (pthread_mutex_init(&dinner->dead_mutex, NULL)
		|| pthread_mutex_init(&dinner->ready_mutex, NULL)
		|| pthread_mutex_init(&dinner->print_mutex, NULL))
		return (0);
	return (1);
}
