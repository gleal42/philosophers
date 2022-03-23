/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:53:55 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 22:18:07 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	check_ate_loop(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		pthread_mutex_lock(&all->satisfied);
		while (all->philos[i].stat.satisfied)
			i++;
		pthread_mutex_unlock(&all->satisfied);
		pthread_mutex_lock(&all->finishtype);
		if (all->simfinished)
		{
			pthread_mutex_unlock(&all->finishtype);
			return ;
		}
		pthread_mutex_unlock(&all->finishtype);
	}
	stop_sim_print(all, NULL, i);
	return ;
}

void	check_dead_loop(t_all *all)
{
	int	i;

	while (1)
	{
		i = 0;
		usleep(100);
		while (i < all->gen.philonbr)
		{
			pthread_mutex_lock(&all->philos[i].lastmeal);
			if (calctime(&all->gen)
				>= all->philos[i].stat.lastmeal + all->gen.t_die)
			{
				pthread_mutex_unlock(&all->philos[i].lastmeal);
				stop_sim_print(all, "%ld %d died\n", i);
				return ;
			}
			pthread_mutex_unlock(&all->philos[i].lastmeal);
			i++;
		}
	}
}
