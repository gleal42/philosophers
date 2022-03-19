/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:16:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/19 21:15:21 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life_bonus.h"

void	*philolife(t_philo *philo)
{
	int i;

	i = 0;
	while (i < 20)
	{
		philopickforks(philo);
		philosleep(philo);
		philothink(philo);
		i++;
	}
	return ((void *)0);
}

void	philopickforks(t_philo *philo)
{
	philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	printf("%s%ld %d has taken a fork\n%s", philo->clr,
		(long)philo->stat.act, philo->nbr, RESET_COLOR);
	if (philo->gen->philonbr == 1)
		return (starve(philo));
	philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	printf("%s%ld %d has taken a fork\n%s", philo->clr,
		(long)philo->stat.act, philo->nbr, RESET_COLOR);
	philoeat(philo);
}

void	starve(t_philo *philo)
{
	while (philo->stat.act < philo->stat.lastmeal + philo->gen->t_die)
		philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
		philo->stat.died++;
}

void	philoeat(t_philo *philo)
{
	philo->stat.lastmeal = calctime(&philo->tval) - philo->gen->tstlife;
	philo->stat.act = philo->stat.lastmeal;
	printf("%s%ld %d is eating\n%s", philo->clr,
			(long)philo->stat.lastmeal, philo->nbr, RESET_COLOR);
	eating(philo);
	if (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die)
		philo->stat.died++;
}

void	eating(t_philo *philo)
{
	while (philo->stat.act <= philo->stat.lastmeal + philo->gen->t_eat)
	{
		philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
		if (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_eat)
		{
			philo->stat.ate++;
			printf("%s%d already ate %d times\n%s", philo->clr, philo->nbr, philo->stat.ate, RESET_COLOR);
			if ((philo->gen->eat_freq && philo->stat.ate == philo->gen->eat_freq)
				|| philo->stat.ate >= 10)
			{
				sem_post(philo->finished_eating);
				break ;
			}
			break ;
		}
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
		philo->stat.died++;

}

void	philothink(t_philo *philo)
{
	philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	printf("%s%ld %d is thinking\n%s", philo->clr,
		(long)philo->stat.act, philo->nbr, RESET_COLOR);
	if (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die)
		philo->stat.died++;
}
