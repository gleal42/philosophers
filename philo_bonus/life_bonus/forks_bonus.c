/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:31:49 by gleal             #+#    #+#             */
/*   Updated: 2022/03/16 19:13:09 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life_bonus.h"

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
	kill(0, SIGINT);
}
