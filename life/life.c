/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:53:40 by gleal             #+#    #+#             */
/*   Updated: 2022/03/11 01:25:05 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int	initlife(int argc, char **argv, t_all *all)
{
	all->gen.endlife = 0;
	all->gen.stlife = calctime(&all->gen.tval);
	all->gen.nbr = ft_atoi(argv[1]);
	all->gen.t_eat = ft_atoi(argv[3]);
	all->gen.t_sleep = ft_atoi(argv[4]);
	all->gen.t_die = ft_atoi(argv[2]);
	if (argc == 6)
	{
		all->gen.eat_freq = ft_atoi(argv[5]);
		if (all->gen.eat_freq == 0)
			return (1);
	}
	else
		all->gen.eat_freq = 0;
	all->philos.gen = &all->gen;
	return (0);
}

void	*philolife(t_philo *philo)
{
	while (!philo->gen->endlife)
	{
		if (!philo->gen->endlife)
			philoeat(philo);
		if (!philo->gen->endlife)
			philosleep(philo);
		if (!philo->gen->endlife)
			philothink(philo);
	}
	return ((void *)0);
}

void	philoeat(t_philo *philo)
{
	int	ate;

	ate = 0;
	philo->stat.lastmeal = calctime(&philo->tval) - philo->gen->stlife;
	philo->stat.act = philo->stat.lastmeal;
	printf("%ld is eating\n", (long)philo->stat.lastmeal);
	while (philo->stat.act < philo->stat.lastmeal + philo->gen->t_eat
		&& philo->stat.act < philo->stat.lastmeal + philo->gen->t_die)
	{
		philo->stat.act = calctime(&philo->tval) - philo->gen->stlife;
		if (philo->stat.act >= philo->stat.lastmeal
			+ philo->gen->t_eat - 10 && !ate)
		{
			philo->stat.ate++;
			ate++;
		}
	}
	if (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die)
	{
		philo->stat.dead = 1;
		printf("%ld died\n", (long)philo->stat.lastmeal);
	}
}

void	philosleep(t_philo *philo)
{
	philo->stat.lastsleep = calctime(&philo->tval) - philo->gen->stlife;
	philo->stat.act = philo->stat.lastsleep;
	printf("%ld is sleeping\n", (long)philo->stat.lastsleep);
	while (philo->stat.act < philo->stat.lastsleep + philo->gen->t_sleep
		&& philo->stat.act < philo->stat.lastmeal + philo->gen->t_die)
		philo->stat.act = calctime(&philo->tval) - philo->gen->stlife;
	if (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die)
	{
		philo->stat.dead = 1;
		printf("%ld died\n", (long)philo->stat.lastmeal);
	}
}

void	philothink(t_philo *philo)
{
	philo->stat.act = calctime(&philo->tval) - philo->gen->stlife;
	printf("%ld is thinking\n", (long)philo->stat.lastsleep);
	if (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die)
	{
		philo->stat.dead = 1;
		printf("%ld died\n", (long)philo->stat.lastmeal);
	}
}
