/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:16:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/22 18:27:34 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life_bonus.h"

int	philolife(t_philo *philo)
{
	philo->act = 0;
	philo->lastmeal = 0;
	philo->ate = 0;
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

	lastsleep = calctime() - philo->gen->tstlife;
	if (lastsleep >= philo->lastmeal + philo->gen->t_die)
		return (philokill(philo));
	careful_print("%s%ld %d is sleeping\n%s", philo);
	while (philo->act <= lastsleep + philo->gen->t_sleep)
	{
		philo->act = calctime() - philo->gen->tstlife;
		if (philo->act >= philo->lastmeal + philo->gen->t_die)
			return (philokill(philo));
	}
	return (0);
}

int	philothink(t_philo *philo)
{
	if (calctime() - philo->gen->tstlife >= philo->lastmeal + philo->gen->t_die)
		return (philokill(philo));
	careful_print("%s%ld %d is thinking\n%s", philo);
	return (0);
}

int	philokill(t_philo *philo)
{
	sem_wait(philo->sm.carefulprinting);
	regular_print("%s%ld %d died\n%s", philo);
	sem_post(philo->sm.finishsim);
	return (1);
}
