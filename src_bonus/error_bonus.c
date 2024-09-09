#include "philo_bonus.h"
/*
int	lonely_philo_check(t_philo *philo)
{
	t_rules	*data;

	data = philo->data;
	if (philo->data->philo_num == 1)
	{
		print_lock("has taken a fork", philo);
		return (1);
	}
	if (philo->id % 2 == 0 || philo->id == data->philo_num)
		ft_sleep(data->time_sleep / 2, philo);
	return (0);
}*/

int	error_message(char *str)
{
	ft_putstr_fd(str, 1);
	return (1);
}

int	free_and_destroy(char *str, t_rules *data, int exit)
{
	if (str)
		ft_putstr_fd(str, 1);
	if (data->philo)
		free(data->philo);
	if (data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->death_lock != SEM_FAILED)
		sem_close(data->death_lock);
	if (data->meal_lock != SEM_FAILED)
		sem_close(data->meal_lock);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_mealcheck");
	return (exit);
}
