/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:08:14 by gleal             #+#    #+#             */
/*   Updated: 2022/03/24 20:45:22 by gleal            ###   ########.fr       */
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
	if (protected_printing("%s%ld %d has taken a fork 🔱\n%s", philo))
	{
		pthread_mutex_unlock(&philo->right);
		return (1);
	}
	return (0);
}

int	try_pick_second_fork(t_philo *philo)
{
	if (philo->gen->philonbr == 1)
		return (starve(philo));
	pthread_mutex_lock(philo->left);
	if (protected_printing("%s%ld %d has taken a fork 🔱\n%s", philo))
	{
		pthread_mutex_unlock(&philo->right);
		pthread_mutex_unlock(philo->left);
		return (1);
	}
	return (0);
}

int	philoeat(t_philo *philo, pthread_mutex_t *right, pthread_mutex_t *left)
{
	pthread_mutex_lock(philo->lastmeal);
	philo->stat.lastmeal = calctime(philo->gen);
	pthread_mutex_unlock(philo->lastmeal);
	if (protected_printing("%s%ld %d is eating 🥙\n%s", philo))
	{
		pthread_mutex_unlock(&philo->right);
		pthread_mutex_unlock(philo->left);
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
	leave_forks_on_the_table(right, left);
	return (0);
}
