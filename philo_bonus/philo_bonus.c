/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:23:07 by gleal             #+#    #+#             */
/*   Updated: 2022/03/16 19:15:56 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	pid_t	philos[201];
	int i;
	int	status;

	status = 0;
	ft_memset(philos, '\0', sizeof(i));
	if (initlife(argc, argv, &all) != EXIT_SUCCESS)
		return ;
	all.gen.tstlife = calctime(&all.gen.tval);
	all.philos.gen = &all.gen;
	ft_memset(&all.philos.stat, '\0', sizeof(t_stats));
	i = 0;
	//while (i < all.philos.gen->philonbr)
	while (i < 2)
	{
		all.philos.nbr = i + 1;
		all.philos.clr = set_color(i);
		philos[i] = fork();
		if (philos[i] == -1)
		{
			printf("There was an error creating philosopher process\n");
			return ;
		}
		if (philos[i] == 0)
		{
			pthread_create(&all.gen.checker, NULL, (void *)&philolife, &all.philos);
			check_finish_sim(&all);
			pthread_join(all.gen.checker, NULL);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < all.gen.philonbr)
	{
		waitpid(philos[i], &status, WNOHANG);
		i++;
	}
}

void	check_finish_sim(t_all *all)
{
	while (1)
	{
		int	i;

		i = 0;
		all->gen.tendlife = calctime(&all->gen.tval) - all->gen.tstlife;
		printf("%ld %d died\n", (long)all->gen.tendlife, i + 1);
		kill(0, SIGINT);
		i++;
	}
}