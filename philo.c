#include "philo.h"
void routine(t_philo *data)
{   
    int i;

    i = 0;
    while(i < data->time_to_eat)
    {
        printf("Philosopher is thinking..");
        i++;
    }
}
void add_fork(int philos_number)
{
    int i;    
    t_fork **fork_mutex;

    i = 0;
    fork_mutex = malloc(sizeof(t_fork*) * philos_number);
    while(i < philos_number)
    {
        fork_mutex[i] = malloc(sizeof(t_fork));
        fork_mutex[i]->mutex = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(fork_mutex[i]->mutex, NULL);
        fork_mutex[i]->value = 0;
        i++;
    }
}

void create_philo(int philos_number)
{
    t_philo **philos;
    int i;

    i = 0;
    philos = malloc(sizeof(t_philo *) * philos_number);
    if(!philos)
        return;
    while(i < philos_number)
    {
        philos[i] = malloc(sizeof (t_philo));
        philos[i]->rank = i +1;
        philos[i]->state = THINKING;
        if (i != philos_number - 1)
            philos[i]->next = philos[i +1];
        else
            philos[i]->next = philos[0];
        i++;
    }
    add_fork(philos_number);
}

int main(int argc, char **argv)
{
    pthread_t tid;
    int i;

    i = 0;
    check_args_number(argc, argv);
    while(i < atoi(argv[1]));
    {

    }
    pthread_create(&tid, NULL, &routine, &(data));



    create_philo(atoi(argv[1]));
    return(0);
    
}