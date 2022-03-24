/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:06:20 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 23:40:09 by gleal            ###   ########.fr       */
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
	pthread_mutex_lock(&philo->died);
	if (philo->stat.dead)
	{
		pthread_mutex_unlock(&philo->died);
		return (1);
	}
	pthread_mutex_unlock(&philo->died);
	return (0);
}

void	death_bed(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->died);
		if (philo->stat.dead)
		{
			pthread_mutex_unlock(&philo->died);
			return ;
		}
		pthread_mutex_unlock(&philo->died);
	}
}
