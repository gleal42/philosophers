/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:05:01 by gleal             #+#    #+#             */
/*   Updated: 2022/03/21 17:50:41 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life_bonus.h"

int	philopickforks(t_philo *philo)
{
	sem_wait(philo->sm.forkpile);
	if (philo->gen->eat_freq && philo->ate == philo->gen->eat_freq)
		usleep(30);
	careful_print("%s%ld %d has taken a fork\n%s", philo);
	if (philo->gen->philonbr == 1)
		return (starve(philo));
	sem_wait(philo->sm.forkpile);
	if (philo->gen->eat_freq && philo->ate == philo->gen->eat_freq)
		usleep(30);
	careful_print("%s%ld %d has taken a fork\n%s", philo);
	return (philoeat(philo));
}

int	starve(t_philo *philo)
{
	philo->act = calctime() - philo->gen->tstlife;
	while (philo->act < philo->lastmeal + philo->gen->t_die)
		philo->act = calctime() - philo->gen->tstlife;
	sem_post(philo->sm.forkpile);
	regular_print("%s%ld %d died\n%s", philo);
	return (1);
}

int	philoeat(t_philo *philo)
{
	philo->lastmeal = calctime() - philo->gen->tstlife;
	if (philo->gen->eat_freq && philo->ate == philo->gen->eat_freq)
		usleep(30);
	careful_print("%s%ld %d is eating\n%s", philo);
	if (eating(philo))
		return (1);
	if (philo->act >= philo->lastmeal + philo->gen->t_die)
		return (philokill(philo));
	return (0);
}

int	eating(t_philo *philo)
{
	philo->act = calctime() - philo->gen->tstlife;
	while (philo->act <= philo->lastmeal + philo->gen->t_eat)
	{
		philo->act = calctime() - philo->gen->tstlife;
		if (philo->act >= philo->lastmeal + philo->gen->t_eat)
		{
			philo->ate++;
			if ((philo->gen->eat_freq && philo->ate == philo->gen->eat_freq))
			{
				sem_post(philo->sm.satisfied);
				break ;
			}
			break ;
		}
		if (philo->act >= philo->lastmeal + philo->gen->t_die)
			return (philokill(philo));
	}
	sem_post(philo->sm.forkpile);
	sem_post(philo->sm.forkpile);
	return (0);
}
