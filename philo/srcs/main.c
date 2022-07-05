/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 08:22:14 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/06/29 08:22:14 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_thread(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(50);
	while (philo->table->finish == 0)
	{
		ft_eat(philo);
		if (philo->table->eaten / philo->table->num_of_philo
			== philo->table->to_eat)
			break ;
		if (philo->table->finish == 1)
			break ;
		ft_sleep(philo);
		if (philo->table->finish == 1)
			break ;
		ft_think(philo);
		if (philo->table->finish == 1)
			break ;
	}
	return (NULL);
}

int	dinner_time(t_zeus *zeus)
{
	int	i;

	if (init_philos(zeus) == -1)
		return (-1);
	zeus->table->start_dinner_time = actual_time();
	i = -1;
	while (++i < zeus->table->num_of_philo)
	{
		if (zeus->table->num_of_philo == 1)
			zeus->philo[i].r_fork = NULL;
		else if (i == zeus->table->num_of_philo - 1)
			zeus->philo[i].r_fork = zeus->philo[0].l_fork;
		else
			zeus->philo[i].r_fork = zeus->philo[i + 1].l_fork;
		pthread_create(&zeus->philo[i].thread, NULL, ft_thread,
			&zeus->philo[i]);
		pthread_mutex_destroy(zeus->philo[i].l_fork);
		if (zeus->table->finish == 1)
			break ;
	}
	i = -1;
	while (++i < zeus->table->num_of_philo)
		pthread_join(zeus->philo[i].thread, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_zeus	*zeus;
	t_table	*table;

	if (!(argc == 5 || argc == 6))
		return (ft_exit("Wrong number of argument."));
	table = malloc(sizeof(*table));
	if (!table)
		return (ft_exit("Malloc failled."));
	memset(table, 0, sizeof(t_table));
	if (init_table(argc, argv, table) == -1)
		return (-1);
	zeus = malloc(sizeof(*zeus));
	if (!zeus)
		return (ft_exit("Malloc failled."));
	memset(zeus, 0, sizeof(t_zeus));
	zeus->table = table;
	pthread_mutex_init(&zeus->die, NULL);
	pthread_create(&zeus->thread, NULL, is_dead, (void *)(zeus));
	pthread_detach(zeus->thread);
	dinner_time(zeus);
	ft_free_all(zeus);
	return (0);
}
