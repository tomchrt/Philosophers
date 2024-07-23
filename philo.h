#ifndef PHILO_H
#define PHILO_H

#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"
#include "limits.h"
#include "stdio.h"

typedef struct s_fork
{
    int value;
    pthread_mutex_t *mutex;

}t_fork;

typedef enum e_state
{
    EATING,
    SLEEPING,
    THINKING,
}t_state;

typedef struct s_philo
{
    t_state state;
    int time_to_eat;
    int rank;
    struct s_philo *next;
    t_fork *fork;
    pthread_t thread;

}t_philo;

t_philo **create_philo(int philos_number);
int ft_is_number(char *str);
int check_args_number(int argc, char **argv);
void add_fork(int philos_number);




#endif