/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:47:28 by gleal             #+#    #+#             */
/*   Updated: 2022/03/25 22:10:23 by gleal            ###   ########.fr       */
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

	if (initlife(argc, argv, &all) != EXIT_SUCCESS)
		return ;
	all.gen.tstlife = 0;
	all.gen.tstlife = calctime(&all.gen);
	all.philo.gen = &all.gen;
	memset((void *)&all.philo.stat, 0, sizeof(all.philo.stat));
	create_philos(&all.philo);
	pthread_mutex_init(&all.finishtype, NULL);
	all.died = 0;
	if (argc == 6)
	{
		pthread_create(&all.check_ate, NULL, (void *)check_ate, &all);
		pthread_detach(all.check_ate);
	}
	finishsim(&all);
}


void	create_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->gen->philonbr)
	{
		philo->proc[i] = fork();
		philo->nbr = i + 1;
		philo->clr = set_color(i);
		if (philo->proc[i] < 0)
		{
			printf("There was an error creating philosopher process\n");
			return ;
		}
		if (philo->proc[i] == 0)
			exit(philolife(philo));
		i++;
	}
}

void	*check_ate(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->gen.philonbr)
	{
		sem_wait(all->philo.sm.satisfied);
		i++;
	}
	sem_wait(all->philo.sm.carefulprinting);
	pthread_mutex_lock(&all->finishtype);
	if (all->died)
	{
		pthread_mutex_unlock(&all->finishtype);
		return (void *)0;
	}
	printf("%s%ld all philosophers ate %d times 🏆\n%s", WHITE,
		(long)calctime(&all->gen), all->gen.eat_freq, RESET);
	pthread_mutex_unlock(&all->finishtype);
	i = 0;
	while (i < all->gen.philonbr)
	{
		sem_post(all->philo.sm.finishsim);
		i++;
	}
	return ((void *)0);
}

void	finishsim(t_all *all)
{
	int		i;
	int		philoindex;

	i = 0;
	waitpid(-1, &philoindex, 0);
	pthread_mutex_lock(&all->finishtype);
	all->died = 1;
	pthread_mutex_unlock(&all->finishtype);
	while (i < all->philo.gen->philonbr)
	{
		if (i == philoindex)
			i++;
		waitpid(all->philo.proc[i], &philoindex, 0);
		i++;
	}
	i = 0;
	while (i < all->gen.philonbr)
	{
		sem_post(all->philo.sm.satisfied);
		i++;
	}
	sem_unlink("satisfied");
	sem_close(all->philo.sm.satisfied);
	sem_unlink("forkpile");
	sem_close(all->philo.sm.forkpile);
	sem_unlink("carefulprinting");
	sem_post(all->philo.sm.carefulprinting);
	sem_close(all->philo.sm.carefulprinting);
	sem_unlink("finishsim");
	sem_close(all->philo.sm.finishsim);
	pthread_mutex_destroy(&all->finishtype);
}
