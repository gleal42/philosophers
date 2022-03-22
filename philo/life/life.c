/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:16:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/21 23:54:08 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	*philolife(t_philo *philo)
{
	if (philo->nbr % 2 == 0)
		usleep(philo->gen->t_eat * 1000);
	while (1)
	{
		if (is_dead(philo))
			return ((void *)0);
		philopickforks(philo);
		if (is_dead(philo))
			return ((void *)0);
		philosleep(philo);
		if (is_dead(philo))
			return ((void *)0);
		philothink(philo);
	}
	return ((void *)0);
}

void	philosleep(t_philo *philo)
{
	philo->stat.lastsleep = calctime() - philo->gen->tstlife;
	pthread_mutex_lock(philo->death);
	if (!philo->gen->endlife)
		printf("%s%ld %d is sleeping\n%s", philo->clr,
			(long)philo->stat.lastsleep, philo->nbr, RESET_COLOR);
	pthread_mutex_unlock(philo->death);
	philo->stat.act = calctime() - philo->gen->tstlife;
	while (philo->stat.act < philo->stat.lastsleep + philo->gen->t_sleep
		&& philo->stat.act < philo->stat.lastmeal + philo->gen->t_die)
	{
		philo->stat.act = calctime() - philo->gen->tstlife;
		pthread_mutex_lock(philo->death);
		if (philo->gen->endlife)
		{
			pthread_mutex_unlock(philo->death);
			return ;
		}
		pthread_mutex_unlock(philo->death);
	}
}

void	philothink(t_philo *philo)
{
	philo->stat.act = calctime() - philo->gen->tstlife;
	pthread_mutex_lock(philo->death);
	if (philo->gen->endlife)
	{
		pthread_mutex_unlock(philo->death);
		return ;
	}
	pthread_mutex_unlock(philo->death);
	printf("%s%ld %d is thinking\n%s", philo->clr,
		(long)philo->stat.act, philo->nbr, RESET_COLOR);
}
