/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:49:45 by vbonnard          #+#    #+#             */
/*   Updated: 2025/03/17 15:21:42 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

long	get_time_since(long start)
{
	return (get_timestamp() - start);
}

void	print_action(t_data *data, int id, const char *action)
{
	pthread_mutex_lock(&data->print_mutex);
	if (!data->simulation_stop)
		ft_printf("%d %d %s\n", get_time_since(data->start_time), id, action);
	pthread_mutex_unlock(&data->print_mutex);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->simulation_mutex);
	free(data->forks);
	free(data->philos);
}

void	precise_sleep(long duration)
{
	long	start;

	start = get_timestamp();
	while (get_timestamp() - start < duration)
		usleep(1000);
}
