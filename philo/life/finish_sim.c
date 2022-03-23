/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_sim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:53:42 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 18:53:44 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int	wrap_in_mutexes(pthread_mutex_t	*mut, int valid,
		t_all *all, t_philo *philo, int (*func)(t_all *, t_philo *))
{
	pthread_mutex_lock(mut);
	if (valid)
	{
		pthread_mutex_unlock(mut);
		func(all, philo);
		return (1);
	}
	pthread_mutex_unlock(mut);
	return (0);
}

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
		if (wrap_in_mutexes(&all->finishtype, all->simfinished, NULL, NULL, NULL))
			return ;
	}
	pthread_mutex_lock(&all->finishtype);
	all->simfinished = 1;
	stop_activity(all);
	unlock_all_forks(all);
	restart_activity(all);
	pthread_mutex_unlock(&all->finishtype);
	return ;
}

int	lock_finishtype(t_all *all, t_philo *philo)
{
	(void)all;
	(void)philo;
	return (0);
}

int	die_philosopher(t_all *all, t_philo *philo)
{
	if (!wrap_in_mutexes(&all->finishtype
	, all->simfinished
	, all
	, philo
	, &lock_finishtype))
	{
		all->simfinished = 1;
		stop_activity(all);
		printf("%ld %d died\n", (long)calctime(&all->gen), philo->nbr);
		unlock_all_forks(all);
		restart_activity(all);
		return (0);
	}
	else
		return (1);
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
			if (wrap_in_mutexes(&all->philos[i].lastmeal
			, calctime(&all->gen) >= all->philos[i].stat.lastmeal + all->gen.t_die
			, all
			, &all->philos[i]
			, &die_philosopher))
				return ;
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
