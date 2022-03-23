/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_sim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:33:56 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 00:53:35by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	check_ate_loop(t_all *all)
{
	int	i;
	int	min;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&all->finishtype);
		while (i < all->gen.philonbr)
		{
			pthread_mutex_lock(&all->ate);
			if (i == 0 || all->philos[i].stat.ate < min)
				min = all->philos[i].stat.ate;
			pthread_mutex_unlock(&all->ate);
			i++;
		}
		if (min >= all->gen.eat_freq)
		{
			if (all->simfinished)
				return ;
			all->simfinished = 1;
			stop_activity(all);
			restart_activity(all);
			unlock_all_forks(all);
			pthread_mutex_unlock(&all->finishtype);
			return ;
		}
		pthread_mutex_unlock(&all->finishtype);
	}
}

void	check_dead_loop(t_all *all)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < all->gen.philonbr)
		{
			pthread_mutex_lock(&all->finishtype);
			pthread_mutex_lock(&all->philos[i].lastmeal);
			if (calctime(&all->gen) >= all->philos[i].stat.lastmeal + all->gen.t_die)
			{
				pthread_mutex_unlock(&all->philos[i].lastmeal);
				if (all->simfinished)
					return ;
				all->simfinished = 1;
				stop_activity(all);
				printf("%ld %d died\n", (long)calctime(&all->gen), i + 1);
				restart_activity(all);
				unlock_all_forks(all);
				pthread_mutex_unlock(&all->finishtype);
				return ;
			}
			pthread_mutex_unlock(&all->philos[i].lastmeal);
			pthread_mutex_unlock(&all->finishtype);
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
			pthread_mutex_unlock(&all->philos[i].right);
			all->philos[i].stat.locked_right = 0;
		}
		pthread_mutex_unlock(&all->philos[i].checkfork);
		pthread_mutex_lock(&all->philos[i+1].checkfork);
		if (all->philos[i+1].stat.locked_left == 1)
		{
			pthread_mutex_unlock(all->philos[i+1].left);
			all->philos[i+1].stat.locked_left = 0;
		}
		pthread_mutex_unlock(&all->philos[i+1].checkfork);
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
	pthread_mutex_destroy(&all->ate);
	free(all->philos);
}
