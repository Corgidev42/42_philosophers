/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:56:58 by vbonnard          #+#    #+#             */
/*   Updated: 2025/03/17 17:01:08 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nb;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * sign);
}


int	perform_cycle(t_philo *philo, int left, int right)
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(1000);
	if (simulation_stopped(data))
		return (1);
	print_action(data, philo->id, "is thinking");
	take_forks(philo, left, right);
	pthread_mutex_lock(&data->simulation_mutex);
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&data->simulation_mutex);
	print_action(data, philo->id, "is eating");
	precise_sleep(data->time_to_eat);
	philo->meals_eaten++;
	release_forks(data, left, right);
	if (data->must_eat_count != -1
		&& philo->meals_eaten >= data->must_eat_count)
		return (1);
	print_action(data, philo->id, "is sleeping");
	precise_sleep(data->time_to_sleep);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		left;
	int		right;

	philo = (t_philo *)arg;
	data = philo->data;
	left = philo->id - 1;
	right = philo->id % data->num_philos;
	if (data->num_philos == 1)
	{
		handle_single_philo(philo, left);
		return (NULL);
	}
	adjust_fork_order(philo, &left, &right);
	while (!perform_cycle(philo, left, right))
		;
	return (NULL);
}
