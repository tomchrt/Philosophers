#ifndef PHILO_H
#define PHILO_H

#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"
#include "limits.h"
#include "stdio.h"
#include "sys/time.h"

typedef struct s_rules
{
	int philo_number;
	int time_to_eat;
	int time_to_die;
	int time_to_sleep;
	int meals_to_eat;
}t_rules;


typedef struct s_dinner
{
	struct s_philo		*philo;
	t_rules 			rules;
	time_t 				start_time;
	pthread_mutex_t 	dead_mutex;
	pthread_mutex_t 	ready_mutex;
	pthread_mutex_t		print_mutex;
	int					dead;
	int					ready;

}	t_dinner;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_t		thread;
	int				rank;
	struct s_philo	*next;
	time_t			last_meal;
	int				meal_count;
	int				fork;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	meal_mutex;
	struct s_dinner *dinner;
}t_philo;



t_philo **create_philo(int philos_number, int time_to_die, int time_to_eat, int time_to_sleep);
int ft_is_number(char *str);
int check_args_number(int argc, char **argv);
void add_fork(int philos_number);
void	ft_usleep(int ms);
long long	current_timestamp(void);
int	try_to_take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	think(t_philo *philo);
void	sleeping(t_philo *philo);
void	*routine(void *arg);
void	add_forks(t_philo **philos, int philos_number);


#endif