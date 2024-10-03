/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <tchareto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 02:19:52 by tchareto          #+#    #+#             */
/*   Updated: 2024/10/03 09:42:09 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_philo *philo, int nb_max_meal)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->meal_count == philo->dinner->rules.meals_to_eat)
		nb_max_meal++;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (nb_max_meal);
}

int	take_forks(t_philo *philo, int fork)
{
	while (fork < 2)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		if (philo->fork == 0)
		{
			fork = fork + 1;
			if (!print_info(philo, "has taken a fork"))
				return (pthread_mutex_unlock(&philo->fork_mutex), 0);
		}
		pthread_mutex_unlock(&philo->fork_mutex);
		if (philo->dinner->rules.philo_number == 1)
			return (pthread_mutex_unlock(&philo->fork_mutex), 0);
		pthread_mutex_lock(&philo->next->fork_mutex);
		if (philo->next->fork == 0)
		{
			fork = fork + 1;
			philo->next->fork = 1;
			if (!print_info(philo, "has taken a fork"))
				return (pthread_mutex_unlock(&philo->next->fork_mutex), 0);
		}
		pthread_mutex_unlock(&philo->next->fork_mutex);
		usleep(1);
	}
	return (1);
}

int	eat(t_philo *philo)
{
	// if (!check_dead(philo))
	// 	print_dead(philo);
	if (!take_forks(philo, 0))
		return (0);
	if (!print_info(philo, "is eating"))
		return (0);
	custom_usleep(philo->dinner->rules.time_to_eat, philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meal_count += 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = current_timestamp();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_lock(&philo->fork_mutex);
	philo->fork = 0;
	pthread_mutex_unlock(&philo->fork_mutex);
	if (philo->next)
	{
		pthread_mutex_lock(&philo->next->fork_mutex);
		philo->next->fork = 0;
		pthread_mutex_unlock(&philo->next->fork_mutex);
	}
	return (1);
}
