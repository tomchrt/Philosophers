#include "philo.h"
//faire des setter et des getter pour securiser
ft_usleep(int usleep_time, t_philo *philo)
{
    while(1)
    {
        usleep(usleep_time * 1000);
        if(philo->state == DEAD)
            break;
    }
}
 void think(t_philo *philo)
{
    printf("Philosopher is thinking..");
    //ft_usleep(ph)
}
 void sleep(t_philo *philo)
{
    printf("Philosopher is sleeping..");  
    ft_usleep(philo->time_to_sleep, philo);

}
void eat(t_philo *philo)
{
    printf("Philosopher is eating..");
    ft_usleep(philo->time_to_eat, philo);
}
void routine(void *arg)
{   
    t_philo *data = (t_philo *)arg;
  
    while(1)
    {   
        eat(data);
        think(data);
        sleep(data);
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

t_philo **create_philo(int philos_number, int time_to_die, int time_to_eat, int time_to_sleep)
{
    t_philo **philos;
    int i;

    i = 0;
    philos = malloc(sizeof(t_philo *) * philos_number);
    if(!philos)
        return(NULL);
    while(i < philos_number)
    {
        
        philos[i] = malloc(sizeof (t_philo));
        philos[i]->rank = i +1;
        philos[i]->state = THINKING;
        philos[i]->time_to_eat = time_to_eat;
        philos[i]->time_to_sleep = time_to_sleep;
        philos[i]->time_to_die = time_to_die;
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
    t_philo **philos = create_philo(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    int i;

    i = 0;
    check_args_number(argc, argv);
    
    while(i < atoi(argv[1]))
    {
        pthread_create(&philos[i]->thread, NULL, (void*)routine, (void *)philos[i]);
        i++;
    }
    i = 0;
    while (i < atoi(argv[i]))
    {
        pthread_join(philos[i]->thread, NULL);
        i++;
    }
    
    return(0);
    
}