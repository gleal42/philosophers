/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:16:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/14 21:28:26 by gleal            ###   ########.fr       */
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

void	philoeat(t_philo *philo, pthread_mutex_t *right, pthread_mutex_t *left)
{
	philo->stat.lastmeal = calctime(&philo->tval) - philo->gen->tstlife;
	philo->stat.act = philo->stat.lastmeal;
	if (!philo->gen->endlife)
		printf("%s%ld %d is eating\n%s", philo->clr,
			(long)philo->stat.lastmeal, philo->nbr, RESET_COLOR);
	eating(philo);
	if (!philo->gen->endlife
		&& (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die))
	{
		philo->stat.dead = 1;
		while (!philo->gen->endlife)
			;
	}
	leave_forks_on_the_table(right, left);
}

void	eating(t_philo *philo)
{
	int	ate;

	ate = 0;
	while (!philo->gen->endlife
		&& (philo->stat.act < philo->stat.lastmeal + philo->gen->t_eat
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
}

void	philosleep(t_philo *philo)
{
	philo->stat.lastsleep = calctime(&philo->tval) - philo->gen->tstlife;
	if (!philo->gen->endlife)
		printf("%s%ld %d is sleeping\n%s", philo->clr,
			(long)philo->stat.lastsleep, philo->nbr, RESET_COLOR);
	philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	while (!philo->gen->endlife
		&& (philo->stat.act < philo->stat.lastsleep + philo->gen->t_sleep
			&& philo->stat.act < philo->stat.lastmeal + philo->gen->t_die))
		philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	if (!philo->gen->endlife
		&& (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die))
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
		printf("%s%ld %d is thinking\n%s", philo->clr,
			(long)philo->stat.act, philo->nbr, RESET_COLOR);
	if (!philo->gen->endlife
		&& (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die))
	{
		philo->stat.dead = 1;
		while (!philo->gen->endlife)
			;
	}
}
