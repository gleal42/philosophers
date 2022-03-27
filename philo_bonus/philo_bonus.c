/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:47:28 by gleal             #+#    #+#             */
/*   Updated: 2022/03/27 00:09:41 by gleal            ###   ########.fr       */
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
	int		i;
	int		status;

	if (initlife(argc, argv, &all) != EXIT_SUCCESS)
		return ;
	all.gen.tstlife = 0;
	all.gen.tstlife = calctime(&all.gen);
	all.philo.gen = &all.gen;
	create_philos(&all.philo);
	i = 0;
	pthread_mutex_init(&all.finishtype, NULL);
	all.starve = 0;
	if (argc == 6)
	{
		pthread_create(&all.check_ate, NULL, (void *)check_ate, &all);
		pthread_detach(all.check_ate);
	}
	pthread_create(&all.check_finish, NULL, (void *)check_finish, &all);
	pthread_detach(all.check_finish);
	while (i < all.philo.gen->philonbr)
	{
		waitpid(all.philo.proc[i], &status, 0);
		i++;
	}
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
		pthread_mutex_lock(&all->finishtype);
		if (all->starve)
		{
			pthread_mutex_unlock(&all->finishtype);
			return ((void *)0);
		}
		i++;
		pthread_mutex_unlock(&all->finishtype);
	}
	sem_wait(all->philo.sm.carefulprinting);
	pthread_mutex_lock(&all->finishtype);
	if (all->starve)
	{
		pthread_mutex_unlock(&all->finishtype);
		return ((void *)0);
	}
	sem_post(all->philo.sm.finishsim);
	pthread_mutex_unlock(&all->finishtype);
	return ((void *)0);
}

void	check_finish(t_all *all)
{
	int	i;

	sem_wait(all->philo.sm.finishsim);
	pthread_mutex_lock(&all->finishtype);
	all->starve = 1;
	sem_post(all->philo.sm.satisfied);
	pthread_mutex_unlock(&all->finishtype);
	i = 0;
	while (i < all->gen.philonbr)
	{
		kill(all->philo.proc[i], SIGTERM);
		i++;
	}
	sem_unlink("satisfied");
	sem_close(all->philo.sm.satisfied);
	sem_unlink("forkpile");
	sem_close(all->philo.sm.forkpile);
	sem_unlink("carefulprinting");
	sem_close(all->philo.sm.carefulprinting);
	sem_unlink("finishsim");
	sem_close(all->philo.sm.finishsim);
	pthread_mutex_destroy(&all->finishtype);
}
