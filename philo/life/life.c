/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:16:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/25 16:57:36 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	*philolife(t_philo *philo)
{
	pthread_mutex_t	*fstfork;
	pthread_mutex_t	*secfork;

	if (philo->gen->philonbr == 1)
		return (starve(philo));
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
		if (philopickforks(philo, fstfork, secfork))
			return ((void *)0);
		if (philosleep(philo))
			return ((void *)0);
		if (philothink(philo))
			return ((void *)0);
	}
	return ((void *)0);
}
//printf("%ld YOOOOOOOOO\n" ,(long)calctime(philo->gen));

void	*starve(t_philo *philo)
{
	pthread_mutex_lock(&philo->right);
	if (protected_printing("%s%ld %d has taken a fork 🔱\n%s", philo))
	{
		pthread_mutex_unlock(&philo->right);
		return ((void *)0);
	}
	pthread_mutex_unlock(&philo->right);
	death_bed(philo);
	return ((void *)0);
}

int	philosleep(t_philo *philo)
{
	double	lastsleep;

	lastsleep = calctime(philo->gen);
	if (protected_printing("%s%ld %d is sleeping 🛌\n%s", philo))
		return (1);
	while (calctime(philo->gen) < lastsleep + philo->gen->t_sleep)
		;
	return (0);
}

int	philothink(t_philo *philo)
{
	if (protected_printing("%s%ld %d is thinking 🤔\n%s", philo) == EXIT_FAILURE)
		return (1);
	return (0);
}

int	protected_printing(const char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->finishsim);
	if (!philo->gen->endlife)
	{
		printf(str, philo->clr,
			(long)(calctime(philo->gen)), philo->nbr, RESET);
		pthread_mutex_unlock(philo->finishsim);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(philo->finishsim);
		return (1);
	}
}
