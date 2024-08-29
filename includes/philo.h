#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>

typedef struct s_rules
{
	int			philo_num;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			num_eat;
	int			all_full;
	int			dead;
	t_philo			*philo;
	p_thread _mutex_t	*forks;
}	t_rules;

typedef struct s_philo
{
	int		id;
	int		meals;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_rules		*data;
}	t_philo;

int	check_args(int ac, char **av, t_rules *data);
int	ft_atoi(const char *str, int *res);

#endif
