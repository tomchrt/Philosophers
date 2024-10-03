/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <tchareto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 08:26:09 by tchareto          #+#    #+#             */
/*   Updated: 2024/10/03 08:29:12 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 6 && argc != 5)
	{
		write(2, "Wrong arguments number", 23);
		return (0);
	}
	while (i < argc)
	{
		if ((atoi(argv[i]) < 0) || (atoi(argv[i]) >= INT_MAX)
			|| !(ft_is_number(argv[i])))
		{
			write(2, "Input is not numbers", 21);
			return (0);
		}
		i++;
	}
	return (1);
}
