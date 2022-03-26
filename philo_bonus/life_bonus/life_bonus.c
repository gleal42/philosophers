/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:16:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/26 19:17:09 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life_bonus.h"

int	philolife(t_philo *philo)
{
	if (philo->gen->philonbr == 1)
		return (starve(philo));
	if (create_philo_mutexes(philo) == EXIT_FAILURE)
		return (-1);
	pthread_create(&philo->mon_finish_sim, NULL,
		(void *)monitor_own_death, philo);
	pthread_detach(philo->mon_finish_sim);
	pthread_create(&philo->mon_own_death, NULL,
		(void *)monitor_finish_sim, philo);
	pthread_detach(philo->mon_own_death);
	while (1)
	{
		if (philopickforks(philo))
			exit (philo->nbr - 1);
		if (philosleep(philo))
			exit (philo->nbr - 1);
		if (philothink(philo))
			exit (philo->nbr - 1);
	}
	exit (0);
}

int	philosleep(t_philo *philo)
{
	double	lastsleep;

	lastsleep = calctime(philo->gen);
	if (careful_print("%s%ld %d is sleeping 🛌\n%s", philo))
		return (1);
	while (calctime(philo->gen) < lastsleep + philo->gen->t_sleep)
		;
	return (0);
}

int	philothink(t_philo *philo)
{
	if (careful_print("%s%ld %d is thinking 🤔\n%s", philo))
		return (1);
	return (0);
}

void	monitor_own_death(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->lastmealtime);
		if (calctime(philo->gen) >= philo->stat.lastmeal + philo->gen->t_die)
		{
			pthread_mutex_unlock(&philo->lastmealtime);
			sem_wait(philo->sm.carefulprinting);
			pthread_mutex_lock(&philo->isdone);
			if (philo->stat.died == 1)
			{
				pthread_mutex_unlock(&philo->isdone);
				return ;
			}
			pthread_mutex_unlock(&philo->isdone);
			regular_print("%s%ld %d died 💀\n%s", philo);
			philo_drop_forks(philo);
			pthread_mutex_destroy(&philo->lastmealtime);
			pthread_mutex_destroy(&philo->isdone);
			pthread_mutex_destroy(&philo->forksheldcheck);
			exit(philo->nbr - 1);
			return ;
		}
		pthread_mutex_unlock(&philo->lastmealtime);
	}
}

void	monitor_finish_sim(t_philo *philo)
{
	int	i;

	sem_wait(philo->sm.finishsim);
	pthread_mutex_lock(&philo->isdone);
	philo->stat.died = 1;
	pthread_mutex_unlock(&philo->isdone);
	pthread_mutex_lock(&philo->forksheldcheck);
	i = 0;
	while (i < philo->stat.forks_held)
	{
		sem_post(philo->sm.forkpile);
		i++;
	}
	philo->stat.forks_held = 0;
	pthread_mutex_unlock(&philo->forksheldcheck);
	return ;
}
