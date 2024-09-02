#include "../includes/philo.h"

static int	ft_atoi(const char *str, int *res)
{
	long long int	result;
	int				i;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			return (1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (result > 2147483648)
			return (1);
	}
	if (str[i] || result <= 0)
		return (1);
	*res = result;
	return (0);
}

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
	data->dead_full = 0;
	data->start_time = ft_time();
	return (0);
}

static int	init_locks(t_rules *data)
{
	if (pthread_mutex_init(&data->lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->print_lock, NULL))
	{
		pthread_mutex_destroy(&data->lock);
		return (1);
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
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			return (1);
		}
	}
	if (init_locks(data))
	{
		while (--i >= 0)
			pthread_mutex_destroy(&data->forks[i]);
		return (1);
	}
	return (0);
}

int	init_philo(t_rules *data)
{
	data->philo = NULL;
	data->forks = NULL;
	data->philo = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philo)
		return (error_message("Failed to malloc\n"));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
	{
		free(data->philo);
		return (error_message("Failed to malloc\n"));
	}
	if (philo_and_lock(data))
	{
		free(data->philo);
		free(data->forks);
		return (error_message("Failed to create mutex\n"));
	}
	return (0);
}
