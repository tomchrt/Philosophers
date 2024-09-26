#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>


int	main(int argc, char **argv)
{
	t_philo	**philos;
	int		i;
	int		philos_number;

	if (argc != 5)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep\n", argv[0]);
		return (1);
	}
	philos_number = atoi(argv[1]);
	philos = create_philo(philos_number, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
	i = 0;
	while (i < philos_number)
	{
		pthread_create(&philos[i]->thread, NULL, routine, (void *)philos[i]);
		i++;
	}
	i = 0;
	while (i < philos_number)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
	// Ajouter ici la libération de la mémoire
	return (0);
}