/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finishsim_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:29:21 by gleal             #+#    #+#             */
/*   Updated: 2022/03/26 18:30:35 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

void	unlock_finish_simulation(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		sem_post(all->philo.sm.finishsim);
		i++;
	}
}

void	waitremainphilo(t_all *all, int *philoindex)
{
	int	i;

	i = 0;
	while (i < all->philo.gen->philonbr)
	{
		if (i == *philoindex)
			i++;
		waitpid(all->philo.proc[i], philoindex, 0);
		i++;
	}
}

void	unlock_satisfied(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		sem_post(all->philo.sm.satisfied);
		i++;
	}
}

void	unlock_carefulprinting(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		sem_post(all->philo.sm.carefulprinting);
		i++;
	}
}

void	philo_drop_forks(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->forksheldcheck);
	while (i < philo->stat.forks_held)
	{
		sem_post(philo->sm.forkpile);
		i++;
	}
	philo->stat.forks_held = 0;
	pthread_mutex_unlock(&philo->forksheldcheck);
}
