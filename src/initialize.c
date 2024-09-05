#include "../includes/philo.h"

int	check_args(int ac, char **av, t_rules *data)
{
	if (ac > 6 || ac < 5)
		return (1);
	if (ft_atoi(av[1], &data->philo_num))
		return (1);
	if (ft_atoi(av[2], &data->time_die))
		return (1);
	if (ft_atoi(av[3], &data->time_eat))
		return (1);
	if (ft_atoi(av[4], &data->time_sleep))
		return (1);
	if (ac == 6 && ft_atoi(av[5], &data->num_eat))
		return (1);
	if (ac == 5)
		data->num_eat = -1;
	data->dead = 0;
	data->full = 0;
	data->start_time = ft_time();
	return (0);
}

static int	init_locks(t_rules *data)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			return (1);
		}
	}
	while (++j < data->philo_num)
	{
		if (pthread_mutex_init(&data->meal_lock[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			while (--j >= 0)
				pthread_mutex_destroy(&data->meal_lock[i]);
			return (1);
		}
	}
	return (0);
}

static int	philo_and_lock(t_rules *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals = 0;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->philo_num];
		data->philo[i].data = data;
		data->philo[i].last_meal = 0;
		data->philo[i].meal_lock = &data->meal_lock[i];
	}
	if (pthread_mutex_init(&data->death_lock, NULL))
		return (1);
	if (init_locks(data))
	{
		pthread_mutex_destroy(&data->death_lock);
		return (1);
	}
	return (0);
}

int	init_philo(t_rules *data)
{
	data->philo = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philo)
		return (error_message("Failed to malloc\n"));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
	{
		free(data->philo);
		return (error_message("Failed to malloc\n"));
	}
	data->meal_lock = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->meal_lock)
	{
		free(data->philo);
		free(data->forks);
		return (error_message("Failed to malloc\n"));
	}
	if (philo_and_lock(data))
	{
		free(data->philo);
		free(data->forks);
		free(data->meal_lock);
		return (error_message("Failed to create mutex\n"));
	}
	return (0);
}
