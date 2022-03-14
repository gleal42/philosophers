/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_sim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:33:56 by gleal             #+#    #+#             */
/*   Updated: 2022/03/14 19:30:46 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	check_finish_sim(t_all *all)
{
	while (1)
	{
		checkdeathsetminate(all);
		if (all->gen.endlife)
			break ;
	}
}

void	checkdeathsetminate(t_all *all)
{
	int	i;
	int	min;

	i = 0;
	min = 0;
	while (i < all->gen.philonbr)
	{
		if (all->philos[i].stat.dead)
		{
			all->gen.endlife = 1;
			usleep(1);
			all->gen.tendlife = calctime(&all->gen.tval) - all->gen.tstlife;
			printf("%ld %d died\n", (long)all->gen.tendlife, i + 1);
			break ;
		}
		if (i == 0 || all->philos[i].stat.ate < min)
			min = all->philos[i].stat.ate;
		i++;
	}
	if (all->gen.eat_freq && min >= all->gen.eat_freq)
		all->gen.endlife = 1;
}

void	finish_sim(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		pthread_join(all->philos[i].philo, NULL);
		i++;
	}
	i = 0;
	while (i < all->gen.philonbr)
	{
		pthread_mutex_destroy(&all->philos[i].own.fork);
		i++;
	}
	free(all->philos);
}
