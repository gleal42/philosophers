/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_sim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:33:56 by gleal             #+#    #+#             */
/*   Updated: 2022/03/15 17:00:41 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	check_finish_sim(t_all *all)
{
	while (1)
	{
		checkdeathsetminate(all);
		if (all->gen.endlife)
			return ;
	}
}

void	checkdeathsetminate(t_all *all)
{
	int	i;
	int	min;

	i = 0;
	pthread_mutex_lock(&all->eat);
	min = all->philos[0].stat.ate;
	pthread_mutex_unlock(&all->eat);
	while (i < all->gen.philonbr)
	{
		if (check_dead_philo(all, i))
			return ;
		pthread_mutex_lock(&all->eat);
		if (all->philos[i].stat.ate < min)
			min = all->philos[i].stat.ate;
		pthread_mutex_unlock(&all->eat);
		i++;
	}
	pthread_mutex_lock(&all->eat);
	if (all->gen.eat_freq && min >= all->gen.eat_freq)
	{
		pthread_mutex_lock(&all->death);
		all->gen.endlife = 1;
		pthread_mutex_unlock(&all->death);
	}
	pthread_mutex_unlock(&all->eat);
}

int	check_dead_philo(t_all *all, int i)
{
	pthread_mutex_lock(&all->death);
	if (all->philos[i].stat.dead)
	{
		all->gen.endlife = 1;
		all->gen.tendlife = calctime(&all->gen.tval) - all->gen.tstlife;
		printf("%ld %d died\n", (long)all->gen.tendlife, i + 1);
		pthread_mutex_unlock(&all->death);
		return (1);
	}
	pthread_mutex_unlock(&all->death);
	return (0);
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
		pthread_mutex_destroy(&all->philos[i].right);
		i++;
	}
	pthread_mutex_destroy(&all->death);
	pthread_mutex_destroy(&all->eat);
	free(all->philos);
}
