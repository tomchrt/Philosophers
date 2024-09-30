#include "philo.h"

long long	current_timestamp(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

long long	get_elapsed_time(t_philo *philo)
{
	return (current_timestamp() - philo->start_time);
}

void	ft_usleep(int ms)
{
	long long	start;
	long long	end;

	start = current_timestamp();
	end = start + ms;
	while (current_timestamp() < end)
	{
		if (end - current_timestamp() > 1)
			usleep(100);
		else
			usleep(1);
	}
}

void	safe_print(t_philo *philo, const char *format, long long time, int rank)
{
	pthread_mutex_lock(philo->death_mutex);
	printf(format, time, rank);
	pthread_mutex_unlock(philo->death_mutex);
}

int	try_to_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork->mutex);
	pthread_mutex_lock(philo->right_fork->mutex);
	if (philo->left_fork->value == 0 && philo->right_fork->value == 0)
	{
		philo->left_fork->value = 1;
		philo->right_fork->value = 1;
		safe_print(philo, "%lld Philosopher %d has taken a fork\n",
			get_elapsed_time(philo), philo->rank);
		safe_print(philo, "%lld Philosopher %d has taken a fork\n",
			get_elapsed_time(philo), philo->rank);
		return (1);
	}
	pthread_mutex_unlock(philo->left_fork->mutex);
	pthread_mutex_unlock(philo->right_fork->mutex);
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	philo->state = EATING;
	philo->last_meal_time = get_elapsed_time(philo);
	pthread_mutex_unlock(philo->death_mutex);
	safe_print(philo, "%lld Philosopher %d is eating\n",
		get_elapsed_time(philo), philo->rank);
	philo->meal_count++;
	ft_usleep(philo->time_to_eat);
	philo->left_fork->value = 0;
	philo->right_fork->value = 0;
	pthread_mutex_unlock(philo->left_fork->mutex);
	pthread_mutex_unlock(philo->right_fork->mutex);

	// DEBUG: Afficher les temps et repas après avoir mangé
	printf("Philosopher %d ate. Last meal time: %lld, Time to die: %d\n", 
		philo->rank, philo->last_meal_time, philo->time_to_die);
}

void	think(t_philo *philo)
{
	philo->state = THINKING;
	safe_print(philo, "%lld Philosopher %d is thinking\n",
		get_elapsed_time(philo), philo->rank);
}

void	sleeping(t_philo *philo)
{
	philo->state = SLEEPING;
	safe_print(philo, "%lld Philosopher %d is sleeping\n",
		get_elapsed_time(philo), philo->rank);
	ft_usleep(philo->time_to_sleep);

	// DEBUG: Afficher les états pendant le sommeil
	printf("Philosopher %d is sleeping. Time to sleep: %d ms\n", 
		philo->rank, philo->time_to_sleep);
}
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->death_mutex);
		long long time_since_last_meal = get_elapsed_time(philo) - philo->last_meal_time;
		if (time_since_last_meal >= philo->time_to_die)
		{
            printf("OUI");
			philo->state = DEAD;
			safe_print(philo, "%lld Philosopher %d died\n",
				get_elapsed_time(philo), philo->rank);
			pthread_mutex_unlock(philo->death_mutex);
			return (NULL);  
		}
		pthread_mutex_unlock(philo->death_mutex);

		if (philo->state == THINKING && try_to_take_forks(philo))
			eat(philo);
		else if (philo->state == EATING)
			sleeping(philo);
		else if (philo->state == SLEEPING)
			think(philo);

		usleep(100);  
	}
	return (NULL);
}


void	add_forks(t_philo **philos, int philos_number)
{
	int		i;
	t_fork	**forks;

	i = 0;
	forks = malloc(sizeof(t_fork *) * philos_number);
	while (i < philos_number)
	{
		forks[i] = malloc(sizeof(t_fork));
		forks[i]->mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(forks[i]->mutex, NULL);
		forks[i]->value = 0;
		i++;
	}
	i = 0;
	while (i < philos_number)
	{
		philos[i]->left_fork = forks[i];
		philos[i]->right_fork = forks[(i + 1) % philos_number];
		i++;
	}
}

t_philo	**create_philo(int philos_number, int time_to_die, int time_to_eat,
	int time_to_sleep)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo *) * philos_number);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < philos_number)
	{
		philos[i] = malloc(sizeof(t_philo));
		philos[i]->rank = i + 1;
		philos[i]->state = THINKING;
		philos[i]->time_to_eat = time_to_eat;
		philos[i]->time_to_sleep = time_to_sleep;
		philos[i]->time_to_die = time_to_die;
		philos[i]->start_time = current_timestamp();
		philos[i]->last_meal_time = philos[i] ->start_time;
		philos[i]->meal_count = 0;
		philos[i]->death_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philos[i]->death_mutex, NULL);
		if (i != philos_number - 1)
			philos[i]->next = philos[i + 1];
		else
			philos[i]->next = philos[0];
		i++;
	}
	add_forks(philos, philos_number);
	return (philos);
}

int	main(int argc, char **argv)
{
	t_philo	**philos;
	int		i;
	int		num_philos;
	int		all_alive;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat \
			time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	num_philos = atoi(argv[1]);
	philos = create_philo(num_philos, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
	all_alive = 1;
	i = 0;
	while (i < num_philos)
	{
		philos[i]->start_time = current_timestamp();
		pthread_create(&philos[i]->thread, NULL, routine, (void *)philos[i]);
		i++;
	}
	while (all_alive)
	{
		i = 0;
		while (i < num_philos)
		{
			pthread_mutex_lock(philos[i]->death_mutex);
			if (philos[i]->state == DEAD)
			{
				all_alive = 0;
				pthread_mutex_unlock(philos[i]->death_mutex);
				break ;
			}
			pthread_mutex_unlock(philos[i]->death_mutex);
			i++;
		}
		usleep(1000);
	}
	i = 0;
	while (i < num_philos)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_destroy(philos[i]->death_mutex);
		free(philos[i]->death_mutex);
		pthread_mutex_destroy(philos[i]->left_fork->mutex);
		free(philos[i]->left_fork->mutex);
		free(philos[i]->left_fork);
		free(philos[i]);
		i++;
	}
	free(philos);
	return (0);
}