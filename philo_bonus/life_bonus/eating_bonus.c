/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:05:01 by gleal             #+#    #+#             */
/*   Updated: 2022/03/26 18:13:33 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life_bonus.h"

int	philopickforks(t_philo *philo)
{
	sem_wait(philo->sm.forkpile);
	pthread_mutex_lock(&philo->forksheldcheck);
	philo->stat.forks_held++;
	pthread_mutex_unlock(&philo->forksheldcheck);
	if (careful_print("%s%ld %d has taken a fork\n%s", philo))
	{
		sem_post(philo->sm.forkpile);
		return (1);
	}
	sem_wait(philo->sm.forkpile);
	pthread_mutex_lock(&philo->forksheldcheck);
	philo->stat.forks_held++;
	pthread_mutex_unlock(&philo->forksheldcheck);
	if (careful_print("%s%ld %d has taken a fork\n%s", philo))
	{
		sem_post(philo->sm.forkpile);
		sem_post(philo->sm.forkpile);
		return (1);
	}
	return (philoeat(philo));
}

int	starve(t_philo *philo)
{
	sem_wait(philo->sm.forkpile);
	regular_print("%s%ld %d has taken a fork\n%s", philo);
	while (calctime(philo->gen) < philo->stat.lastmeal + philo->gen->t_die)
		;
	regular_print("%s%ld %d died\n%s", philo);
	exit(philo->nbr - 1);
}

int	philoeat(t_philo *philo)
{
	philo->stat.lastmeal = calctime(philo->gen);
	if (careful_print("%s%ld %d is eating\n%s", philo))
	{
		sem_post(philo->sm.forkpile);
		sem_post(philo->sm.forkpile);
		return (1);
	}
	while (calctime(philo->gen) < philo->stat.lastmeal + philo->gen->t_eat)
		;
	philo->stat.ate++;
	if ((philo->gen->eat_freq && philo->stat.ate == philo->gen->eat_freq))
		sem_post(philo->sm.satisfied);
	sem_post(philo->sm.forkpile);
	sem_post(philo->sm.forkpile);
	pthread_mutex_lock(&philo->forksheldcheck);
	philo->stat.forks_held = 0;
	pthread_mutex_unlock(&philo->forksheldcheck);
	return (0);
}
