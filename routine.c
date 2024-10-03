/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <tchareto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 01:12:30 by tchareto          #+#    #+#             */
/*   Updated: 2024/10/03 14:25:26 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_breaker(t_philo *philos)
{
	pthread_mutex_lock(&philos->dinner->dead_mutex);
	if (philos->dinner->dead == 1)
	{
		pthread_mutex_unlock(&philos->dinner->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->dinner->dead_mutex);
	return (0);
}

int	handle_number_meals(t_philo *philos, t_dinner *dinner, int *nb_max_meal)
{
	if (!check_dead(philos))
	{
		if (*nb_max_meal != dinner->rules.philo_number)
			print_dead(philos);
		return (1);
	}
	*nb_max_meal = check_meals(philos, *nb_max_meal);
	if (*nb_max_meal == dinner->rules.philo_number)
	{
		set_dead(philos);
		return (1);
	}
	return (0);
}

void	end_check(t_dinner *dinner, t_philo **philos)
{
	int	nb_max_meal;
	int	i;
	int	total_philos;

	nb_max_meal = 0;
	total_philos = dinner->rules.philo_number;
	i = 0;
	while (1)
	{
		i = 0;
		if (dead_breaker(philos[i]))
			break ;
		while (i < total_philos)
		{
			if (handle_number_meals(philos[i], dinner, &nb_max_meal))
				break ;
			i++;
			usleep(100);
		}
		usleep(100);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	get_ready(philo);
	if (!print_info(philo, "is thinking"))
		return (NULL);
	if (philo->rank % 2)
		custom_usleep(philo->dinner->rules.time_to_eat, philo);
	while (!(ft_is_dead(philo)))
	{
		if (!eat(philo))
			break ;
		if (!sleeping(philo))
			break ;
		if (!print_info(philo, "is thinking"))
			break ;
		usleep(1);
	}
	return (NULL);
}

int	sleeping(t_philo *philo)
{
	if (!print_info(philo, "is sleeping"))
		return (0);
	custom_usleep(philo->dinner->rules.time_to_sleep, philo);
	return (1);
}
