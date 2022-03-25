/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:31:25 by gleal             #+#    #+#             */
/*   Updated: 2022/03/25 00:11:19 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int	initlife(int argc, char **argv, t_all *all)
{
	all->gen.endlife = 0;
	if (!(is_input_uint(&argv[1], argc)))
		return (1);
	all->gen.philonbr = ft_atoi(argv[1]);
	if (all->gen.philonbr == 0)
		return (1);
	all->gen.t_eat = ft_atoi(argv[3]);
	all->gen.t_sleep = ft_atoi(argv[4]);
	all->gen.t_die = ft_atoi(argv[2]);
	if (pthread_mutex_init(&all->right_order, NULL) == EXIT_FAILURE)
		return (1);
	if (argc == 6)
	{
		if (pthread_mutex_init(&all->satisfied, NULL) == EXIT_FAILURE)
			return (1);
		all->gen.eat_freq = ft_atoi(argv[5]);
		if (all->gen.eat_freq == 0)
			return (1);
	}
	else
		all->gen.eat_freq = 0;
	return (0);
}

int	prepare_individuals(t_all *all)
{
	int		i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		if (pthread_mutex_init(&all->philos[i].right, NULL) == EXIT_FAILURE)
		{
			pthread_mutex_destroy(&all->satisfied);
			delete_other_philo_mutexes(all, i - 1);
			free(all->philos);
			return (1);
		}
		all->philos[(i + 1) % all->gen.philonbr].left = &all->philos[i].right;
		all->philos[i].gen = &all->gen;
		all->philos[i].satisfied = &all->satisfied;
		all->philos[i].nbr = i + 1;
		memset(&all->philos[i].stat, '\0', sizeof(t_stats));
		i++;
	}
	return (0);
}

int	startsim_addphilos(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		if (pthread_create(&all->philos[i].philo, NULL,
				&philolife, &all->philos[i]))
			return (remove_remain_philos_mutexes(all, i - 1));
			usleep(18);
		i++;
	}
	return (0);
}

int	remove_remain_philos_mutexes(t_all *all, int last)
{
	int	i;

	while (last >= 0)
	{
		pthread_join(all->philos[last].philo, NULL);
		last--;
	}
	i = 0;
	while (i < all->gen.philonbr)
	{
		pthread_mutex_destroy(&all->philos[i].right);
		i++;
	}
	pthread_mutex_destroy(&all->satisfied);
	free(all->philos);
	return (1);
}
