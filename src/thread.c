#include "../includes/philo.h"
/*
static void	*ft_test(void *pointer)
{
	//testing
	t_philo	*philo;

	philo = (t_philo *)pointer;
	int random_time = rand() % 1000;
	usleep(random_time * 1000);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("Hello! I'm philosopher number %d\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);
	return (0);
}*/

int	start_threads(t_rules *data)
{
	int			i;
	long long	time;

	i = -1;
	time = ft_time();
	data->start_time = time;
	while (++i < data->philo_num)
	{
		data->philo->last_meal = time;
		if (pthread_create(&(data->philo[i].thread),
				NULL, &eat_sleep_think, &data->philo[i]))
		{
			while (--i >= 0)
				pthread_join(data->philo[i].thread, NULL);
			return (1);
		}
	}
	return (0);
}

int	join_threads(t_rules *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		if (pthread_join(data->philo[i].thread, NULL))
			return (1);
	return (0);
}
