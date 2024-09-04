#include "../includes/philo.h"

int	error_message(char *str)
{
	ft_putstr_fd(str, 1);
	return(1);
}

int	free_and_destroy(char *str, t_rules *data, int exit)
{
	int i;

	i = 0;

	if (str)
		ft_putstr_fd(str, 1);
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->print_lock);
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
	return (exit);
}
