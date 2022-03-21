/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:16:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/21 01:44:20 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life_bonus.h"

int	philolife(t_philo *philo)
{
	int i;

	philo->lastsleep = 0;
	philo->act = 0;
	philo->lastmeal = 0;
	philo->ate = 0;
	i = 0;
	while (i < 20)
	{
		if (philopickforks(philo))
			return (1);
		if (philosleep(philo))
			return (1);
		if (philothink(philo))
			return (1);
		i++;
	}
	return (0);
}

int	philopickforks(t_philo *philo)
{
	sem_wait(philo->forkpile);
	if ((philo->gen->eat_freq && philo->ate == philo->gen->eat_freq)
		|| philo->ate >= 10)
		usleep(30);
	careful_print("%s%ld %d has taken a fork\n%s", philo);
	if (philo->gen->philonbr == 1)
		return (starve(philo));
	sem_wait(philo->forkpile);
	if ((philo->gen->eat_freq && philo->ate == philo->gen->eat_freq)
		|| philo->ate >= 10)
		usleep(30);
	careful_print("%s%ld %d has taken a fork\n%s", philo);
	return (philoeat(philo));
}

int	starve(t_philo *philo)
{
	philo->act = calctime(&philo->tval) - philo->gen->tstlife;
	while (philo->act < philo->lastmeal + philo->gen->t_die)
		philo->act = calctime(&philo->tval) - philo->gen->tstlife;
	sem_post(philo->finishsim);
	regular_print("%s%ld %d died\n%s", philo);
	return (1);
}

int	philoeat(t_philo *philo)
{
	philo->lastmeal = calctime(&philo->tval) - philo->gen->tstlife;
	if ((philo->gen->eat_freq && philo->ate == philo->gen->eat_freq)
		|| philo->ate >= 10)
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
	philo->act = calctime(&philo->tval) - philo->gen->tstlife;
	while (philo->act <= philo->lastmeal + philo->gen->t_eat)
	{
		philo->act = calctime(&philo->tval) - philo->gen->tstlife;
		if (philo->act >= philo->lastmeal + philo->gen->t_eat)
		{
			philo->ate++;
			if ((philo->gen->eat_freq && philo->ate == philo->gen->eat_freq)
				|| philo->ate >= 10)
			{
				sem_post(philo->satisfied);
				break ;
			}
			break ;
		}
		if (philo->act >= philo->lastmeal + philo->gen->t_die)
			return (philokill(philo));
	}
	sem_post(philo->forkpile);
	sem_post(philo->forkpile);
	return (0);
}

int	philosleep(t_philo *philo)
{
	philo->lastsleep = calctime(&philo->tval) - philo->gen->tstlife;
	if ((philo->gen->eat_freq && philo->ate == philo->gen->eat_freq)
		|| philo->ate >= 10)
		usleep(30);
	careful_print("%s%ld %d is sleeping\n%s", philo);
	philo->act = calctime(&philo->tval) - philo->gen->tstlife;
	while (philo->act < philo->lastsleep + philo->gen->t_sleep
			&& philo->act < philo->lastmeal + philo->gen->t_die)
	{
		philo->act = calctime(&philo->tval) - philo->gen->tstlife;
		if (philo->act >= philo->lastmeal + philo->gen->t_die)
			return (philokill(philo));
	}
	return (0);
}

int	philothink(t_philo *philo)
{
	if ((philo->gen->eat_freq && philo->ate == philo->gen->eat_freq)
		|| philo->ate >= 10)
		usleep(30);
	philo->act = calctime(&philo->tval) - philo->gen->tstlife;
	careful_print("%s%ld %d is thinking\n%s", philo);
	if (philo->act >= philo->lastmeal + philo->gen->t_die)
		return (philokill(philo));
	return (0);
}

int philokill(t_philo *philo)
{
	sem_wait(philo->carefulprinting);
	sem_post(philo->finishsim);
	regular_print("%s%ld %d died\n%s", philo);
	return (1);
}