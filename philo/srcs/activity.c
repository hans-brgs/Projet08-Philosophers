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

void	ft_eat(t_philos *philo)
{	
	if (philo->table->eaten / philo->table->num_of_philo
		== philo->table->to_eat)
		return ;
	pthread_mutex_lock(philo->l_fork);
	philo->table->wait = 1;
	mutex_printf(philo, STATE_RFORK);
	if (!philo->r_fork)
		return ;
	pthread_mutex_lock(philo->r_fork);
	mutex_printf(philo, STATE_RFORK);
	mutex_printf(philo, STATE_EAT);
	philo->start_time_die = actual_time();
	philo->table->eaten += 1;
	ft_usleep(philo->table, philo->table->time_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->table->write);
	printf("%ld %d %s\n", ft_timestamp(philo), philo->id, STATE_SLEEP);
	pthread_mutex_unlock(&philo->table->write);
	ft_usleep(philo->table, philo->table->time_sleep);
}

void	ft_think(t_philos *philo)
{
	pthread_mutex_lock(&philo->table->write);
	printf("%ld %d %s\n", ft_timestamp(philo), philo->id, STATE_THINK);
	pthread_mutex_unlock(&philo->table->write);
}
