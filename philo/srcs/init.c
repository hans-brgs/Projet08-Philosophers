/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:50:48 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/06/30 14:50:48 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_arg(t_table *table)
{
	if (table->num_of_philo < 1)
		return (-1);
	if (table->time_die < 1)
		return (-1);
	if (table->time_eat < 1)
		return (-1);
	if (table->time_sleep < 1)
		return (-1);
	if (table->to_eat == 0)
		return (-1);
	return (0);
}

int	init_table(int argc, char **argv, t_table *table)
{
	table->num_of_philo = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	table->wait = 0;
	table->finish = 0;
	if (argc == 6)
		table->to_eat = ft_atoi(argv[5]);
	else
		table->to_eat = -1;
	if (check_arg(table) == -1)
		return (ft_exit("Argument has wrong value."));
	return (0);
}

int	init_philos(t_zeus *zeus)
{
	int			i;
	t_table		*table;
	t_philos	*philo;

	table = zeus->table;
	philo = malloc(sizeof(t_philos) * table->num_of_philo);
	if (!philo)
		return (ft_exit("Malloc failled."));
	i = -1;
	zeus->philo = philo;
	while (++i < table->num_of_philo)
	{
		philo[i].l_fork = malloc(sizeof(pthread_mutex_t));
		if (!philo[i].l_fork)
			return (ft_exit("Malloc failled."));
		pthread_mutex_init(philo[i].l_fork, NULL);
	}
	return (0);
}
