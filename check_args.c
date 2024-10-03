/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <tchareto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 08:26:09 by tchareto          #+#    #+#             */
/*   Updated: 2024/10/03 14:34:05 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_atoi(const char *str)
{
	int		i;
	int		fact;
	long	res;

	i = 0;
	fact = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		||str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			fact = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((((res * 10) + (str[i] - '0')) / 10) != res)
			return ((((fact < 0) * LONG_MIN)) + (fact > 0) * LONG_MAX);
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * fact);
}

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
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
	{
		write(2, "Meals count has to be at least 1", 33);
		return (0);
	}
	if (argc != 6 && argc != 5)
	{
		write(2, "Wrong arguments number", 23);
		return (0);
	}
	while (i < argc)
	{
		if ((ft_atoi(argv[i]) < 0) || (ft_atoi(argv[i]) >= INT_MAX)
			|| !(ft_is_number(argv[i])))
		{
			write(2, "Input is not numbers", 21);
			return (0);
		}
		i++;
	}
	return (1);
}
