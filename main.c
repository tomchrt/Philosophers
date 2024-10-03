/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <tchareto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:32:05 by tchareto          #+#    #+#             */
/*   Updated: 2024/10/03 14:37:54 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->rules.philo_number)
	{
		pthread_mutex_destroy(&dinner->philo[i].fork_mutex);
		pthread_mutex_destroy(&dinner->philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&dinner->dead_mutex);
	pthread_mutex_destroy(&dinner->ready_mutex);
	pthread_mutex_destroy(&dinner->print_mutex);
}

void	free_philo(t_dinner *dinner, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < dinner->rules.philo_number)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}

int	join_threads(t_dinner *dinner, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < dinner->rules.philo_number)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
	free_philo(dinner, philos);
	return (1);
}

int	main(int argc, char **argv)
{
	t_dinner	dinner;
	t_philo		**philos;

	if (!check_args(argc, argv))
		return (0);
	if (!dinner_init(&dinner, argc, argv))
		return (0);
	philos = create_philo(&dinner);
	if (!philos)
		return (0);
	if (!thread_launcher(&dinner, philos))
		return (0);
	if (!join_threads(&dinner, philos))
		return (0);
	return (1);// 
}
