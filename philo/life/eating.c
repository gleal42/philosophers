/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:08:46 by gleal             #+#    #+#             */
/*   Updated: 2022/03/22 17:05:30 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	philoeat(t_philo *philo, pthread_mutex_t *right, pthread_mutex_t *left)
{
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(philo->eat);
	philo->stat.lastmeal = calctime() - philo->gen->tstlife;
	pthread_mutex_unlock(philo->eat);
	if (is_dead(philo))
		return ;
	philo->stat.act = philo->stat.lastmeal;
	printf("%s%ld %d is eating\n%s", philo->clr,
		(long)philo->stat.lastmeal, philo->nbr, RESET_COLOR);
	if (eating(philo))
		return ;
	leave_forks_on_the_table(right, left);
}

int	starve(t_philo *philo)
{
	death_bed(philo);
	return (1);
}

int	eating(t_philo *philo)
{
	while (philo->stat.act < philo->stat.lastmeal + philo->gen->t_eat)
	{
		if (is_dead(philo))
		{
			leave_forks_on_the_table(&philo->right, philo->left);
			return (1);
		}
		philo->stat.act = calctime() - philo->gen->tstlife;
		if (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_eat)
		{
			pthread_mutex_lock(philo->eat);
			philo->stat.ate++;
			pthread_mutex_unlock(philo->eat);
			usleep(10);
		}
	}
	return (0);
}
