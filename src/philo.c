#include "../includes/philo.h"
#include <stdio.h> //DELETE

int	ft_atoi(const char *str, int *res)
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
		return(1);
	if (ft_atoi(av[2], &data->time_die))
		return(1);
	if (ft_atoi(av[3], &data->time_eat))
		return(1);
	if (ft_atoi(av[4], &data->time_sleep))
		return(1);
	if (ac == 6 && ft_atoi(av[5], &data->num_eat))
		return(1);
	if (ac == 5)
		data->num_eat = -1;
	data->all_full = 0;
	data->dead = 0;
	return (0);
}

void	test_init(t_rules *data)
{
	printf("Number of philos:%d\n", data->philo_num);
	printf("Time to die     :%d\n", data->time_die);
	printf("Time to eat     :%d\n", data->time_eat);
	printf("Time to sleep   :%d\n", data->time_sleep);
	printf("Number of meals :%d\n", data->num_eat);
}

int	philo_and_lock(t_rules *data)
{
	int i;

	i = -1;
	while (++i < data->philo_num)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals = 0;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) & data->philo_num];
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
	}
	if (pthread_mutex_init(&data->lock, NULL))
		return (1);
	return (0);
}

int	init_philo(t_rules *data)
{
	data->philo = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philo)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
	{
		free(data->philo);
		return (1);
	}
	if (philo_and_lock(data))
	{
		free(data->philo);
		free(data->forks);
		return(1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_rules data;

	if (check_args(ac, av, &data))
		return (1);
	if (init_philo(&data))
		return (1);
	test_init(&data); //testing
}
