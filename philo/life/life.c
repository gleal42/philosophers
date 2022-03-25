/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:16:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/25 00:53:12 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	*philolife(void *ptr)
{
	t_philo *philo;
	pthread_mutex_t	*fstfork;
	pthread_mutex_t	*secfork;

	philo = (t_philo *)ptr;
	if (philo->gen->philonbr == 1)
	{
		usleep(philo->gen->t_die * 1000);
		printf("%ld %d died \n", calctime(philo->gen), philo->nbr);
		return ((void *)0);
	}
	if (philo->nbr % 2)
	{
		fstfork = &philo->right;
		secfork = philo->left;
	}
	else
	{
		fstfork = philo->left;
		secfork = &philo->right;
	}
	while (1)
	{
		philopickforks(philo, fstfork, secfork);
		philoeat(philo, fstfork, secfork);
		philosleep(philo);
		philothink(philo);
	}
	return ((void *)0);
}

int	philopickforks(t_philo *philo, pthread_mutex_t *fstfork, pthread_mutex_t *secfork)
{
	pthread_mutex_lock(fstfork);
	printf("%ld %d has taken a fork \n", calctime(philo->gen), philo->nbr);
	pthread_mutex_lock(secfork);
	printf("%ld %d has taken a fork \n", calctime(philo->gen), philo->nbr);
	return (0);
}

int	philoeat(t_philo *philo, pthread_mutex_t *fstfork, pthread_mutex_t *secfork)
{
	philo->stat.lastmeal = calctime(philo->gen);
	printf("%ld %d is eating \n", calctime(philo->gen), philo->nbr);
	while (calctime(philo->gen) < philo->stat.lastmeal + philo->gen->t_eat)
		;
	philo->stat.ate++;
	if (philo->gen->eat_freq && philo->stat.ate >= philo->gen->eat_freq)
	{
		pthread_mutex_lock(philo->satisfied);
		philo->stat.satisfied = 1;
		pthread_mutex_unlock(philo->satisfied);
	}
	pthread_mutex_unlock(fstfork);
	pthread_mutex_unlock(secfork);
	return (0);
}

int	philosleep(t_philo *philo)
{
	philo->stat.lastsleep = calctime(philo->gen);
	printf("%ld %d is sleeping \n", calctime(philo->gen), philo->nbr);
	while (calctime(philo->gen) < philo->stat.lastsleep + philo->gen->t_sleep)
		;
	return (0);
}

int	philothink(t_philo *philo)
{
	printf("%ld %d is thinking \n", (calctime(philo->gen)), philo->nbr);
	if (philo->gen->philonbr % 2 && calctime(philo->gen) + philo->gen->t_eat > philo->gen->t_die)
	{
		while (calctime(philo->gen) < philo->stat.lastmeal + philo->gen->t_die)
			;
		printf("%ld %d died \n", calctime(philo->gen), philo->nbr);
	}
	return (0);
}
