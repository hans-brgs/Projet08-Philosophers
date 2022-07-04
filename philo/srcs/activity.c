/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:28:32 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/07/01 10:28:32 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_dinner_start(t_zeus *zeus)
{
	int	stop;
	int	i;

	stop = 0;
	while (1)
	{
		i = -1;
		while (++i < zeus->table->num_of_philo)
		{
			if (zeus->table->wait != 0)
			{
				stop = 1;
				break ;
			}
		}
		if (stop == 1)
			break ;
	}
}

void	*is_dead(void *arg)
{
	int		i;
	t_zeus	*zeus;

	zeus = (t_zeus *)arg;
	wait_dinner_start(zeus);
	ft_usleep(zeus->table->time_die);
	while (1)
	{
		i = -1;
		while (++i < zeus->table->num_of_philo)
		{
			if (actual_time() - zeus->philo[i].start_time_die
				> zeus->table->time_die)
			{
				pthread_mutex_lock(&zeus->die);
				printf("%ld %d %s\n", ft_timestamp(&zeus->philo[i]),
					zeus->philo[i].id, STATE_DIED);
				zeus->table->finish = 1;
				pthread_mutex_unlock(&zeus->die);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	ft_eat(t_philos *philo)
{	
	if (philo->table->eaten / philo->table->num_of_philo
		== philo->table->to_eat)
		return ;
	pthread_mutex_lock(philo->l_fork);
	philo->table->wait = 1;
	printf("%ld %d %s\n", ft_timestamp(philo), philo->id, STATE_LFORK);
	if (!philo->r_fork)
	{
		ft_usleep(philo->table->time_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	printf("%ld %d %s\n", ft_timestamp(philo), philo->id, STATE_RFORK);
	philo->table->eaten += 1;
	printf("%ld %d %s\n", ft_timestamp(philo), philo->id, STATE_EAT);
	philo->start_time_die = actual_time();
	ft_usleep(philo->table->time_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_sleep(t_philos *philo)
{
	long int	time;

	time = 0;
	printf("%ld %d %s\n", ft_timestamp(philo), philo->id, STATE_SLEEP);
	while (time < philo->table->time_sleep)
	{
		if (philo->table->finish == 1)
			break ;
		ft_usleep(1);
		time ++;
	}
}

void	ft_think(t_philos *philo)
{
	printf("%ld %d %s\n", ft_timestamp(philo), philo->id, STATE_THINK);
}
