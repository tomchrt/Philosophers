/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <tchareto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 04:13:54 by tchareto          #+#    #+#             */
/*   Updated: 2024/10/03 09:34:59 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->dinner->dead_mutex);
	dead = philo->dinner->dead;
	pthread_mutex_unlock(&philo->dinner->dead_mutex);
	return (dead);
}

void	set_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->dead_mutex);
	philo->dinner->dead = 1;
	pthread_mutex_unlock(&philo->dinner->dead_mutex);
}

void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->print_mutex);
	printf("%ld %u died\n", (current_timestamp() - philo->dinner->start_time),
		philo->rank);
	pthread_mutex_unlock(&philo->dinner->print_mutex);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	// printf("curent time : %ld\n", current_timestamp());
	// printf("philos last meal : %ld\n", philo->last_meal);
	// printf("condition de con : %ld\n", current_timestamp() - philo->last_meal);
	// printf("philos last time to eat : %d\n", philo->dinner->rules.time_to_die);
	if ((current_timestamp()
			- philo->last_meal) > philo->dinner->rules.time_to_die)
	{
		set_dead(philo);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (1);
}
