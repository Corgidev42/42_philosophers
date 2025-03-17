/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:49:36 by vbonnard          #+#    #+#             */
/*   Updated: 2025/03/17 15:00:51 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Analyse les arguments de la ligne de commande
 * et initialise les données de simulation.
 *
 * Cette fonction prend les arguments de la ligne de commande
 * et les utilise pour initialiser
 * les paramètres de simulation dans la structure t_data.
 * Les arguments attendus sont :
 * - argv[1] : Nombre de philosophes.
 * - argv[2] : Temps avant qu'un philosophe meure de faim (en millisecondes).
 * - argv[3] : Temps qu'un philosophe passe à manger (en millisecondes).
 * - argv[4] : Temps qu'un philosophe passe à dormir (en millisecondes).
 * - argv[5] : (Optionnel) Nombre de fois qu'un philosophe
 * doit manger avant la fin de la simulation.
 *
 * @param data Pointeur vers la structure t_data à initialiser.
 * @param argc Nombre d'arguments de la ligne de commande.
 * @param argv Tableau de chaînes de caractères
 * contenant les arguments de la ligne de commande.
 */
static void	parse_arguments(t_data *data, int argc, char **argv)
{
	data->num_philos = atoi(argv[1]);
	data->time_to_die = atol(argv[2]);
	data->time_to_eat = atol(argv[3]);
	data->time_to_sleep = atol(argv[4]);
	data->must_eat_count = -1;
	if (argc == 6)
		data->must_eat_count = atoi(argv[5]);
	data->simulation_stop = 0;
	data->start_time = get_timestamp();
}

/**
 * @brief Alloue la mémoire nécessaire pour les philosophes et les fourchettes.
 *
 * Cette fonction alloue de la mémoire
 * pour le tableau de philosophes et le tableau
 * de mutex pour les fourchettes
 * en fonction du nombre de philosophes spécifié dans
 * la structure de données.
 *
 * @param data Pointeur vers la structure de données contenant les informations
 * nécessaires pour l'initialisation.
 * @return Retourne 0 en cas de succès, ou 1 si une allocation échoue.
 */
static int	allocate_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	return (0);
}

/**
 * @brief Initialise les mutex pour les fourchettes
 * et autres opérations synchronisées.
 *
 * Cette fonction initialise les mutex pour
 * chaque fourchette utilisée par les philosophes,
 * ainsi que les mutex pour l'affichage et la simulation.
 *
 * @param data Pointeur vers la structure de données contenant
 * les informations sur les philosophes et les mutex.
 */
static void	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->simulation_mutex, NULL);
}

/**
 * @brief Initialise les philosophes avec des valeurs par défaut.
 *
 * Cette fonction initialise chaque philosophe dans le tableau `data->philos`.
 * Chaque philosophe reçoit un identifiant unique, le nombre de repas mangés
 * est initialisé à zéro, le temps du dernier repas est initialisé au temps de
 * début, et un pointeur vers la structure `data` est assigné.
 *
 * @param data Pointeur vers la structure de données contenant les informations
 *             sur les philosophes et les paramètres de simulation.
 */
static void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].data = data;
		i++;
	}
}

int	init_data(t_data *data, int argc, char **argv)
{
	parse_arguments(data, argc, argv);
	if (allocate_data(data))
		return (1);
	init_mutexes(data);
	init_philosophers(data);
	return (0);
}
