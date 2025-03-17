/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:49:38 by vbonnard          #+#    #+#             */
/*   Updated: 2025/03/17 15:03:05 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Vérifie les arguments passés au programme.
 *
 * Cette fonction vérifie si
 * le nombre d'arguments passés au programme est correct.
 * Le programme doit recevoir soit 5 soit 6 arguments.
 *
 * @param argc Le nombre d'arguments passés au programme.
 * @param argv Un tableau de chaînes de caractères représentant les arguments.
 * @return Retourne 0 si le nombre d'arguments est correct,
 * sinon retourne 1 et affiche un message d'utilisation.
 */
static int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		ft_printf("Usage: %s number_of_philosophers \
			time_to_die time_to_eat time_to_sleep  \
			[number_of_times_each_philosopher_must_eat]\n",
			argv[0]);
		return (1);
	}
	return (0);
}

/**
 * @brief Crée les threads pour chaque philosophe.
 *
 * Cette fonction initialise et crée un thread pour chaque philosophe
 * en utilisant la fonction pthread_create. Chaque thread exécute la routine
 * du philosophe.
 *
 * @param data Pointeur vers la structure de données contenant les informations
 * nécessaires pour créer les threads des philosophes.
 *
 * @return Retourne 0 en cas de succès,
 * ou 1 en cas d'échec de la création d'un thread.
 */
static int	create_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philosopher_routine,
				&data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Crée un thread de surveillance.
 *
 * Cette fonction initialise et crée un thread de surveillance qui exécutera
 * la routine de surveillance spécifiée.
 *
 * @param data Un pointeur vers les données partagées entre les threads.
 * @param monitor Un pointeur vers le thread de surveillance à créer.
 * @return Retourne 0 en cas de succès,
 * 1 en cas d'échec de la création du thread.
 */
static int	create_monitor_thread(t_data *data, pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, monitor_routine, data) != 0)
		return (1);
	return (0);
}

/**
 * @brief Rejoint tous les threads des philosophes
 * et le thread de surveillance.
 *
 * Cette fonction attend que tous les threads des philosophes se terminent
 * en appelant pthread_join sur chacun d'eux. Ensuite, elle attend également
 * la fin du thread de surveillance.
 *
 * @param data Pointeur vers la structure de données contenant les informations
 *             sur les philosophes et les threads.
 * @param monitor Thread de surveillance à rejoindre.
 */
static void	join_all_threads(t_data *data, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;

	if (check_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
	{
		ft_printf("Error initializing data\n");
		return (1);
	}
	if (create_philosopher_threads(&data))
	{
		ft_printf("Error creating thread\n");
		return (1);
	}
	if (create_monitor_thread(&data, &monitor))
	{
		ft_printf("Error creating monitor thread\n");
		return (1);
	}
	join_all_threads(&data, monitor);
	cleanup(&data);
	return (0);
}
