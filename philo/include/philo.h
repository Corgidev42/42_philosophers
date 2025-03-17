/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:48:15 by vbonnard          #+#    #+#             */
/*   Updated: 2025/03/17 12:06:44 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include "libft.h"
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
	int					must_eat_count; // -1 si non spécifié
	int					simulation_stop;
	long				start_time;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		simulation_mutex;
};

long					get_timestamp(void);
long					get_time_since(long start);
void					print_action(t_data *data, int id, const char *action);
void					*philosopher_routine(void *arg);
void					*monitor_routine(void *arg);
int						init_data(t_data *data, int argc, char **argv);
void					cleanup(t_data *data);

#endif
