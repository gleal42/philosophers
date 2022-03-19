/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:23:07 by gleal             #+#    #+#             */
/*   Updated: 2022/03/19 21:19:32 by gleal            ###   ########.fr       */
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
	pthread_create(&all.philo.check_ate, NULL, (void *)check_ate, &all);
	pthread_join(all.philo.check_ate, NULL);
	//pthread_detach(all.philo.check_ate);
	//pthread_exit(0);
	exit(EXIT_SUCCESS);
}

void	*check_ate(t_all *all)
{
	int	i;
	struct timeval	temp;
	double final;
	
	i = 0;
	while (i < all->gen.philonbr)
	{
		sem_wait(all->philo.finished_eating);
		final = calctime(&temp) - all->gen.tstlife;
		printf("%s %lu %d Philosophers are already done eating\n%s", RESET_COLOR, (long)final, i + 1, RESET_COLOR);
		i++;
	}
	printf("%ld %d is satisfied\n", (long)all->gen.tendlife, all->philo.nbr);
	i = 0;
	while (i < all->gen.philonbr)
	{
		all->gen.tendlife = calctime(&all->gen.tval) - all->gen.tstlife;
		kill(all->gen.philos[i] , SIGTERM);
		i++;
	}
	sem_unlink("satisfied");
	sem_close(all->philo.finished_eating);
	sem_unlink("simcontinue");
	sem_close(all->philo.simcontinue);
	pthread_exit(0);
	return ((void *)0);
}
