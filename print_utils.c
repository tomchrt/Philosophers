/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <tchareto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 02:00:05 by tchareto          #+#    #+#             */
/*   Updated: 2024/10/03 13:43:23 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_info(t_philo *philo, char *info)
{
	pthread_mutex_lock(&philo->dinner->print_mutex);
	if (ft_is_dead(philo))
		return (pthread_mutex_unlock(&philo->dinner->print_mutex), 0);
	printf("%ld %u %s\n", (current_timestamp() - philo->dinner->start_time),
		philo->rank, info);
	pthread_mutex_unlock(&philo->dinner->print_mutex);
	return (1);
}
