/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:53:40 by gleal             #+#    #+#             */
/*   Updated: 2022/03/11 15:57:52by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	*philolife(t_philo *philo)
{
	while (!philo->gen->endlife)
	{
		if (!philo->gen->endlife)
			philopickforks(philo);
		if (!philo->gen->endlife)
			philosleep(philo);
		if (!philo->gen->endlife)
			philothink(philo);
	}
	return ((void *)0);
}

void	philopickforks(t_philo *philo)
{
	pthread_mutex_lock(philo->own->fork);
	*philo->own->using = 1;
	if (!*philo->right->using)
	{
		pthread_mutex_lock(philo->right->fork);
		*philo->right->using = 1;
		if (!philo->gen->endlife)
			philoeat(philo, philo->own, philo->right);
	}
	else
	{
		pthread_mutex_lock(philo->left->fork);
		*philo->left->using = 1;
		if (!philo->gen->endlife)
			philoeat(philo, philo->own, philo->left);
	}
}

void	philoeat(t_philo *philo, t_fork *forkone, t_fork *forktwo)
{
	int	ate;

	ate = 0;
	philo->stat.lastmeal = calctime(&philo->tval) - philo->gen->tstlife;
	philo->stat.act = philo->stat.lastmeal;
	printf("%ld %d is eating\n", (long)philo->stat.lastmeal, philo->nbr);
	while (!philo->gen->endlife && (philo->stat.act < philo->stat.lastmeal + philo->gen->t_eat
		&& philo->stat.act < philo->stat.lastmeal + philo->gen->t_die))
	{
		philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
		if (philo->stat.act >= philo->stat.lastmeal
			+ philo->gen->t_eat - 10 && !ate)
		{
			philo->stat.ate++;
			ate++;
		}
	}
	if (!philo->gen->endlife && (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die))
	{
		philo->stat.dead = 1;
		while (!philo->gen->endlife)
			;
	}
	pthread_mutex_unlock(forkone->fork);
	pthread_mutex_unlock(forktwo->fork);
}

void	philosleep(t_philo *philo)
{
	philo->stat.lastsleep = calctime(&philo->tval) - philo->gen->tstlife;
	philo->stat.act = philo->stat.lastsleep;
	printf("%ld %d is sleeping\n", (long)philo->stat.lastsleep, philo->nbr);
	while (!philo->gen->endlife && (philo->stat.act < philo->stat.lastsleep + philo->gen->t_sleep
		&& philo->stat.act < philo->stat.lastmeal + philo->gen->t_die))
		philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	if (!philo->gen->endlife && (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die))
	{
		philo->stat.dead = 1;
		while (!philo->gen->endlife)
			;
	}
}

void	philothink(t_philo *philo)
{
	philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	printf("%ld %d is thinking\n", (long)philo->stat.act, philo->nbr);
	if (!philo->gen->endlife && (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die))
	{
		philo->stat.dead = 1;
		while (!philo->gen->endlife)
			;
	}
}
