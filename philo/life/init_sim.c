/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:31:25 by gleal             #+#    #+#             */
/*   Updated: 2022/03/24 00:18:13 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int	initlife(int argc, char **argv, t_all *all)
{
	all->simfinished = 0;
	all->gen.endlife = 0;
	if (!(is_input_uint(&argv[1], argc)))
		return (1);
	all->gen.philonbr = ft_atoi(argv[1]);
	if (all->gen.philonbr == 0)
		return (1);
	all->gen.t_eat = ft_atoi(argv[3]);
	all->gen.t_sleep = ft_atoi(argv[4]);
	all->gen.t_die = ft_atoi(argv[2]);
	if (argc == 6)
	{
		all->gen.eat_freq = ft_atoi(argv[5]);
		if (all->gen.eat_freq == 0)
			return (1);
	}
	else
		all->gen.eat_freq = 0;
	return (create_gen_mutexes(all));
}

int	prepare_individuals(t_all *all)
{
	int		i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		if (create_philo_mutexes(all, i) == EXIT_FAILURE)
		{
			free(all->philos);
			return (1);
		}
		all->philos[i].gen = &all->gen;
		all->philos[i].satisfied = &all->satisfied;
		all->philos[i].nbr = i + 1;
		memset(&all->philos[i].stat, '\0', sizeof(t_stats));
		all->philos[i].clr = set_color(i);
		all->philos[(i + 1) % all->gen.philonbr].left = &all->philos[i].right;
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
				(void *)&philolife, &all->philos[i]))
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
		pthread_mutex_destroy(&all->philos[i].died);
		pthread_mutex_destroy(&all->philos[i].lastmeal);
		pthread_mutex_destroy(&all->philos[i].checkfork);
		i++;
	}
	delete_gen_mutexes(all);
	free(all->philos);
	return (1);
}
