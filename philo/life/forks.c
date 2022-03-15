/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:08:14 by gleal             #+#    #+#             */
/*   Updated: 2022/03/15 17:13:27 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	philopickforks(t_philo *philo)
{
	if (try_pick_first_fork(philo) != 0)
		return ;
	if (try_pick_second_fork(philo) != 0)
		return ;
	if (is_dead(philo))
	{
		leave_forks_on_the_table(&philo->right, philo->left);
		return ;
	}
	philoeat(philo, &philo->right, philo->left);
}

int	try_pick_first_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->right);
	philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->right);
		return (1);
	}
	printf("%s%ld %d has taken a fork\n%s", philo->clr,
		(long)philo->stat.act, philo->nbr, RESET_COLOR);
	return (0);
}

int	try_pick_second_fork(t_philo *philo)
{
	if (philo->gen->philonbr == 1)
		return (starve(philo));
	pthread_mutex_lock(philo->left);
	philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	if (is_dead(philo))
	{
		leave_forks_on_the_table(&philo->right, philo->left);
		return (1);
	}
	printf("%s%ld %d has taken a fork\n%s", philo->clr,
		(long)philo->stat.act, philo->nbr, RESET_COLOR);
	return (0);
}
