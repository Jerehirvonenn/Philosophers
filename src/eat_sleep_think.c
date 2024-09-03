#include "../includes/philo.h"

#include <stdio.h>
static int	ft_sleep(long long wait, t_philo *philo)
{
	long long	start;
	long long 	i;

	start = ft_time();
	i = 0;
	while (get_time() - start > wait)
	{
		if (i % 100 == 0)
		{
			pthread_mutex_lock(&philo->data->lock);
			if (philo->data->dead_full)
			{
				pthread_mutex_unlock(&philo->data->lock);
				return (1);
			}
			pthread_mutex_unlock(&philo->data->lock);
		}
		i++;
		usleep(500);
	}
}

static int	print_lock(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead_full)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	printf("%lld ", ft_time() - philo->data->start_time);
	printf("%d ", philo->id);
	printf("%s\n", str);
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

static int	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_lock("has taken left fork", philo);
	pthread_mutex_lock(philo->right_fork);
	print_lock("has taken right fork", philo);
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
	//while all not eaten and no one dead
	while (data->dead_full == 0)
	{
	//grab forks
		grab_forks(philo);
	//eat
	//sleep_think
	//repeat
		return (0);
	}
	return (0);
}
