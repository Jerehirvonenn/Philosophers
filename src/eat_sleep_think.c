#include "../includes/philo.h"

#include <stdio.h>
static int	print_lock(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lld ", ft_time() - philo->data->start_time);
	printf("%d ", philo->id);
	printf("%s\n", str);
	pthread_mutex_unlock(&philo->data->print_lock);
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
