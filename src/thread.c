#include "../includes/philo.h"

int	start_threads(t_rules *data)
{
	int			i;
	long long	time;

	i = -1;
	time = ft_time();
	data->start_time = time;
	while (++i < data->philo_num)
	{
		data->philo[i].last_meal = time;
		if (pthread_create(&(data->philo[i].thread),
				NULL, &eat_sleep_think, &data->philo[i]))
		{
			while (--i >= 0)
				pthread_join(data->philo[i].thread, NULL);
			return (1);
		}
	}
	return (0);
}

int	join_threads(t_rules *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		if (pthread_join(data->philo[i].thread, NULL))
			return (1);
	return (0);
}
