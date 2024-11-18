#include "philo.h"

int	lonely_philo_check(t_philo *philo)
{
	t_rules	*data;


	print_lock("is thinking", philo);
	data = philo->data;
	if (philo->data->philo_num == 1)
	{
		print_lock("has taken a fork", philo);
		return (1);
	}
	if (philo->id % 2 == 0 || philo->id == data->philo_num)
		ft_sleep(data->time_sleep / 2, philo);
	return (0);
}

int	error_message(char *str)
{
	ft_putstr_fd(str, 1);
	return (1);
}

int	free_and_destroy(char *str, t_rules *data, int exit)
{
	int	i;

	i = 0;
	if (str)
		ft_putstr_fd(str, 1);
	pthread_mutex_destroy(&data->death_lock);
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
