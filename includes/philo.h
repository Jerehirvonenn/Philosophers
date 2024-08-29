#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

struct s_rules;

typedef struct s_philo
{
	pthread_t		thread;
	int			id;
	int			meals;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_rules		*data;
}	t_philo;

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
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
}	t_rules;

int	check_args(int ac, char **av, t_rules *data);
int	init_philo(t_rules *data);

#endif
