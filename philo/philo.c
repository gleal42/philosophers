/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:23:07 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 02:38:42 by gleal            ###   ########.fr       */
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
	all.gen.tstlife = 0;
	all.gen.tstlife = calctime(&all.gen);
	prepare_individuals(&all);
	startsim_addphilos(&all);
	pthread_create(&all.check_dead, NULL, (void *)&check_dead_loop, &all);
	pthread_detach(all.check_dead);
	if (argc == 6)
	{
		pthread_create(&all.check_ate, NULL, (void *)&check_ate_loop, &all);
		pthread_detach(all.check_ate);
	}
	finish_sim(&all);
}
