#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	data->num_philos = atoi(argv[1]);
	data->time_to_die = atol(argv[2]);
	data->time_to_eat = atol(argv[3]);
	data->time_to_sleep = atol(argv[4]);
	data->must_eat_count = -1;
	if (argc == 6)
		data->must_eat_count = atoi(argv[5]);
	data->simulation_stop = 0;
	data->start_time = get_timestamp();
	/* Allocation de la mémoire pour les philosophes */
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (1);
	/* Allocation de la mémoire pour les mutex des fourchettes */
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	/* Initialisation des mutex */
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->simulation_mutex, NULL);
	/* Initialisation des philosophes */
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	for (i = 0; i < data->num_philos; i++)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->simulation_mutex);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;
	int			i;

	if (argc != 5 && argc != 6)
	{
		ft_printf("Usage: %s number_of_philosophers \
			time_to_die time_to_eat time_to_sleep \
			[number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	if (init_data(&data, argc, argv))
	{
		ft_printf("Error initializing data\n");
		return (1);
	}
	/* Création des threads pour chaque philosophe */
	i = 0;
	while (i < data.num_philos)
	{
		if (pthread_create(&data.philos[i].thread, NULL, philosopher_routine,
				&data.philos[i]) != 0)
		{
			ft_printf("Error creating thread\n");
			return (1);
		}
		i++;
	}
	/* Création du thread de surveillance */
	if (pthread_create(&monitor, NULL, monitor_routine, &data) != 0)
	{
		ft_printf("Error creating monitor thread\n");
		return (1);
	}
	/* Attente de la fin des threads philosophes */
	i = 0;
	while (i < data.num_philos)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	cleanup(&data);
	return (0);
}
