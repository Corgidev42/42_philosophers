#include "philo.h"

static void	precise_sleep(long duration)
{
	long	start;

	start = get_timestamp();
	while (get_timestamp() - start < duration)
		usleep(500);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		left;
	int		tmp;
	int		right;

	philo = (t_philo *)arg;
	data = philo->data;
	left = philo->id - 1;
	right = philo->id % data->num_philos; // indice du philosophe suivant
	if (data->num_philos == 1)
	{
		/* Cas particulier : un seul philosophe.
			Il prend la seule fourchette et finit par mourir de faim */
		pthread_mutex_lock(&data->forks[left]);
		print_action(data, philo->id, "has taken a fork");
		pthread_mutex_unlock(&data->forks[left]);
		precise_sleep(data->time_to_die);
		return (NULL);
	}
	/* Pour éviter les interblocages, on change l'ordre de prise des fourchettes
		selon que le numéro du philosophe est pair ou impair */
	if (philo->id % 2 == 0)
	{
		tmp = left;
		left = right;
		right = tmp;
	}
	while (1)
	{
		pthread_mutex_lock(&data->simulation_mutex);
		if (data->simulation_stop)
		{
			pthread_mutex_unlock(&data->simulation_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->simulation_mutex);
		/* Prise des fourchettes */
		pthread_mutex_lock(&data->forks[left]);
		print_action(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&data->forks[right]);
		print_action(data, philo->id, "has taken a fork");
		/* Phase d'alimentation */
		pthread_mutex_lock(&data->simulation_mutex);
		philo->last_meal = get_timestamp();
		pthread_mutex_unlock(&data->simulation_mutex);
		print_action(data, philo->id, "is eating");
		precise_sleep(data->time_to_eat);
		philo->meals_eaten++;
		/* Libération des fourchettes */
		pthread_mutex_unlock(&data->forks[left]);
		pthread_mutex_unlock(&data->forks[right]);
		/* Si le nombre minimum de repas est atteint, on sort de la boucle */
		if (data->must_eat_count != -1
			&& philo->meals_eaten >= data->must_eat_count)
			break ;
		/* Phase de sommeil */
		print_action(data, philo->id, "is sleeping");
		precise_sleep(data->time_to_sleep);
		/* Phase de réflexion */
		print_action(data, philo->id, "is thinking");
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		all_done;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->simulation_mutex);
			if (!data->simulation_stop && (get_timestamp()
					- data->philos[i].last_meal) > data->time_to_die)
			{
				print_action(data, data->philos[i].id, "died");
				data->simulation_stop = 1;
				pthread_mutex_unlock(&data->simulation_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->simulation_mutex);
			i++;
		}
		/* Si un nombre minimum de repas est imposé,
			on vérifie que tous les philosophes
			l'ont atteint pour arrêter la simulation */
		if (data->must_eat_count != -1)
		{
			all_done = 1;
			for (i = 0; i < data->num_philos; i++)
			{
				if (data->philos[i].meals_eaten < data->must_eat_count)
				{
					all_done = 0;
					break ;
				}
			}
			if (all_done)
			{
				pthread_mutex_lock(&data->simulation_mutex);
				data->simulation_stop = 1;
				pthread_mutex_unlock(&data->simulation_mutex);
				return (NULL);
			}
		}
		usleep(1000);
	}
	return (NULL);
}
