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
		printf("%ld %d %s\n", get_time_since(data->start_time), id, action);
	pthread_mutex_unlock(&data->print_mutex);
}
