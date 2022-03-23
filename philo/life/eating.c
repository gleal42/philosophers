/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:08:46 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 02:45:48 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"


int	starve(t_philo *philo)
{
	death_bed(philo);
	return (1);
}

int	eating(t_philo *philo)
{
	while (philo->stat.act < philo->stat.lastmeal + philo->gen->t_eat)
	{
		if (is_dead(philo))
			return (1);
		philo->stat.act = calctime(philo->gen);
		if (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_eat)
		{
			pthread_mutex_lock(philo->ate);
			philo->stat.ate++;
			pthread_mutex_unlock(philo->ate);
			usleep(10);
		}
	}
	return (0);
}
