/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:53:55 by gleal             #+#    #+#             */
/*   Updated: 2022/03/25 17:00:54 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int	check_satisfied(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		pthread_mutex_lock(&all->satisfied);
		if (all->philos[i].stat.satisfied == 0)
		{
			pthread_mutex_unlock(&all->satisfied);
			return (0);
		}
		pthread_mutex_unlock(&all->satisfied);
		i++;
	}
	pthread_mutex_lock(&all->finishsim);
	all->gen.endlife = 1;
	printf("%s%ld all philosophers ate %d times 🏆\n%s",
		WHITE, (long)calctime(&all->gen), all->gen.eat_freq, RESET);
	pthread_mutex_unlock(&all->finishsim);
	return (1);
}

int	check_dead(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		pthread_mutex_lock(&all->lastmeal);
		if (calctime(&all->gen) >= all->philos[i].stat.lastmeal
			+ all->gen.t_die)
		{
			pthread_mutex_unlock(&all->lastmeal);
			pthread_mutex_lock(&all->finishsim);
			all->gen.endlife = 1;
			printf("%s%ld %d died 💀\n%s", all->philos[i].clr,
				(long)calctime(&all->gen), all->philos[i].nbr, RESET);
			pthread_mutex_unlock(&all->finishsim);
			return (1);
		}
		pthread_mutex_unlock(&all->lastmeal);
		i++;
	}
	return (0);
}

void	check_finish_loop(t_all *all)
{
	if (all->gen.eat_freq > 0)
	{
		while (1)
		{
			if (check_dead(all))
				return ;
			if (check_satisfied(all))
				return ;
		}
	}
	else
	{
		while (1)
		{
			if (check_dead(all))
				return ;
		}
	}
}
