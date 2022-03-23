/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:16:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 16:48:07 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	*philolife(t_philo *philo)
{
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
	double lastsleep;

	lastsleep = calctime(philo->gen);
	if (is_dead(philo))
		return (1);
	printf("%s%ld %d is sleeping\n%s", philo->clr,
		(long)(calctime(philo->gen)), philo->nbr, RESET_COLOR);
	while (calctime(philo->gen) <= lastsleep + philo->gen->t_sleep)
	{
		if (is_dead(philo))
			return (1);
	}
	return (0);
}

int	philothink(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	printf("%s%ld %d is thinking\n%s", philo->clr,
		(long)(calctime(philo->gen)), philo->nbr, RESET_COLOR);
	return (0);
}
