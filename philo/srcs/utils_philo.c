/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 21:30:52 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/07/03 21:30:52 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		ft_exit("Gettimeofday failled\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(t_table *table, long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms && table->finish == 0)
		usleep(time_in_ms / 10);
}

long int	ft_timestamp(t_philos *philo)
{
	long int	timestamp;

	timestamp = actual_time() - philo->table->start_dinner_time;
	return (timestamp);
}

void	mutex_printf(t_philos *philo, char *str)
{
	pthread_mutex_lock(&philo->table->write);
	printf("%ld %d %s\n", ft_timestamp(philo), philo->id, str);
	pthread_mutex_unlock(&philo->table->write);
}

void	ft_free_all(t_zeus *zeus)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&zeus->table->write);
	while (++i < zeus->table->num_of_philo)
	{
		pthread_mutex_destroy(zeus->philo[i].l_fork);
		free(zeus->philo[i].l_fork);
	}
	free(zeus->philo);
	free(zeus->table);
	free(zeus);
}
