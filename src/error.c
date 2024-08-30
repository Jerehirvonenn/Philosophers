#include "../includes/philo.h"

static void	ft_putstr_fd(char *str, int fd)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

int	error_message(char *str)
{
	ft_putstr_fd(str, 1);
	return(1);
}

int	free_and_destroy(char *str, t_rules *data, int exit)
{
	int i;

	i = 0;

	if (str)
		ft_putstr_fd(str, 1);
	pthread_mutex_destroy(&data->lock);
	while (i < data->philo_num)
		pthread_mutex_destroy(&data->forks[i++]);
	return (exit);
}
