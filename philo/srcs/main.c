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

int	dinner_time(t_zeus *zeus)
{
	int	i;

	if (init_philos(zeus) == -1)
		return (-1);
	zeus->table->start_dinner_time = actual_time();
	i = -1;
	while (++i < zeus->table->num_of_philo)
	{
		if (pthread_create(&zeus->philo[i].thread, NULL,
				ft_thread, &zeus->philo[i]) != 0)
		{
			ft_free_all(zeus);
			return (ft_exit("Thread failled"));
		}
		pthread_detach(zeus->philo[i].thread);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_zeus	*zeus;

	if (!(argc == 5 || argc == 6))
		return (ft_exit("Wrong number of argument."));
	zeus = malloc(sizeof(*zeus));
	if (!zeus)
		return (ft_exit("Malloc failled."));
	memset(zeus, 0, sizeof(t_zeus));
	if (init_table(argc, argv, zeus) == -1)
		return (-1);
	if (pthread_create(&zeus->thread, NULL, is_dead, (void *)(zeus)) != 0)
	{
		ft_free(zeus, 2);
		return (ft_exit("Thread failled."));
	}
	if (dinner_time(zeus) == -1)
		return (-1);
	pthread_join(zeus->thread, NULL);
	ft_free_all(zeus);
	return (0);
}
