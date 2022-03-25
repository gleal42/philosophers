/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:16:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/25 21:58:53 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life_bonus.h"

int	philolife(t_philo *philo)
{
	pthread_mutex_init(&philo->lastmeal_m, NULL);
	pthread_mutex_init(&philo->checkowndeath_m, NULL);
	pthread_create(&philo->monitor_finish_sim, NULL, (void *)monitor_own_death, philo);
	pthread_detach(philo->monitor_finish_sim);
	pthread_create(&philo->monitor_own_death, NULL, (void *)monitor_finish_sim, philo);
	pthread_detach(philo->monitor_own_death);
	while (1)
	{
		if (philopickforks(philo))
			return (1);
		if (philosleep(philo))
			return (1);
		if (philothink(philo))
			return (1);
	}
	return (0);
}

int	philosleep(t_philo *philo)
{
	double	lastsleep;

	lastsleep = calctime(philo->gen);
	careful_print("%s%ld %d is sleeping\n%s", philo);
	while (calctime(philo->gen) < lastsleep + philo->gen->t_sleep)
		;
	return (0);
}

int	philothink(t_philo *philo)
{
	careful_print("%s%ld %d is thinking\n%s", philo);
	return (0);
}

void	monitor_own_death(t_philo *philo)
{
	int i;

	while (1)
	{
		if (calctime(philo->gen) >= philo->stat.lastmeal + philo->gen->t_die)
		{
			sem_wait(philo->sm.carefulprinting);
			regular_print("%s%ld %d died\n%s", philo);
			i = 0;
			while (i < philo->gen->philonbr)
			{
				sem_post(philo->sm.finishsim);
				i++;
			}
			return ;
		}
	}
}

void	monitor_finish_sim(t_philo *philo)
{
	sem_wait(philo->sm.finishsim);
	pthread_mutex_destroy(&philo->lastmeal_m);
	pthread_mutex_destroy(&philo->checkowndeath_m);
	exit(philo->nbr-1);
	return ;
	
}
