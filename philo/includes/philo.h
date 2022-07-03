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

typedef struct s_table
{
	int			num_of_philo;
	int			to_eat;
	int			eaten;
	int			finish;
	int			wait;
	long int	time_die;
	long int	time_eat;
	long int	time_sleep;
	long int	time_think;
	long int	start_dinner_time;
}	t_table;

typedef struct s_philos
{
	int				id;
	int				is_dead;
	long int		start_time_die;
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
	pthread_mutex_t	die;

}	t_zeus;

//  utils_lib
int			ft_atoi(const char *str);
int			ft_exit(char *str);

// init
int			init_table(int argc, char **argv, t_table *table);
int			init_philos(t_zeus *zeus);

// utils_philos
void		ft_usleep(long int time_in_ms);
void		ft_free_all(t_zeus *zeus);
long int	actual_time(void);
long int	ft_timestamp(t_philos *philo);

// activity
void		ft_eat(t_philos *philo);
void		ft_think(t_philos *philo);
void		ft_sleep(t_philos *philo);
void		*is_dead(void *arg);

# define R "\033[0;31m"
# define G "\033[0;32m"
# define C "\033[0;36m"
# define P "\033[0;35m"
# define K "\033[0;30m"
# define W "\033[0;37m"
# define STATE_LFORK "has taken a fork"
# define STATE_RFORK "has taken a fork"
# define STATE_EAT "is eating"
# define STATE_SLEEP "is sleeping"
# define STATE_THINK "is thinking"
# define STATE_DIED "died"

#endif