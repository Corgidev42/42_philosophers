/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:48:15 by vbonnard          #+#    #+#             */
/*   Updated: 2025/03/17 15:12:32 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long				last_meal;
	pthread_t			thread;
	t_data				*data;
}						t_philo;

struct					s_data
{
	int					num_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					must_eat_count;
	int					simulation_stop;
	long				start_time;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		simulation_mutex;
};

// --------------------- philo_utils.c ------------------------------------- //

/**
 * @brief Retourne l'horodatage actuel en millisecondes.
 *

	* Cette fonction utilise gettimeofday pour
	obtenir l'heure actuelle et la convertit en millisecondes.
 *
 * @return long L'horodatage en millisecondes.
 */
long					get_timestamp(void);

/**
 * @brief Calcule le temps écoulé depuis un instant donné.
 *

	* Cette fonction retourne la différence entre
	l'horodatage actuel et l'instant de départ fourni.
 *
 * @param start Instant de départ en millisecondes.
 * @return long Temps écoulé en millisecondes depuis start.
 */
long					get_time_since(long start);

/**
 * @brief Affiche une action effectuée
 * par un philosophe de manière thread-safe.
 *

	* La fonction verrouille le mutex d'affichage
	pour éviter les chevauchements de messages.
 * Si la simulation est stoppée, aucun message n'est affiché.
 *
 * @param data Pointeur vers la structure de données globale.
 * @param id Identifiant du philosophe.
 * @param action Description de l'action effectuée.
 */
void					print_action(t_data *data, int id, const char *action);

/**
 * @brief Libère les ressources allouées et détruit les mutex.
 *
 * Cette fonction détruit tous les mutex associés aux fourchettes,
	au mutex d'affichage
 * et au mutex de simulation,
	puis libère la mémoire allouée pour les fourchettes et les philosophes.
 *
 * @param data Pointeur vers la structure de données globale.
 */
void					cleanup(t_data *data);

/**
 * @brief Effectue une pause précise pendant une durée donnée.
 *

	* La fonction utilise une boucle pour vérifier
	le temps écoulé et effectue un usleep de 1000 microsecondes
 * jusqu'à atteindre la durée spécifiée.
 *
 * @param duration Durée de la pause en millisecondes.
 */
void					precise_sleep(long duration);

// --------------------- philo_monitor.c -------------------------------------
	//

/**
 * @brief Routine de surveillance pour les philosophes.
 *

	* Cette fonction est exécutée dans un thread
	séparé et surveille l'état des philosophes.

	* Elle vérifie périodiquement si un philosophe
	est mort ou si tous les philosophes ont terminé.
 * Si l'une de ces conditions est remplie,
	la fonction retourne NULL pour terminer le thread.
 *
 * @param arg Pointeur vers les données partagées (de type t_data).
 * @return NULL lorsque la surveillance est terminée.
 */
void					*monitor_routine(void *arg);

// --------------------- init.c ------------------------------------- //

/**
 * @brief Initialise les données nécessaires
 *  pour le programme des philosophes.
 *
 * Cette fonction analyse les arguments de la ligne de commande,
	alloue la mémoire
 * nécessaire pour les données,
	initialise les mutex et les structures des philosophes.
 *

	* @param data Un pointeur vers la structure
	t_data qui contient toutes les données du programme.
 * @param argc Le nombre d'arguments passés à la ligne de commande.

	* @param argv Un tableau de chaînes de caractères
	contenant les arguments de la ligne de commande.
 * @return Retourne 0 en cas de succès,
	ou 1 en cas d'échec de l'allocation de mémoire.
 */
int						init_data(t_data *data, int argc, char **argv);

// --------------------- philo_routine_tools.c ----------------------------- //

/**
 * @brief Gère le cas particulier d’un seul philosophe.
 *
 * Si un seul philosophe est présent, il prend la seule fourchette disponible,
	affiche
 * le message correspondant et attend jusqu’à ce qu’il meure de faim.
 *
 * @param philo Pointeur vers le philosophe.
 * @param fork_index Index de la fourchette à utiliser.
 */
