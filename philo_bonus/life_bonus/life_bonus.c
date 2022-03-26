/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:16:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/26 16:21:55 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life_bonus.h"

int	philolife(t_philo *philo)
{
	if (philo->gen->philonbr == 1)
		return (starve(philo));
	pthread_mutex_init(&philo->lastmealtime, NULL);
	pthread_mutex_init(&philo->isdone, NULL);
	pthread_create(&philo->mon_finish_sim, NULL, (void *)monitor_own_death, philo);
	pthread_detach(philo->mon_finish_sim);
	pthread_create(&philo->mon_own_death, NULL, (void *)monitor_finish_sim, philo);
	pthread_detach(philo->mon_own_death);
	while (1)
	{
		if (philopickforks(philo))
			exit (1);
		if (philosleep(philo))
			exit (1);
		if (philothink(philo))
			exit (1);
	}
	exit (0);
}

int	philosleep(t_philo *philo)
{
	double	lastsleep;

	lastsleep = calctime(philo->gen);
	if (careful_print("%s%ld %d is sleeping\n%s", philo))
		return (1);
	while (calctime(philo->gen) < lastsleep + philo->gen->t_sleep)
		;
	return (0);
}

int	philothink(t_philo *philo)
{
	if (careful_print("%s%ld %d is thinking\n%s", philo))
		return (1);
	return (0);
}

void	monitor_own_death(t_philo *philo)
{
	while (1)
	{
		if (calctime(philo->gen) >= philo->stat.lastmeal + philo->gen->t_die)
		{
			sem_wait(philo->sm.carefulprinting);
			pthread_mutex_lock(&philo->isdone);
			if (philo->stat.died == 1)
			{
				//printf("%ld yooo philo 🏆\n", (long)calctime(philo->gen));
				pthread_mutex_unlock(&philo->isdone);
				return ;
			}
			pthread_mutex_unlock(&philo->isdone);
			regular_print("%s%ld %d died\n%s", philo);
			pthread_mutex_destroy(&philo->lastmealtime);
			pthread_mutex_destroy(&philo->isdone);
			exit(philo->nbr-1);
			return ;
		}
	}
}

void	monitor_finish_sim(t_philo *philo)
{
	sem_wait(philo->sm.finishsim);
	pthread_mutex_lock(&philo->isdone);
	philo->stat.died = 1;
	pthread_mutex_unlock(&philo->isdone);
	return ;
}
