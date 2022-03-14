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


/* 	philo->stat.lastsleep = calctime(&philo->tval) - philo->gen->tstlife;
	philo->stat.act = philo->stat.lastsleep;
	if (!philo->gen->endlife)
		printf("%s%ld %d is sleeping\n%s", philo->clr, (long)philo->stat.lastsleep, philo->nbr, RESET_COLOR);
	while (!philo->gen->endlife && (philo->stat.act < philo->stat.lastsleep + philo->gen->t_sleep
		&& philo->stat.act < philo->stat.lastmeal + philo->gen->t_die))
		philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	if (!philo->gen->endlife && (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die))
	{
		philo->stat.dead = 1;
		while (!philo->gen->endlife)
			;
	} */

void	philopickforks(t_philo *philo)
{
	pthread_mutex_lock(&philo->own.fork);
	philo->own.using = 1;
	philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;;
	if (!philo->gen->endlife)
		printf("%s%ld %d has taken a fork\n%s", philo->clr, (long)philo->stat.act, philo->nbr, RESET_COLOR);
	if (philo->gen->philonbr == 1)
	{
		while (philo->stat.act < philo->stat.lastmeal + philo->gen->t_die)
			philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
		philo->stat.dead = 1;
		while (!philo->gen->endlife)
			;
		pthread_mutex_unlock(&philo->own.fork);
		return ;
	}
	while (1)
	{
		if (!philo->right->using)
		{
			philo->right->using = 1;
			pthread_mutex_lock(&philo->right->fork);
			philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;;
			if (!philo->gen->endlife)
				printf("%s%ld %d has taken a fork\n%s", philo->clr, (long)philo->stat.act, philo->nbr, RESET_COLOR);
			if (!philo->gen->endlife)
				philoeat(philo, &philo->own, philo->right);
			else
			{
				pthread_mutex_unlock(&philo->own.fork);
				pthread_mutex_unlock(&philo->right->fork);
				philo->own.using = 0;
				philo->right->using = 0;
			}
			break ;
		}
		if (!philo->left->using)
		{
			philo->left->using = 1;
			pthread_mutex_lock(&philo->left->fork);
			philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;;
			if (!philo->gen->endlife)
				printf("%s%ld %d has taken a fork\n%s", philo->clr, (long)philo->stat.act, philo->nbr, RESET_COLOR);
			if (!philo->gen->endlife)
				philoeat(philo, &philo->own, philo->left);
			else
			{
				pthread_mutex_unlock(&philo->own.fork);
				pthread_mutex_unlock(&philo->left->fork);
				philo->own.using = 0;
				philo->left->using = 0;
			}
			break ;
		}
	}
}

void	philoeat(t_philo *philo, t_fork *forkone, t_fork *forktwo)
{
	int	ate;

	ate = 0;
	philo->stat.lastmeal = calctime(&philo->tval) - philo->gen->tstlife;
	philo->stat.act = philo->stat.lastmeal;
	if (!philo->gen->endlife)
		printf("%s%ld %d is eating\n%s", philo->clr, (long)philo->stat.lastmeal, philo->nbr, RESET_COLOR);
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
	pthread_mutex_unlock(&forkone->fork);
	pthread_mutex_unlock(&forktwo->fork);
	forkone->using = 0;
	forktwo->using = 0;
}

void	philosleep(t_philo *philo)
{
	philo->stat.lastsleep = calctime(&philo->tval) - philo->gen->tstlife;
	if (!philo->gen->endlife)
		printf("%s%ld %d is sleeping\n%s", philo->clr, (long)philo->stat.lastsleep, philo->nbr, RESET_COLOR);
	philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
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
	if (!philo->gen->endlife)
		printf("%s%ld %d is thinking\n%s", philo->clr, (long)philo->stat.act, philo->nbr, RESET_COLOR);
	if (!philo->gen->endlife && (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die))
	{
		philo->stat.dead = 1;
		while (!philo->gen->endlife)
			;
	}
}
