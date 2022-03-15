/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:08:46 by gleal             #+#    #+#             */
/*   Updated: 2022/03/15 17:15:01 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	philoeat(t_philo *philo, pthread_mutex_t *right, pthread_mutex_t *left)
{
	philo->stat.lastmeal = calctime(&philo->tval) - philo->gen->tstlife;
	philo->stat.act = philo->stat.lastmeal;
	if (is_dead(philo))
	{
		leave_forks_on_the_table(right, left);
		return ;
	}
	printf("%s%ld %d is eating\n%s", philo->clr,
		(long)philo->stat.lastmeal, philo->nbr, RESET_COLOR);
	eating(philo);
	pthread_mutex_lock(philo->death);
	if (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_die)
	{
		philo->stat.dead = 1;
		pthread_mutex_unlock(philo->death);
		leave_forks_on_the_table(right, left);
		return ;
	}
	pthread_mutex_unlock(philo->death);
	leave_forks_on_the_table(right, left);
}

int	starve(t_philo *philo)
{
	while (philo->stat.act < philo->stat.lastmeal + philo->gen->t_die)
		philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
	pthread_mutex_lock(philo->death);
	philo->stat.dead = 1;
	pthread_mutex_unlock(philo->death);
	death_bed(philo);
	return (1);
}

void	eating(t_philo *philo)
{
	while (philo->stat.act < philo->stat.lastmeal + philo->gen->t_eat
		&& philo->stat.act < philo->stat.lastmeal + philo->gen->t_die)
	{
		if (is_dead(philo))
		{
			leave_forks_on_the_table(&philo->right, philo->left);
			return ;
		}
		philo->stat.act = calctime(&philo->tval) - philo->gen->tstlife;
		if (philo->stat.act >= philo->stat.lastmeal + philo->gen->t_eat)
		{
			pthread_mutex_lock(philo->eat);
			philo->stat.ate++;
			pthread_mutex_unlock(philo->eat);
			usleep(10);
		}
	}
}
