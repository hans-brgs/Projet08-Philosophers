/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 20:28:24 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/07/08 20:28:24 by hbourgeo         ###   ########.fr       */
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

static int	check_death(t_zeus *zeus)
{
	int	i;

	i = -1;
	while (++i < zeus->table->num_of_philo)
	{
		if (actual_time() - zeus->philo[i].start_time_die
			>= zeus->table->time_die)
		{
			pthread_mutex_lock(&zeus->table->write);
			zeus->table->finish = 1;
			printf("%ld %d %s\n", ft_timestamp(&zeus->philo[i]),
				zeus->philo[i].id, STATE_DIED);
			return (1);
		}
	}
	if (zeus->table->eaten >= zeus->table->num_of_philo)
	{
		pthread_mutex_lock(&zeus->table->write);
		zeus->table->finish = 1;
		return (1);
	}
	return (0);
}

void	*is_dead(void *arg)
{
	t_zeus	*zeus;

	zeus = (t_zeus *)arg;
	wait_dinner_start(zeus);
	ft_usleep(zeus->table, zeus->table->time_die);
	while (1)
	{
		if (check_death(zeus) == 1)
			return (NULL);
	}
	return (NULL);
}

void	*ft_thread(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->table, 50);
	while (philo->table->finish == 0)
	{
		if (philo->table->finish == 1)
			return (NULL);
		ft_eat(philo);
		if (philo->table->finish == 1 || philo->is_full == 1)
			return (NULL);
		ft_sleep(philo);
		if (philo->table->finish == 1)
			return (NULL);
		ft_think(philo);
		if (philo->table->finish == 1)
			return (NULL);
	}
	return (NULL);
}
