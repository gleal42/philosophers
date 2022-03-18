/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:23:07 by gleal             #+#    #+#             */
/*   Updated: 2022/03/18 19:07:31 by gleal            ###   ########.fr       */
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
	int i;
	int	status;

	status = 0;
	ft_memset(all.gen.philos, '\0', sizeof(all.gen.philos));
	if (initlife(argc, argv, &all) != EXIT_SUCCESS)
		return ;
	all.gen.tstlife = calctime(&all.gen.tval);
	all.philo.gen = &all.gen;
	ft_memset(&all.philo.stat, '\0', sizeof(t_stats));
	i = 0;
	while (i < all.philo.gen->philonbr)
	{
		all.philo.nbr = i + 1;
		all.philo.clr = set_color(i);
		all.gen.philos[i] = fork();
		if (all.gen.philos[i] == -1)
		{
			printf("There was an error creating philosopher process\n");
			return ;
		}
		if (all.gen.philos[i] == 0)
		{
			philolife(&all.philo);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	check_finish_sim(&all);
	i = 0;
	while (i < all.gen.philonbr)
	{
		waitpid(all.gen.philos[i], &status, WNOHANG);
		i++;
	}
}

void	check_finish_sim(t_all *all)
{
	int	i;

	i = 0;
	while (1)
	{
		if (all->philo.stat.ate >= 4)
		{
			while (i < all->gen.philonbr)
			{
				all->gen.tendlife = calctime(&all->gen.tval) - all->gen.tstlife;
				printf("%ld %d died\n", (long)all->gen.tendlife, i + 1);
				kill(all->gen.philos[i] , SIGTERM);
				i++;
			}
			return ;
		}
	}
}