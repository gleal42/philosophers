/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:29:57 by gleal             #+#    #+#             */
/*   Updated: 2022/03/27 03:15:29 by gleal            ###   ########.fr       */
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
		return (delete_gen_mutexes(&all));
	all.gen.tstlife = 0;
	all.gen.tstlife = calctime(&all.gen);
	if (prepare_individuals(&all) == EXIT_FAILURE)
		return (1);
	if (startsim_addphilos(&all))
		return (1);
	check_finish_loop(&all);
	finish_sim(&all);
	return (0);
}

int	finish_sim(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->gen.philonbr)
		pthread_join(all->philos[i].philo, NULL);
	i = -1;
	while (++i < all->gen.philonbr)
		pthread_mutex_destroy(&all->philos[i].right);
		i++;
	pthread_mutex_destroy(&all->satisfied);
	pthread_mutex_destroy(&all->finishsim);
	pthread_mutex_destroy(&all->lastmeal);
	free(all->philos);
	return (0);
}
