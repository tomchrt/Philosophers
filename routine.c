/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <tchareto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 01:12:30 by tchareto          #+#    #+#             */
/*   Updated: 2024/10/03 09:33:18 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_check(t_dinner *dinner, t_philo **philos)
{
	int	nb_max_meal;
	int	i;
	int	total_philos;

	nb_max_meal = 0;
	total_philos = dinner->rules.philo_number;
	i = 0;
	while (i < total_philos)
	{
		if (!check_dead(philos[i]))
		{
			if (nb_max_meal != total_philos)
				print_dead(philos[i]);
			break ;
		}
		nb_max_meal = check_meals(philos[i], nb_max_meal);
		if (nb_max_meal == total_philos)
		{
			set_dead(philos[i]);
			break ;
		}
		i++;
		usleep(1);
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
