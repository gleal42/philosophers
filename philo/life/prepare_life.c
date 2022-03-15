/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_life.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:31:25 by gleal             #+#    #+#             */
/*   Updated: 2022/03/15 15:09:28 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int	initlife(int argc, char **argv, t_all *all)
{
	all->gen.endlife = 0;
	if (!is_input_integer(&argv[1]))
		return (1);
	all->gen.philonbr = ft_atoi(argv[1]);
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
	pthread_mutex_init(&all->death, NULL);
	pthread_mutex_init(&all->eat, NULL);
	return (0);
}

void	prepare_individuals(t_all	*all)
{
	int		i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		all->philos[i].gen = &all->gen;
		all->philos[i].death = &all->death;
		all->philos[i].eat = &all->eat;
		all->philos[i].nbr = i + 1;
		ft_memset(&all->philos[i].stat, '\0', sizeof(t_stats));
		all->philos[i].clr = set_color(i);
		pthread_mutex_init(&all->philos[i].right, NULL);
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
