#include "philo.h"

int	ft_sleep(long long wait, t_philo *philo)
{
	long long	start;
	long long	i;

	start = ft_time();
	i = 0;
	while (ft_time() - start < wait)
	{
		if (i % 100 == 0)
		{
			pthread_mutex_lock(&philo->data->death_lock);
			if (philo->data->dead)
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

int	print_lock(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->dead || philo->data->full)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return (1);
	}
	printf("%lld %d %s\n", ft_time() - philo->data->start_time,
		philo->id, str);
	pthread_mutex_unlock(&philo->data->death_lock);
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
	print_lock("is eating", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = ft_time();
	pthread_mutex_unlock(philo->meal_lock);
	ft_sleep(philo->data->time_eat, philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->meals++;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	*eat_sleep_think(void *strct)
{
	t_philo	*philo;
	t_rules	*data;	

	philo = (t_philo *)strct;
	data = philo->data;
	if (lonely_philo_check(philo))
		return (0);
	pthread_mutex_lock(&data->death_lock);
	while (data->full == 0 && data->dead == 0)
	{
		pthread_mutex_unlock(&data->death_lock);
		grab_forks(philo);
		ft_eat(philo);
		pthread_mutex_lock(&data->death_lock);
		if (data->full)
			break ;
		pthread_mutex_unlock(&data->death_lock);
		print_lock("is sleeping", philo);
		ft_sleep(philo->data->time_sleep, philo);
		print_lock("is thinking", philo);
		pthread_mutex_lock(&data->death_lock);
	}
	pthread_mutex_unlock(&data->death_lock);
	return (0);
}
