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

static int	check_arg(int argc, t_table *table)
{
	if (table->num_of_philo < 1)
		return (-1);
	if (table->time_die < 1)
		return (-1);
	if (table->time_eat < 1)
		return (-1);
	if (table->time_sleep < 1)
		return (-1);
	if (argc == 6 && table->to_eat < 1)
		return (-1);
	return (0);
}

static int	fill_table(int argc, char **argv, t_zeus *zeus)
{
	t_table	*table;

	table = zeus->table;
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
	if (check_arg(argc, table) == -1)
	{
		ft_free(zeus, 1);
		return (ft_exit("Arg Error"));
	}
	return (0);
}

int	init_table(int argc, char **argv, t_zeus *zeus)
{
	zeus->table = malloc(sizeof(t_table));
	if (!zeus->table)
	{
		free(zeus);
		return (ft_exit("Malloc failled."));
	}
	memset(zeus->table, 0, sizeof(t_table));
	if (fill_table(argc, argv, zeus) == -1)
		return (-1);
	pthread_mutex_init(&zeus->table->write, NULL);
	return (0);
}

static int	fill_philos(t_zeus *zeus)
{
	int			i;
	t_philos	*philo;

	i = -1;
	philo = zeus->philo;
	while (++i < zeus->table->num_of_philo)
	{
		memset(&philo[i], 0, sizeof(t_philos));
		philo[i].id = i + 1;
		philo[i].table = zeus->table;
		philo[i].l_fork = malloc(sizeof(pthread_mutex_t));
		if (!philo[i].l_fork)
		{
			ft_free(zeus, 3);
			return (ft_exit("Malloc failled."));
		}
		pthread_mutex_init(philo[i].l_fork, NULL);
	}
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
	{
		ft_free(zeus, 2);
		return (ft_exit("Malloc failled."));
	}
	zeus->philo = philo;
	if (fill_philos(zeus) == -1)
		return (-1);
	i = -1;
	while (++i < zeus->table->num_of_philo)
	{
		if (zeus->table->num_of_philo == 1)
			philo[i].r_fork = NULL;
		else if (i == zeus->table->num_of_philo - 1)
			philo[i].r_fork = zeus->philo[0].l_fork;
		else
			philo[i].r_fork = zeus->philo[i + 1].l_fork;
	}
	return (0);
}
