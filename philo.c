#include "philo.h"
void think(t_philo *philo)
{

}
void sleep(t_philo *philo)
{

}
void eat(t_philo *philo)
{

}
void routine(void *arg)
{   
    t_philo *data = (t_philo *)arg;
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

t_philo **create_philo(int philos_number)
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
    //pthread_create(&tid, NULL, &routine, &(data));
    add_fork(philos_number);
    return(philos);
}

int main(int argc, char **argv)
{
    pthread_t tid;
    t_philo **philos = create_philo(atoi(argv[1]));
    int i;

    i = 0;
    check_args_number(argc, argv);
    
    while(i < atoi(argv[1]))
    {
        pthread_create(&philos[i]->thread, NULL, routine, (void *)philos[i]);
        i++;
    }
    i = 0;
    while (i < atoi(argv[i]))
    {
        pthread_join(philos[i]->thread, NULL);
    }
    
    return(0);
    
}