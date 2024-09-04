#include "../includes/philo.h"

#include <stdio.h> //DEL
static int	ft_sleep(long long wait, t_philo *philo)
{
	long long	start;
	long long 	i;

	start = ft_time();
	i = 0;
	while (ft_time() - start < wait)
	{
		if (i % 100 == 0)
		{
			pthread_mutex_lock(&philo->data->death_lock);
			if (philo->data->dead_full)
			{
				pthread_mutex_unlock(&philo->data->death_lock);
				return (1);
			}
			pthread_mutex_unlock(&philo->data->death_lock);
		}
		i++;
		usleep(500);
	}
	return (0);
}

static int	print_lock(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->dead_full)
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		pthread_mutex_unlock(&philo->data->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	printf("%lld ", ft_time() - philo->data->start_time);
	printf("%d ", philo->id);
	printf("%s\n", str);
	pthread_mutex_unlock(&philo->data->print_lock);
	return (0);
}

static int	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_lock("has taken a fork", philo);
	pthread_mutex_lock(philo->right_fork);
	print_lock("has taken a fork", philo);
	return (0);
}

static int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->meals++;
	philo->last_meal = ft_time();
	pthread_mutex_unlock(philo->meal_lock);
	print_lock("is eating", philo);
	ft_sleep(philo->data->time_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

static int	ft_sleep_think(t_philo *philo)
{
	print_lock("is sleeping", philo);
	ft_sleep(philo->data->time_sleep, philo);
	print_lock("is thinking", philo);
	return (0);
}

void	*eat_sleep_think(void *strct)
{
	t_philo	*philo;
	t_rules	*data;	

	philo = (t_philo *)strct;
	data = philo->data;
	//while all not eaten and no one dead
	pthread_mutex_lock(&data->death_lock);
	while (data->dead_full == 0)
	{
		pthread_mutex_unlock(&data->death_lock);
		grab_forks(philo);
		ft_eat(philo);
		ft_sleep_think(philo);
		pthread_mutex_lock(&data->death_lock);
	}
	pthread_mutex_unlock(&data->death_lock);
	return (0);
}
