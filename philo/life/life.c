/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:16:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/25 01:03:18 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

//printf("%ld %ld YOOOOOOOOO\n" ,(long)calctime(philo->gen) ,(long)philo->gen->t_die);

void	*philolife(t_philo *philo)
{
/*	t_philo *philo;
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
	}*/
	if (philo->nbr % 2 == 0)
		usleep(philo->gen->t_eat * 1000);
	while (1)
	{
		if (philopickforks(philo))
			return ((void *)0);
		if (philosleep(philo))
			return ((void *)0);
		if (philothink(philo))
			return ((void *)0);
	}
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
		printf(str, philo->clr, (long)(calctime(philo->gen)), philo->nbr, RESET_COLOR);
		pthread_mutex_unlock(philo->finishsim);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(philo->finishsim);
		return (1);
	}
}

int	starve(t_philo *philo)
{
	death_bed(philo);
	return (1);
}