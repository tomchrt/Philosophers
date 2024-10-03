/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <tchareto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 08:25:32 by tchareto          #+#    #+#             */
/*   Updated: 2024/10/03 08:25:38 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "limits.h"
# include "pthread.h"
# include "stdio.h"
# include "stdlib.h"
# include "sys/time.h"
# include "unistd.h"

typedef struct s_rules
{
	int				philo_number;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				meals_to_eat;
}					t_rules;

typedef struct s_dinner
{
	struct s_philo	*philo;
	t_rules			rules;
	time_t			start_time;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	print_mutex;
	int				dead;
	int				ready;

}					t_dinner;

typedef struct s_philo
{
	pthread_t		thread;
	int				rank;
	struct s_philo	*next;
	time_t			last_meal;
	pthread_mutex_t	last_meal_mutex;
	int				meal_count;
	int				fork;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	meal_mutex;
	struct s_dinner	*dinner;
}					t_philo;

int					thread_launcher(t_dinner *dinner, t_philo **philos);
int					dinner_init(t_dinner *dinner, int argc, char **argv);
t_rules				rules_init(int argc, char **argv);
int					check_args(int argc, char **argv);
int					ft_is_number(char *str);
time_t				current_timestamp(void);
int					thread_launcher(t_dinner *dinner, t_philo **philos);
void				get_ready(t_philo *philo);
int					print_info(t_philo *philo, char *info);
int					ft_is_dead(t_philo *philo);
void				*routine(void *arg);
void				custom_usleep(time_t time_sleep, t_philo *philo);
int					eat(t_philo *philo);
int					take_forks(t_philo *philo, int fork);
t_philo				**create_philo(t_dinner *dinner);
void				end_check(t_dinner *dinner, t_philo **philos);
int					check_dead(t_philo *philo);
int					check_meals(t_philo *philo, int nb_max_meal);
void				set_dead(t_philo *philo);
void				print_dead(t_philo *philo);
int					sleeping(t_philo *philo);
void				free_philo(t_dinner *dinner, t_philo **philos);

#endif