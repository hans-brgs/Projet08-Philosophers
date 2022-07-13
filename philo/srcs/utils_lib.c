/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 08:27:49 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/06/29 08:27:49 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\r' || c == '\n')
		return (1);
	else if (c == '\v' || c == '\f' || c == '\t')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	char			sign;
	unsigned int	nbr;

	sign = 1;
	nbr = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return ((int)(sign * nbr));
}

int	ft_exit(char *str)
{
	printf("%serror : %s%s\n", R, str, K);
	return (-1);
}

void	ft_free(t_zeus *zeus, int j)
{
	if (j == 1)
	{
		free(zeus->table);
		free(zeus);
	}
	if (j == 2)
	{
		pthread_mutex_destroy(&zeus->table->write);
		free(zeus->table);
		free(zeus);
	}
	if (j == 3)
	{
		pthread_mutex_destroy(&zeus->table->write);
		free(zeus->philo);
		free(zeus->table);
		free(zeus);
	}
}
