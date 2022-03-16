/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:16:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/16 19:13:37 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life_bonus.h"

void	*philolife(t_philo *philo)
{
	while (1)
	{
		philopickforks(philo);
		philosleep(philo);
		philothink(philo);
	}
	return ((void *)0);
}

void	philoeat(t_philo *philo)
{
	philo->stat.lastmeal = calctime(&philo->tval) - philo->gen->tstlife;
	philo->stat.act = philo->stat.lastmeal;
	printf("%s%ld %d is eating\n%s", philo->clr,
			(long)philo->stat.lastmeal, philo->nbr, RESET_COLOR);
	eating(philo);
	if (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die)
		kill(0, SIGINT);
}

void	eating(t_philo *philo)
{
	while (philo->stat.act < philo->stat.lastmeal + philo->gen->t_eat
			&& philo->stat.act < philo->stat.lastmeal + philo->gen->t_die)
	{
		philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
		if (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_eat)
			philo->stat.ate++;
	}
}

void	philosleep(t_philo *philo)
{
	philo->stat.lastsleep = calctime(&philo->tval) - philo->gen->tstlife;
	printf("%s%ld %d is sleeping\n%s", philo->clr,
		(long)philo->stat.lastsleep, philo->nbr, RESET_COLOR);
	philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	while (philo->stat.act < philo->stat.lastsleep + philo->gen->t_sleep
			&& philo->stat.act < philo->stat.lastmeal + philo->gen->t_die)
		philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	if (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die)
		kill(0, SIGINT);
}

void	philothink(t_philo *philo)
{
	philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	printf("%s%ld %d is thinking\n%s", philo->clr,
		(long)philo->stat.act, philo->nbr, RESET_COLOR);
	if (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die)
		kill(0, SIGINT);
}
