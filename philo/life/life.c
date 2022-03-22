/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:16:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/22 17:43:30 by gleal            ###   ########.fr       */
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
	if (is_dead(philo))
		return ;
	printf("%s%ld %d is sleeping\n%s", philo->clr,
		(long)philo->stat.lastsleep, philo->nbr, RESET_COLOR);
	philo->stat.act = calctime() - philo->gen->tstlife;
	while (philo->stat.act < philo->stat.lastsleep + philo->gen->t_sleep)
	{
		philo->stat.act = calctime() - philo->gen->tstlife;
		if (is_dead(philo))
			return ;
	}
}

void	philothink(t_philo *philo)
{
	philo->stat.act = calctime() - philo->gen->tstlife;
	if (is_dead(philo))
		return ;
	printf("%s%ld %d is thinking\n%s", philo->clr,
		(long)philo->stat.act, philo->nbr, RESET_COLOR);
}
