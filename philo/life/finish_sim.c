/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_sim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:53:55 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 21:18:48 by gleal            ###   ########.fr       */
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
	pthread_mutex_lock(&all->finishtype);
	all->simfinished = 1;
	stop_activity(all);
	unlock_all_forks(all);
	restart_activity(all);
	pthread_mutex_unlock(&all->finishtype);
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
				pthread_mutex_lock(&all->finishtype);
				if (all->simfinished)
				{
					pthread_mutex_unlock(&all->finishtype);
					return ;
				}
				all->simfinished = 1;
				stop_activity(all);
				printf("%ld %d died\n", (long)calctime(&all->gen), i + 1);
				unlock_all_forks(all);
				restart_activity(all);
				pthread_mutex_unlock(&all->finishtype);
				return ;
			}
			pthread_mutex_unlock(&all->philos[i].lastmeal);
			i++;
		}
	}
}

void	stop_activity(t_all *all)
{
	int i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		pthread_mutex_lock(&all->philos[i].died);
		all->philos[i].stat.dead = 1;
		i++;
	}
}

void	restart_activity(t_all *all)
{
	int i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		pthread_mutex_unlock(&all->philos[i].died);
		i++;
	}
}

void	unlock_all_forks(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		pthread_mutex_lock(&all->philos[i].checkfork);
		if (all->philos[i].stat.locked_right == 1)
		{
			all->philos[i].stat.locked_right = 0;
			pthread_mutex_unlock(&all->philos[i].right);
		}
		pthread_mutex_unlock(&all->philos[i].checkfork);
		pthread_mutex_lock(&all->philos[(i+1) % all->gen.philonbr].checkfork);
		if (all->philos[(i+1) % all->gen.philonbr].stat.locked_left == 1)
		{
			all->philos[(i+1) % all->gen.philonbr].stat.locked_left = 0;
			pthread_mutex_unlock(all->philos[(i+1) % all->gen.philonbr].left);
		}
		pthread_mutex_unlock(&all->philos[(i+1) % all->gen.philonbr].checkfork);
		i++;
	}
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
		pthread_mutex_destroy(&all->philos[i].died);
		pthread_mutex_destroy(&all->philos[i].lastmeal);
		pthread_mutex_destroy(&all->philos[i].checkfork);
		i++;
	}
	pthread_mutex_destroy(&all->finishtype);
	pthread_mutex_destroy(&all->satisfied);
	free(all->philos);
}
