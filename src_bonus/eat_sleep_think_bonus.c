#include "philo_bonus.h"

int	ft_sleep(long long wait)
{
	long long	start;

	start = ft_time();
	while (ft_time() - start < wait)
	{
		usleep(1000);
	}
	return (0);
}

int	print_lock(char *str, t_philo *philo)
{
	sem_wait(philo->data->death_lock);
	printf("%lld %d %s\n", ft_time() - philo->data->start_time,
		philo->id, str);
	sem_post(philo->data->death_lock);
	return (0);
}

static int	grab_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_lock("has taken a fork", philo);
	sem_wait(philo->data->forks);
	print_lock("has taken a fork", philo);
	return (0);
}

static int	ft_eat(t_philo *philo)
{
	print_lock("is eating", philo);
	sem_wait(philo->data->meal_lock);
	philo->last_meal = ft_time();
	sem_post(philo->data->meal_lock);
	ft_sleep(philo->data->time_eat);
	sem_wait(philo->data->meal_lock);
	philo->meals++;
	sem_post(philo->data->meal_lock);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	return (0);
}

/*int	lonely_philo_check(t_philo *philo)
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

int	eat_sleep_think(void *strct)
{
	t_philo	*philo;
	t_rules	*data;	

	philo = (t_philo *)strct;
	data = philo->data;
	//if (lonely_philo_check(philo))
	//	return (0);
	sem_wait(data->death_lock);
	while (1)
	{
		sem_post(data->death_lock);
		grab_forks(philo);
		ft_eat(philo);
		sem_wait(data->death_lock);
		if (philo->meals >= data->num_eat && data->num_eat != 0) //need to change later
			break ;
		sem_post(data->death_lock);
		print_lock("is sleeping", philo);
		ft_sleep(philo->data->time_sleep);
		print_lock("is thinking", philo);
		sem_wait(data->death_lock);
	}
	sem_post(data->death_lock);
	exit (0);
}
