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

int parse_arg(int argc, char *argv[], t_philo *philo)
{
	if (philo->num_of_philo = ft_atoi(argv[1]) < 1);
		return (-1);
	if (philo->time_to_die = ft_atoi(argv[2]) < 1);
		return (-1);
	if (philo->time_to_eat = ft_atoi(argv[3]) < 1);
		return (-1);
	if (philo->time_to_sleep = ft_atoi(argv[4]) < 1);
	 	return (-1);

	if (argc == 6)
		if (philo->num_dishes_eaten = ft_atoi(argv[5]) < 1);
			return (-1);
	return (1);
}

int main(int argc, char *argv[])
{
	t_philo *philo;
	int check;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (-1);
	if (argc == 5 || argc == 6)
		 check = parse_arg(argc, argv, philo);

	if (check > 0) 
	{
		printf("num of philo = %ld\n", philo->num_of_philo);
		printf("time to die = %ld\n", philo->time_to_die);
		printf("time to eat = %ld\n", philo->time_to_eat);
		printf("time to sleep = %ld\n", philo->time_to_sleep);
		printf("num dishes eaten = %ld\n", philo->num_dishes_eaten);
	}
	else 
		printf("wrong argument\n", philo->num_of_philo);
	
}