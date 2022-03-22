/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:23:07 by gleal             #+#    #+#             */
/*   Updated: 2022/03/22 17:10:34 by gleal            ###   ########.fr       */
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

	if (initlife(argc, argv, &all) != EXIT_SUCCESS)
		return ;
	all.philos = malloc(sizeof(t_philo) * all.gen.philonbr);
	prepare_individuals(&all);
	all.gen.tstlife = calctime();
	pthread_create(&all.monitor, NULL, (void *)&monitordie, &all);
	pthread_detach(all.monitor);
	startsim_addphilos(&all);
	if (argc == 6)
		check_ate_loop(&all);
	finish_sim(&all);
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
		i++;
	}
	pthread_mutex_destroy(&all->death);
	pthread_mutex_destroy(&all->eat);
	free(all->philos);
}
