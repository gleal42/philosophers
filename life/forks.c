/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:31:49 by gleal             #+#    #+#             */
/*   Updated: 2022/03/14 20:17:01 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	philopickforks(t_philo *philo)
{
	pthread_mutex_lock(&philo->own.fork);
	philo->own.using = 1;
	philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	if (!philo->gen->endlife)
		printf("%s%ld %d has taken a fork\n%s", philo->clr,
			(long)philo->stat.act, philo->nbr, RESET_COLOR);
	if (philo->gen->philonbr == 1)
		return (starve(philo));
	while (1)
	{
		if (!philo->right->using)
		{
			pick_fork(philo, philo->right);
			break ;
		}
		if (!philo->left->using)
		{
			pick_fork(philo, philo->left);
			break ;
		}
	}
}

void	starve(t_philo *philo)
{
	while (philo->stat.act < philo->stat.lastmeal + philo->gen->t_die)
		philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	philo->stat.dead = 1;
	while (!philo->gen->endlife)
		;
	pthread_mutex_unlock(&philo->own.fork);
}

void	pick_fork(t_philo *philo, t_fork *pickedfork)
{
	pickedfork->using = 1;
	pthread_mutex_lock(&pickedfork->fork);
	philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	if (!philo->gen->endlife)
		printf("%s%ld %d has taken a fork\n%s", philo->clr,
			(long)philo->stat.act, philo->nbr, RESET_COLOR);
	if (!philo->gen->endlife)
		philoeat(philo, &philo->own, pickedfork);
	else
	{
		pthread_mutex_unlock(&philo->own.fork);
		pthread_mutex_unlock(&pickedfork->fork);
		philo->own.using = 0;
		pickedfork->using = 0;
	}
}

void	leave_forks_on_the_table(t_fork *forkone, t_fork *forktwo)
{
	pthread_mutex_unlock(&forkone->fork);
	pthread_mutex_unlock(&forktwo->fork);
	forkone->using = 0;
	forktwo->using = 0;
}
