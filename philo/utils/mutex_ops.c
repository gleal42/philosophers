/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:06:20 by gleal             #+#    #+#             */
/*   Updated: 2022/03/15 17:15:29 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	leave_forks_on_the_table(pthread_mutex_t *right, pthread_mutex_t *left)
{
	pthread_mutex_unlock(right);
	pthread_mutex_unlock(left);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	if (philo->gen->endlife)
	{
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	pthread_mutex_unlock(philo->death);
	return (0);
}

void	death_bed(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->death);
		if (philo->gen->endlife)
		{
			pthread_mutex_unlock(philo->death);
			return ;
		}
		pthread_mutex_unlock(philo->death);
	}
}

void	rest_cutlery(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->eat);
		if (philo->gen->endlife)
		{
			pthread_mutex_unlock(philo->eat);
			return ;
		}
		pthread_mutex_unlock(philo->eat);
	}
}
