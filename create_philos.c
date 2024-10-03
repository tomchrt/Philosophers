/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <tchareto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:59:33 by tchareto          #+#    #+#             */
/*   Updated: 2024/10/03 14:42:12 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_launcher(t_dinner *dinner, t_philo **philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&dinner->ready_mutex);
	while (i < dinner->rules.philo_number)
	{
		if (pthread_create(&philos[i]->thread, NULL, &routine, philos[i]))
		{
			pthread_mutex_unlock(&dinner->ready_mutex);
			return (0);
		}
		i++;
	}
	dinner->start_time = current_timestamp();
	pthread_mutex_unlock(&dinner->ready_mutex);
	end_check(dinner, philos);
	return (1);
}

void	init_philos(t_philo **philos, t_dinner *dinner, int i)
{
	pthread_mutex_init(&philos[i]->fork_mutex, NULL);
	pthread_mutex_init(&philos[i]->meal_mutex, NULL);
	pthread_mutex_init(&philos[i]->last_meal_mutex, NULL);
	philos[i]->dinner = dinner;
	philos[i]->rank = i + 1;
	philos[i]->last_meal = current_timestamp();
	philos[i]->meal_count = 0;
	philos[i]->fork = 0;
}

void	set_next(t_philo **philo, t_dinner *dinner, int i)
{
	if (i != dinner->rules.philo_number - 1)
		philo[i]->next = philo[i + 1];
	else
		philo[i]->next = philo[0];
}

t_philo	**create_philo(t_dinner *dinner)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo *) * dinner->rules.philo_number);
	if (!philos)
	//free_philo
		return (NULL);
	while (i < dinner->rules.philo_number)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (NULL);
		init_philos(philos, dinner, i);
		i++;
	}
	i = 0;
	while (i < dinner->rules.philo_number)
	{
		set_next(philos, dinner, i);
		i++;
	}
	return (philos);
}
