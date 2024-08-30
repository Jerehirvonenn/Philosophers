#include "../includes/philo.h"
#include <stdio.h> //DELETE

//TO DO: Usage message, Error messages for failingto create threads/mutexes, func that stops all threads if
//lets say making thread nmber 5 fails

void	test_init(t_rules *data)
{
	printf("Number of philos:%d\n", data->philo_num);
	printf("Time to die     :%d\n", data->time_die);
	printf("Time to eat     :%d\n", data->time_eat);
	printf("Time to sleep   :%d\n", data->time_sleep);
	printf("Number of meals :%d\n", data->num_eat);
	int i = 0;
	while (i < data->philo_num)
	{
		printf("-----------------------\n");
		printf("ID     :%d\n", data->philo[i].id);
		printf("Meals  :%d\n", data->philo[i].meals);
		printf("L_fork :%p\n", data->philo[i].left_fork);
		printf("R_fork :%p\n", data->philo[i].right_fork);
		printf("-----------------------\n");
		i++;
	}
}

void	*ft_test(void *pointer)
{
	t_philo *philo;

	philo = (t_philo*)pointer;
	int random_time = rand() % 1000;  // Random time
	usleep(random_time * 1000);       // usleep takes microseconds
	pthread_mutex_lock(&philo->data->lock);
	printf("Hello! I'm philosopher number %d\n", philo->id);
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

int	start_threads(t_rules *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		if (pthread_create(&(data->philo[i].thread),
			NULL, &ft_test, &data->philo[i]))
		{
			while (--i >= 0)
				pthread_join(data->philo[i].thread, NULL);
			return (1);
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

int	main(int ac, char **av)
{
	t_rules	data;

	if (check_args(ac, av, &data))
		return (error_message("Invalid input"));
	if (init_philo(&data))
		return (1);
	test_init(&data); //testing
	if (start_threads(&data))
		return (1);
	join_threads(&data);
}
