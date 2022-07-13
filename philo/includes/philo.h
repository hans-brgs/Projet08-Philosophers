/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 08:08:29 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/06/29 08:08:29 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

typedef struct s_table
{
	int				num_of_philo;
	int				to_eat;
	int				eaten;
	int				finish;
	int				wait;
	long int		time_die;
	long int		time_eat;
	long int		time_sleep;
	long int		start_dinner_time;
	pthread_mutex_t	write;
}	t_table;

typedef struct s_philos
{
	int				id;
	int				is_dead;
	long int		start_time_die;
	int				eaten;
	int				is_full;
	t_table			*table;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philos;

typedef struct s_zeus
{
	t_table			*table;
	t_philos		*philo;
	pthread_t		thread;
}	t_zeus;

//  utils_lib
int			ft_atoi(const char *str);
int			ft_exit(char *str);
void		ft_free(t_zeus *zeus, int j);
void		ft_free_all(t_zeus *zeus);

// init
int			init_table(int argc, char **argv, t_zeus *zeus);
int			init_philos(t_zeus *zeus);

// utils_philos
void		ft_usleep(t_table *table, long int time_in_ms);
long int	actual_time(void);
long int	ft_timestamp(t_philos *philo);
void		mutex_printf(t_philos *philo, char *str);

// activity
void		ft_eat(t_philos *philo);
void		ft_think(t_philos *philo);
void		ft_sleep(t_philos *philo);

// threads
void		*ft_thread(void *arg);
void		*is_dead(void *arg);

# define R "\033[0;31m"
# define K "\033[0;30m"
# define STATE_LFORK "has taken a fork"
# define STATE_RFORK "has taken a fork"
# define STATE_EAT "is eating"
# define STATE_SLEEP "is sleeping"
# define STATE_THINK "is thinking"
# define STATE_DIED "died"

#endif