void					handle_single_philo(t_philo *philo, int fork_index);

/**

	* @brief Réorganise l’ordre de prise des
	fourchettes pour éviter les interblocages.
 *

	* Cette fonction échange les indices
	des fourchettes gauche et droite selon le numéro du
 * philosophe et le nombre total de philosophes
 afin de prévenir les deadlocks.
 *
 * @param philo Pointeur vers le philosophe.
 * @param left Pointeur vers l'indice de la fourchette gauche.
 * @param right Pointeur vers l'indice de la fourchette droite.
 */
void					adjust_fork_order(t_philo *philo, int *left,
							int *right);

/**
 * @brief Vérifie si la simulation doit être arrêtée.
 *

	* Cette fonction verrouille le mutex de
	simulation pour accéder à l'état de la simulation.
 *
 * @param data Pointeur vers la structure de données globale.
 * @return int Renvoie 1 si la simulation doit s'arrêter, 0 sinon.
 */
int						simulation_stopped(t_data *data);

/**
 * @brief Permet à un philosophe de prendre les deux fourchettes.
 *

	* Cette fonction verrouille les mutex
	correspondant aux fourchettes gauche et droite et
 * affiche le message indiquant que le philosophe a pris une fourchette.
 *
 * @param philo Pointeur vers le philosophe.
 * @param left Indice de la fourchette gauche.
 * @param right Indice de la fourchette droite.
 */
void					take_forks(t_philo *philo, int left, int right);

/**
 * @brief Libère les mutex associés aux fourchettes.
 *
 * Déverrouille les mutex correspondant aux fourchettes gauche et droite.
 *
 * @param data Pointeur vers la structure de données globale.
 * @param left Indice de la fourchette gauche.
 * @param right Indice de la fourchette droite.
 */
void					release_forks(t_data *data, int left, int right);

// --------------------- philo_routine.c ----------------------------------- //

/**
 * @brief Effectue un cycle complet d’actions pour un philosophe.
 *
 * La fonction réalise les étapes suivantes :
 * - Pour les philosophes pairs, une attente courte (usleep de 1000 µs).
 * - Vérification si la simulation doit être arrêtée via simulation_stopped.
 * - Affichage de l’état "is thinking".
 * - Prise des deux fourchettes grâce à take_forks.
 * - Mise à jour du temps du dernier repas (protégé par un mutex).
 *
	- Affichage de l’état "is eating" suivi d’une
	attente pendant le temps d’alimentation.
 * - Incrémentation du compteur de repas consommés.
 * - Libération des fourchettes avec release_forks.
 * - Si un nombre minimum de repas est défini et atteint,
	la fonction renvoie 1 pour indiquer l’arrêt.
 * - Affichage de l’état "is sleeping" et attente pendant le temps de sommeil.
 *
 * @param philo Pointeur vers la structure du philosophe.
 * @param left Indice de la fourchette gauche.
 * @param right Indice de la fourchette droite.
 * @return int Retourne 1 si la simulation doit être arrêtée, 0 sinon.
 */
int						perform_cycle(t_philo *philo, int left, int right);

/**
 * @brief Routine principale exécutée par chaque philosophe.
 *
 * Cette fonction représente la vie d’un philosophe dans la simulation :
 * - Récupération des données du philosophe.
 * - Détermination des indices des fourchettes gauche et droite.
 *
	- Traitement particulier du cas d’un seul philosophe
	(appel à handle_single_philo).
 *
	- Ajustement de l’ordre de prise des fourchettes
	(pour éviter les deadlocks) via adjust_fork_order.
 *
	- Exécution en boucle du cycle d’actions
	(perform_cycle) jusqu’à l’arrêt de la simulation.
 *
 * @param arg Pointeur générique vers la structure t_philo du philosophe.
 * @return void* Retourne NULL à la fin de la routine.
 */
void					*philosopher_routine(void *arg);

#endif
