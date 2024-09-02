#include "../includes/philo.h"

int	print_lock()
{
	pthread_mutex_lock(data->print_lock);
	pthread_mutex_unlock(data->print_lock);
}

int	grab_forks(t_philo *philo, t_rules *data)
{
	pthread_mutex_lock(philo->left_fork);
	print_lock();
	pthread_mutex_lock(philo->right_fork);
	print_lock();
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
		grab_forks(philo, data);
	//eat
	//sleep_think
	//repeat
	}
	return (0);
}
