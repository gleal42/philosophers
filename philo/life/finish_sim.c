/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_sim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:33:56 by gleal             #+#    #+#             */
/*   Updated: 2022/03/22 17:47:13 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	check_ate_loop(t_all *all)
{
	while (1)
	{
		pthread_mutex_lock(&all->death);
		if (all->gen.endlife)
		{
			pthread_mutex_unlock(&all->death);
			return ;
		}
		pthread_mutex_unlock(&all->death);
		check_all_eat(all);
	}
}

void	check_all_eat(t_all *all)
{
	int	i;
	int	min;

	i = 0;
	pthread_mutex_lock(&all->eat);
	min = all->philos[0].stat.ate;
	pthread_mutex_unlock(&all->eat);
	while (i < all->gen.philonbr)
	{
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
		unlock_all_forks(all);
		pthread_mutex_unlock(&all->death);
	}
	pthread_mutex_unlock(&all->eat);
}

void	monitordie(t_all *all)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < all->gen.philonbr)
		{
			if (is_dead_gen(all))
				return ;
			if (did_philo_die(all, i))
				return ;
			i++;
		}
	}
}

int	did_philo_die(t_all *all, const int i)
{
	pthread_mutex_lock(&all->eat);
	if (calctime() - all->gen.tstlife
		>= all->philos[i].stat.lastmeal + all->gen.t_die)
	{
		pthread_mutex_unlock(&all->eat);
		pthread_mutex_lock(&all->death);
		all->gen.endlife = 1;
		unlock_all_forks(all);
		all->gen.tendlife = calctime() - all->gen.tstlife;
		printf("%ld %d died\n", (long)all->gen.tendlife, i + 1);
		pthread_mutex_unlock(&all->death);
		return (1);
	}
	pthread_mutex_unlock(&all->eat);
	return (0);
}

void	unlock_all_forks(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		pthread_mutex_unlock(&all->philos[i].right);
		i++;
	}
}
