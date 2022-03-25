/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:29:57 by gleal             #+#    #+#             */
/*   Updated: 2022/03/25 00:52:36 by gleal            ###   ########.fr       */
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

int	philosophers(int argc, char **argv)
{
	t_all	all;

	if (initlife(argc, argv, &all) != EXIT_SUCCESS)
		return (1);
	all.philos = malloc(sizeof(t_philo) * all.gen.philonbr);
	if (!all.philos)
	{
		pthread_mutex_destroy(&all.satisfied);
		return (1);
	}
	all.gen.tstlife = 0;
	all.gen.tstlife = calctime(&all.gen);
	if (prepare_individuals(&all) == EXIT_FAILURE)
		return (1);
	if (startsim_addphilos(&all))
		return (1);
	finish_sim(&all);
	return (0);
}
