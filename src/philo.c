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
	printf("Start Time      :%lld\n", data->start_time);
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

void	monitor(t_rules *data)
{
	int	i;

	i = -1;
	while (data->full == 0)
	{
		while (++i < data->philo_num)
		{
			pthread_mutex_lock(&data->meal_lock[i]);
			if (ft_time() - data->philo[i].last_meal >= data->time_die)
			{
				pthread_mutex_lock(&data->death_lock);
				data->dead = 1;
				printf("%lld %d %s\n", ft_time() - data->start_time, i + 1, "died");
				pthread_mutex_unlock(&data->death_lock);
				pthread_mutex_unlock(&data->meal_lock[i]);
				return ;
			}
			pthread_mutex_unlock(&data->meal_lock[i]);

		}
		i = 0;
		while (data->num_eat != -1 && i < data->philo_num && data->philo[i].meals >= data->num_eat)
			i++;
		if (i == data->philo_num)
			data->full = 1;
		i = -1;
	}
}

int	main(int ac, char **av)
{
	t_rules	data;

	if (check_args(ac, av, &data))
		return (error_message("Invalid input\n"));
	if (init_philo(&data))
		return (1);
	test_init(&data); //testing
	if (start_threads(&data))
		return (free_and_destroy("Failed to create threads\n", &data, 1));
	monitor(&data);
	join_threads(&data);
	free_and_destroy(NULL, &data, 0);
}
