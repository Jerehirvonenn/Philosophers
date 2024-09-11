#include "philo_bonus.h"

void	eat_sleep_think(t_philo *philo)
{
	t_rules *data;

	data = philo->data;
}

void	ft_test(t_philo *philo)
{
	printf("Hello process philo number %i\n",philo->id);
	exit(0);
}

int	start_philos(t_rules *data)
{
	int		i;
	long long	start;

	i = 0;
	start = ft_time();
	data->start_time = start;
	while (i < data->philo_num)
	{
		data->philo[i].last_meal = start;
		data->philo[i].pid = fork();
		if (data->philo[i].pid == -1)
		{
			while (--i >= 0)
				kill(data->philo[i].pid, SIGTERM);
			return (1);
		}
		else if (data->philo[i].pid == 0)
			ft_test(&data->philo[i]);
		else
			usleep(100);
		i++;
	}
	return(0);
}

int	main(int ac, char **av)
{
	t_rules	data;

	if (check_args(ac, av, &data))
		return (error_message("Invalid input\n"));
	if (init_philo(&data))
		return (1);
	if (start_philos(&data))
		return (free_and_destroy("Failed to something something\n", &data, 1));
	/*monitor(&data);
	join_threads(&data);
	free_and_destroy(NULL, &data, 0);*/
}
