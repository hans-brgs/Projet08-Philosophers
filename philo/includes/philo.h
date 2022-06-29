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
# include <pthread.h>
# include <sys/time.h>


typedef struct s_philo
{
	size_t	num_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	size_t	num_dishes_eaten;
}	t_philo;

int	ft_atoi(const char *str);

#endif