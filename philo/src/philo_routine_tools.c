/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:49:42 by vbonnard          #+#    #+#             */
/*   Updated: 2025/03/17 14:57:33 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Fonction auxiliaire pour le cas d’un seul philosophe */
void	handle_single_philo(t_philo *philo, int fork_index)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[fork_index]);
	print_action(data, philo->id, "has taken a fork");
	pthread_mutex_unlock(&data->forks[fork_index]);
	precise_sleep(data->time_to_die);
}

/* Réorganise l’ordre de prise des fourchettes pour éviter les deadlocks */
void	adjust_fork_order(t_philo *philo, int *left, int *right)
{
	int	tmp;

	if (philo->id % 2 == 0 || philo->data->num_philos % 2 == 1)
	{
		tmp = *left;
		*left = *right;
		*right = tmp;
	}
}

/* Vérifie si la simulation doit s'arrêter */
int	simulation_stopped(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->simulation_mutex);
	stop = data->simulation_stop;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (stop);
}

/* Prend les deux fourchettes et affiche les messages correspondants */
void	take_forks(t_philo *philo, int left, int right)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[left]);
	print_action(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&data->forks[right]);
	print_action(data, philo->id, "has taken a fork");
}

/* Libère les mutex des fourchettes */
void	release_forks(t_data *data, int left, int right)
{
	pthread_mutex_unlock(&data->forks[left]);
	pthread_mutex_unlock(&data->forks[right]);
}
