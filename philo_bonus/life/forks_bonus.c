/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:31:49 by gleal             #+#    #+#             */
/*   Updated: 2022/03/14 22:11:47 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life_bonus.h"

void	philopickforks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right);
	philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	if (!philo->gen->endlife)
		printf("%s%ld %d has taken a fork\n%s", philo->clr,
			(long)philo->stat.act, philo->nbr, RESET_COLOR);
	if (philo->gen->philonbr == 1)
		return (starve(philo));
	pthread_mutex_lock(philo->left);
	philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	if (!philo->gen->endlife)
		printf("%s%ld %d has taken a fork\n%s", philo->clr,
			(long)philo->stat.act, philo->nbr, RESET_COLOR);
	if (!philo->gen->endlife)
		philoeat(philo, &philo->right, philo->left);
	else
		leave_forks_on_the_table(&philo->right, philo->left);
}

void	starve(t_philo *philo)
{
	while (philo->stat.act < philo->stat.lastmeal + philo->gen->t_die)
		philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	philo->stat.dead = 1;
	while (!philo->gen->endlife)
		;
	pthread_mutex_unlock(&philo->right);
}

void	leave_forks_on_the_table(pthread_mutex_t *right, pthread_mutex_t *left)
{
	pthread_mutex_unlock(right);
	pthread_mutex_unlock(left);
}
