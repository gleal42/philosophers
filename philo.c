/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:23:07 by gleal             #+#    #+#             */
/*   Updated: 2022/03/11 19:15:52 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc < 5)
		printf("Forgot arguments\n");
	else if (argc >= 5 && argc <= 6)
		philosophers(argc, argv);
	else
		printf("Too many arguments\n");
}

void	philosophers(int argc, char **argv)
{
	t_all	all;
	int i;
	int min;

	if (initlife(argc, argv, &all) != EXIT_SUCCESS)
		return ;
	all.philos = malloc(sizeof(t_philo) * all.gen.philonbr);
	i = 0;
	while (i < all.gen.philonbr)
	{
		all.philos[i].gen = &all.gen;
		all.philos[i].nbr = i + 1;
		ft_memset(&all.philos[i].stat, '\0', sizeof(t_stats));
		pthread_mutex_init(all.philos[i].own->fork, NULL);
		*all.philos[i].own->using = 0;
		all.philos[(i + 1)%all.gen.philonbr].left->fork = all.philos[i].own->fork;
		if (i == 0)
			all.philos[all.gen.philonbr].right->fork = all.philos[i].own->fork;
		else
			all.philos[i - 1].right->fork = all.philos[i].own->fork;
		i++;
	}
	all.gen.tstlife = calctime(&all.gen.tval);
	i = 0;
	while (i < all.gen.philonbr)
	{
		pthread_create(&all.philos[i].philo, NULL, (void *)&philolife, &all.philos[i]);
		i++;
	}
	while (1)
	{
		i = 0;
		min = 0;
		while (i < all.gen.philonbr)
		{
			if (all.philos[i].stat.dead)
			{
				all.gen.tendlife = calctime(&all.gen.tval) - all.gen.tstlife;
				all.gen.endlife = 1;
				printf("%ld %d died\n", (long)all.gen.tendlife, i + 1);
				break ;
			}
			if (i == 0 || all.philos[i].stat.ate < min)
				min = all.philos[i].stat.ate;
			i++;
		}
		if (all.philos[i].stat.dead || (all.gen.eat_freq && min >= all.gen.eat_freq))
		{
			all.gen.endlife = 1;
			break ;
		}
	}
	i = 0;
	while (i < all.gen.philonbr)
	{
		pthread_join(all.philos[i].philo, NULL);
		i++;
	}
	i = 0;
	while (i < all.gen.philonbr)
	{
		pthread_mutex_destroy(all.philos[i].own->fork);
		i++;
	}
	free(all.philos);
}
