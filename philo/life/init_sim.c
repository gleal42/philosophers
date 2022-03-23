/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:31:25 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 21:49:50 by gleal            ###   ########.fr       */
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
	if (argc == 6)
	{
		all->gen.eat_freq = ft_atoi(argv[5]);
		if (all->gen.eat_freq == 0)
			return (1);
	}
	else
		all->gen.eat_freq = 0;
	pthread_mutex_init(&all->satisfied, NULL);
	pthread_mutex_init(&all->finishtype, NULL);
	all->simfinished = 0;
	return (0);
}

void	prepare_individuals(t_all	*all)
{
	int		i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		all->philos[i].gen = &all->gen;
		all->philos[i].satisfied = &all->satisfied;
		all->philos[i].nbr = i + 1;
		pthread_mutex_init(&all->philos[i].died, NULL);
		pthread_mutex_init(&all->philos[i].lastmeal, NULL);
		memset(&all->philos[i].stat, '\0', sizeof(t_stats));
		all->philos[i].clr = set_color(i);
		pthread_mutex_init(&all->philos[i].right, NULL);
		pthread_mutex_init(&all->philos[i].checkfork, NULL);
		all->philos[(i + 1) % all->gen.philonbr].left = &all->philos[i].right;
		i++;
	}
}

void	startsim_addphilos(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		pthread_create(&all->philos[i].philo, NULL,
			(void *)&philolife, &all->philos[i]);
		usleep(18);
		i++;
	}
}
