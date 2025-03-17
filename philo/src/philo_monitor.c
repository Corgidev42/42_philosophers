/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:50:46 by vbonnard          #+#    #+#             */
/*   Updated: 2025/03/17 16:52:50 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Vérifie si un philosophe est mort.
 *
 * Cette fonction parcourt tous les philosophes
 * et vérifie si l'un d'eux est mort
 * en comparant le temps écoulé depuis
 * son dernier repas avec le temps limite pour mourir.
 * Si un philosophe est trouvé mort,
 * la fonction imprime l'action "died" et arrête la simulation.
 *
 * @param data Pointeur vers la structure de données contenant
 * les informations de la simulation.
 * @return 1 si un philosophe est mort, 0 sinon.
 */
static int	check_death(t_data *data)
{
	int	i;

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
			return (1);
		}
		pthread_mutex_unlock(&data->simulation_mutex);
		i++;
	}
	return (0);
}

/**
 * @brief Vérifie si tous les philosophes ont terminé de manger.
 *
 * Cette fonction vérifie si chaque philosophe a mangé le nombre de repas requis
 * (défini par `must_eat_count`). Si `must_eat_count` est défini à -1,
	la fonction
 * retourne immédiatement 0, indiquant que la simulation ne doit pas s'arrêter.
 * Si tous les philosophes ont mangé le nombre de repas requis, la fonction
 * verrouille le mutex de simulation,
	met à jour l'état de l'arrêt de la simulation
 * et déverrouille le mutex.
 *
 * @param data Pointeur vers la structure de données contenant les informations
 *             sur la simulation et les philosophes.
 * @return int 1 si tous les philosophes ont terminé de manger, 0 sinon.
 */
static int	check_all_done(t_data *data)
{
	int	i;

	i = 0;
	if (data->must_eat_count == -1)
		return (0);
	while (i < data->num_philos)
	{
		// printf("%d\n", data->philos[i].meals_eaten);
		if (data->philos[i].meals_eaten < data->must_eat_count)
			return (0);
		i++;
	}
	pthread_mutex_lock(&data->simulation_mutex);
	data->simulation_stop = 1;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data))
			return (NULL);
		if (check_all_done(data))
			return (NULL);
		precise_sleep(1);
	}
	return (NULL);
}
