#include "philo.h"

static inline int	check_death(int i, t_rules *data)
{
	pthread_mutex_lock(&data->meal_lock[i]);
	if (ft_time() - data->philo[i].last_meal >= data->time_die)
	{
		pthread_mutex_lock(&data->death_lock);
		data->dead = 1;
		printf("%lld %d %s\n", ft_time() - data->start_time, i + 1, "died");
		pthread_mutex_unlock(&data->death_lock);
		pthread_mutex_unlock(&data->meal_lock[i]);
		return (1);
	}
	pthread_mutex_unlock(&data->meal_lock[i]);
	return (0);
}

static inline int	check_full(t_rules *data)
{
	int	i;

	i = 0;
	while (data->num_eat != -1 && i < data->philo_num)
	{
		pthread_mutex_lock(&data->meal_lock[i]);
		if (data->philo[i].meals >= data->num_eat)
			i++;
		else
		{
			pthread_mutex_unlock(&data->meal_lock[i]);
			break ;
		}
		pthread_mutex_unlock(&data->meal_lock[i - 1]);
	}
	return (i);
}

void	monitor(t_rules *data)
{
	int	i;

	i = -1;
	while (data->full == 0)
	{
		while (++i < data->philo_num)
		{
			if (check_death(i, data))
				return ;
		}
		i = check_full(data);
		if (i == data->philo_num)
		{
			pthread_mutex_lock(&data->death_lock);
			data->full = 1;
			pthread_mutex_unlock(&data->death_lock);
		}
		i = -1;
	}
}

int	main(int ac, char **av)
{
	t_rules	data;

	if (check_args(ac, av, &data))
		return (error_message("Invalid input\n"));
	if (init_philo(&data))
		return (1);
	if (start_threads(&data))
		return (free_and_destroy("Failed to create threads\n", &data, 1));
	monitor(&data);
	join_threads(&data);
	free_and_destroy(NULL, &data, 0);
}
