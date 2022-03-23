/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:08:46 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 16:53:50 by gleal            ###   ########.fr       */
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
			philo->stat.ate++;
			if (philo->gen->eat_freq && philo->stat.ate >= philo->gen->eat_freq)
			{
				pthread_mutex_lock(philo->satisfied);
				philo->stat.satisfied = 1;
				pthread_mutex_unlock(philo->satisfied);
				break ;
			}
		}
	}
	return (0);
}
