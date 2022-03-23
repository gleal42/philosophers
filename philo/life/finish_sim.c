/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_sim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:53:55 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 17:02:33 by gleal            ###   ########.fr       */
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
		if (all->philos[i].stat.satisfied)
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
		usleep(100);
		i = 0;
		while (i < all->gen.philonbr)
		{
			pthread_mutex_lock(&all->finishtype);
			pthread_mutex_lock(&all->philos[i].lastmeal);
			if (calctime(&all->gen)
				>= all->philos[i].stat.lastmeal + all->gen.t_die)
			{
				pthread_mutex_unlock(&all->philos[i].lastmeal);
				if (lock_finishtype(all))
					return ;
				stop_activity(all);
				printf("%ld %d died\n", (long)calctime(&all->gen), i + 1);
				unlock_all_forks(all);
				restart_activity(all);
				pthread_mutex_unlock(&all->finishtype);
				return ;
			}
			pthread_mutex_unlock(&all->philos[i].lastmeal);
			pthread_mutex_unlock(&all->finishtype);
			i++;
		}
	}
}

int	lock_finishtype(t_all *all)
{
	if (all->simfinished)
	{
		pthread_mutex_unlock(&all->finishtype);
		return (1);
	}
	all->simfinished = 1;
	return (0);
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
			pthread_mutex_unlock(&all->philos[i].right);
			all->philos[i].stat.locked_right = 0;
		}
		pthread_mutex_unlock(&all->philos[i].checkfork);
		pthread_mutex_lock(&all->philos[(i+1) % all->gen.philonbr].checkfork);
		if (all->philos[(i+1) % all->gen.philonbr].stat.locked_left == 1)
		{
			pthread_mutex_unlock(all->philos[(i+1) % all->gen.philonbr].left);
			all->philos[(i+1) % all->gen.philonbr].stat.locked_left = 0;
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
		i++;
	}
	pthread_mutex_unlock(&all->finishtype);
	pthread_mutex_destroy(&all->finishtype);
	pthread_mutex_destroy(&all->satisfied);
	free(all->philos);
}
