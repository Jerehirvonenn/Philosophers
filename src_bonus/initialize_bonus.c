#include "philo_bonus.h"

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
		data->num_eat = 0;
	data->dead = 0;
	data->full = 0;
	data->start_time = ft_time();
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
		data->philo[i].data = data;
		data->philo[i].last_meal = 0;
	}
	return (0);
}

static int	init_sems(t_rules *data)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_death");
	sem_unlink("/philo_meal");
	sem_unlink("/philo_full");
	data->forks = sem_open("/philo_forks", O_CREAT, S_IRWXU, data->philo_num);
	data->death_lock = sem_open("/philo_death", O_CREAT, S_IRWXU, 1);
	data->meal_lock = sem_open("/philo_meal", O_CREAT, S_IRWXU, 1);
	data->full_lock = sem_open("/philo_full", O_CREAT, S_IRWXU, 0);
	if (data->forks == SEM_FAILED || data->death_lock == SEM_FAILED
		|| data->meal_lock == SEM_FAILED || data->full_lock == SEM_FAILED)
	{
		//could maybe use free and deastroy func
		if (data->forks != SEM_FAILED)
			sem_close(data->forks);
		if (data->death_lock != SEM_FAILED)
			sem_close(data->death_lock);
		if (data->meal_lock != SEM_FAILED)
			sem_close(data->meal_lock);
		if (data->full_lock != SEM_FAILED)
			sem_close(data->full_lock);
		sem_unlink("/philo_forks");
		sem_unlink("/philo_death");
		sem_unlink("/philo_meal");
		sem_unlink("/philo_full");
		return (1);
	}
	return (0);
}

int	init_philo(t_rules *data)
{
	data->philo = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philo)
		return (error_message("Failed to malloc\n"));
	if (init_sems(data))
	{
		free(data->philo);
		return (error_message("Failed to create semaphore"));
	}
	philo_and_lock(data);
	return (0);
}
