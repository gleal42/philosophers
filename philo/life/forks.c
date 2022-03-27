/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:08:14 by gleal             #+#    #+#             */
/*   Updated: 2022/03/27 03:47:15 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int	philopickforks(t_philo *philo)
{
	if (try_pick_first_fork(philo, &philo->right) != 0)
		return (1);
	if (try_pick_second_fork(philo, &philo->right, philo->left) != 0)
		return (1);
	if (philoeat(philo, &philo->right, philo->left))
		return (1);
	return (0);
}

int	try_pick_first_fork(t_philo *philo, pthread_mutex_t *fstfork)
{
	pthread_mutex_lock(fstfork);
	if (protected_printing("%s%ld %d has taken a fork 🔱\n%s", philo))
	{
		pthread_mutex_unlock(fstfork);
		return (1);
	}
	return (0);
}

int	try_pick_second_fork(t_philo *philo,
	pthread_mutex_t *fstfork, pthread_mutex_t *secfork)
{
	pthread_mutex_lock(secfork);
	if (protected_printing("%s%ld %d has taken a fork 🔱\n%s", philo))
	{
		pthread_mutex_unlock(fstfork);
		pthread_mutex_unlock(secfork);
		return (1);
	}
	return (0);
}

int	philoeat(t_philo *philo, pthread_mutex_t *fstfork, pthread_mutex_t *secfork)
{
	pthread_mutex_lock(philo->lastmeal);
	philo->stat.lastmeal = calctime(philo->gen);
	pthread_mutex_unlock(philo->lastmeal);
	if (protected_printing("%s%ld %d is eating 🥙\n%s", philo))
	{
		leave_forks_on_the_table(fstfork, secfork);
		return (1);
	}
	while (calctime(philo->gen) < philo->stat.lastmeal + philo->gen->t_eat)
		;
	philo->stat.ate++;
	if (philo->gen->eat_freq && philo->stat.ate >= philo->gen->eat_freq)
	{
		pthread_mutex_lock(philo->satisfied);
		philo->stat.satisfied = 1;
		pthread_mutex_unlock(philo->satisfied);
	}
	leave_forks_on_the_table(fstfork, secfork);
	return (0);
}
