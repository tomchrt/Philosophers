#ifndef PHILO_H
#define PHILO_H

#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"
#include "limits.h"
#include "stdio.h"
#include "sys/time.h"

typedef struct s_fork
{
    int value;
    pthread_mutex_t *mutex;

}t_fork;

typedef enum e_state
{
    DEAD,
    EATING,
    SLEEPING,
    THINKING,
}t_state;

typedef struct s_philo
{
	t_state			state;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				rank;
	long long		last_meal_time;
	struct s_philo	*next;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int 			meal_count;
	pthread_t		thread;
	long long 		start_time;
	pthread_mutex_t *death_mutex;
	pthread_mutex_t *print_mutex;

	
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