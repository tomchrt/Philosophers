/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <tchareto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:44:56 by tchareto          #+#    #+#             */
/*   Updated: 2024/10/03 13:43:14 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	current_timestamp(void)
{
	struct timeval	tv;
	time_t			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	custom_usleep(time_t time_sleep, t_philo *philo)
{
	time_t	start;

	start = current_timestamp();
	while (current_timestamp() - start < time_sleep && !ft_is_dead(philo))
	{
		usleep(100);
	}
}

void	get_ready(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->ready_mutex);
	pthread_mutex_unlock(&philo->dinner->ready_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = current_timestamp();
	pthread_mutex_unlock(&philo->last_meal_mutex);
}
