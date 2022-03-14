/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:23:07 by gleal             #+#    #+#             */
/*   Updated: 2022/03/14 00:30:29 by gleal            ###   ########.fr       */
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
		all.philos[i].clr = set_color(i);	
		pthread_mutex_init(&all.philos[i].own.fork, NULL);
		all.philos[i].own.using = 0;
		all.philos[(i + 1)%all.gen.philonbr].left = &all.philos[i].own;
		if (i == 0)
			all.philos[all.gen.philonbr - 1].right = &all.philos[i].own;
		else
			all.philos[i - 1].right = &all.philos[i].own;
		i++;
	}
	all.gen.tstlife = calctime(&all.gen.tval);
	i = 0;
	while (i < all.gen.philonbr)
	{
		pthread_create(&all.philos[i].philo, NULL, (void *)&philolife, &all.philos[i]);
		usleep(15);
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
				all.gen.endlife = 1;
				usleep(1);
				all.gen.tendlife = calctime(&all.gen.tval) - all.gen.tstlife;
				printf("%ld %d died\n", (long)all.gen.tendlife, i + 1);
				break ;
			}
			if (i == 0 || all.philos[i].stat.ate < min)
				min = all.philos[i].stat.ate;
			i++;
		}
		if (all.gen.eat_freq && min >= all.gen.eat_freq)
			all.gen.endlife = 1;
		if (all.gen.endlife)
			break ;
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
		pthread_mutex_destroy(&all.philos[i].own.fork);
		i++;
	}
	free(all.philos);
}
