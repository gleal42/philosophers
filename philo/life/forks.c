/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:08:14 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 02:46:06 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int	philopickforks(t_philo *philo)
{
	if (try_pick_first_fork(philo) != 0)
		return (1);
	if (try_pick_second_fork(philo) != 0)
		return (1);
	if (philoeat(philo, &philo->right, philo->left))
		return (1);
	return (0);
}

int	try_pick_first_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->right);
	pthread_mutex_lock(&philo->checkfork);
	philo->stat.locked_right = 1;
	pthread_mutex_unlock(&philo->checkfork);
	philo->stat.act = calctime(philo->gen);
	if (is_dead(philo))
		return (1);
	//printf("%ld %d cmooooooooooon\n", (long)calctime(philo->gen), philo->nbr);
	printf("%s%ld %d has taken a fork\n%s", philo->clr,
		(long)philo->stat.act, philo->nbr, RESET_COLOR);
	return (0);
}

int	try_pick_second_fork(t_philo *philo)
{
	if (philo->gen->philonbr == 1)
		return (starve(philo));
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(&philo->checkfork);
	philo->stat.locked_left = 1;
	pthread_mutex_unlock(&philo->checkfork);
	if (is_dead(philo))
		return (1);
	philo->stat.act = calctime(philo->gen);
	printf("%s%ld %d has taken a fork\n%s", philo->clr,
		(long)philo->stat.act, philo->nbr, RESET_COLOR);
	return (0);
}

int	philoeat(t_philo *philo, pthread_mutex_t *right, pthread_mutex_t *left)
{
	pthread_mutex_lock(&philo->lastmeal);
	philo->stat.lastmeal = calctime(philo->gen);
	pthread_mutex_unlock(&philo->lastmeal);
	if (is_dead(philo))
		return (1);
	printf("%s%ld %d is eating\n%s", philo->clr,
		(long)philo->stat.lastmeal, philo->nbr, RESET_COLOR);
	if (eating(philo))
		return (1);
	leave_forks_on_the_table(right, left);
	pthread_mutex_lock(&philo->checkfork);
	philo->stat.locked_right = 0;
	philo->stat.locked_left = 0;
	pthread_mutex_unlock(&philo->checkfork);
	return (0);
}