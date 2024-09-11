#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>

struct	s_rules;

typedef struct s_philo
{
	pthread_t		thread;
	pid_t			pid;
	int			id;
	int			meals;
	long long		last_meal;
	struct s_rules		*data;
}	t_philo;

typedef struct s_rules
{
	int			philo_num;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			num_eat;
	int			dead;
	int			full;
	long long		start_time;
	t_philo			*philo;
	sem_t			*forks;
	sem_t			*meal_lock;
	sem_t			*death_lock;
	sem_t			*full_lock;
}	t_rules;

//error_bonus.c
int	error_message(char *str);
int	free_and_destroy(char *str, t_rules *data, int exit);

//initialize_bonus.c
int	check_args(int ac, char **av, t_rules *data);
int	init_philo(t_rules *data);

//utils_bonus.c
long long	ft_time(void);
void		ft_putstr_fd(char *str, int fd);
int		ft_atoi(const char *str, int *res);

#endif
