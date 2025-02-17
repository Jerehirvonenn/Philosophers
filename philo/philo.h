/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhirvone <jhirvone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:29:00 by jhirvone          #+#    #+#             */
/*   Updated: 2024/11/18 11:47:46 by jhirvone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

struct	s_rules;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals;
	long long		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*meal_lock;
	struct s_rules	*data;
}	t_philo;

typedef struct s_rules
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	death_lock;
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	int				dead;
	int				full;
	long long		start_time;
	t_philo			*philo;
}	t_rules;

long long	ft_time(void);
void		*eat_sleep_think(void *strct);
void		ft_putstr_fd(char *str, int fd);
int			check_args(int ac, char **av, t_rules *data);
int			init_philo(t_rules *data);
int			start_threads(t_rules *data);
int			join_threads(t_rules *data);
int			lonely_philo_check(t_philo *philo);
int			error_message(char *str);
int			free_and_destroy(char *str, t_rules *data, int exit);
int			ft_atoi(const char *str, int *res);
int			start_threads(t_rules *data);
int			join_threads(t_rules *data);
int			print_lock(char *str, t_philo *philo);
int			ft_sleep(long long wait, t_philo *philo);

#endif
