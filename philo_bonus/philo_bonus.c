/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:23:07 by gleal             #+#    #+#             */
/*   Updated: 2022/03/21 00:13:47y gleal            ###   ########.fr       */
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

	if (initlife(argc, argv, &all) != EXIT_SUCCESS)
		return ;
	all.gen.tstlife = calctime(&all.gen.tval);
	all.philo.gen = &all.gen;
	create_philos(&all.philo);
	i = 0;
	pthread_mutex_init(&all.finishtype, NULL);
	all.starve = 0;
	pthread_create(&all.check_ate, NULL, (void *)check_ate, &all);
	//pthread_join(all.check_ate, NULL);
	pthread_detach(all.check_ate);
	check_finish(&all);
	while (i < all.philo.gen->philonbr)
	{
		waitpid(all.philo.proc[i], &status, 0);
		i++;
	}
}

void	create_philos(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->gen->philonbr)
	{
		philo->proc[i] = fork();
		//struct timeval t1;
		//double a = calctime(&t1) - philo->gen->tstlife;
		//printf("%s%ld here\n%s",RESET_COLOR, (long)a, RESET_COLOR);
		if (philo->proc[i] < 0)
		{
			printf("There was an error creating philosopher process\n");
			return ;
		}
		if (philo->proc[i] == 0)
		{
			philo->nbr = i + 1;
			philo->clr = set_color(i);
			exit(philolife(philo));
		}
		i++;
	}
}

void	*check_ate(t_all *all)
{
	int	i;
	struct timeval	temp;
	double final;
	
	i = 0;
	while (i < all->gen.philonbr)
	{
		sem_wait(all->philo.satisfied);
		pthread_mutex_lock(&all->finishtype);
		//printf("%ssatisfied\n%s", RESET_COLOR, RESET_COLOR);
		if (all->starve)
		{
			pthread_mutex_unlock(&all->finishtype);
			return ((void *)0);
		}
		final = calctime(&temp) - all->gen.tstlife;
		i++;
		pthread_mutex_unlock(&all->finishtype);
	}
	sem_wait(all->philo.carefulprinting);
	//printf("%ssatified after\n%s", RESET_COLOR, RESET_COLOR);
	pthread_mutex_lock(&all->finishtype);
	if (all->starve)
	{
		pthread_mutex_unlock(&all->finishtype);
		return ((void *)0);
	}
	sem_post(all->philo.finishsim);
	pthread_mutex_unlock(&all->finishtype);
	return ((void *)0);
}

void	check_finish(t_all *all)
{
	int	i;

	//printf("%snormal death\n%s", RESET_COLOR, RESET_COLOR);
	sem_wait(all->philo.finishsim);
	pthread_mutex_lock(&all->finishtype);
	all->starve = 1;
	sem_post(all->philo.satisfied);
	pthread_mutex_unlock(&all->finishtype);
	i = 0;
	while (i < all->gen.philonbr)
	{
		all->gen.tendlife = calctime(&all->gen.tval) - all->gen.tstlife;
		kill(all->philo.proc[i] , SIGTERM);
		i++;
	}
	sem_unlink("satisfied");
	sem_close(all->philo.satisfied);
	sem_unlink("forkpile");
	sem_close(all->philo.forkpile);
	sem_unlink("carefulprinting");
	sem_close(all->philo.carefulprinting);
	sem_unlink("finishsim");
	sem_close(all->philo.finishsim);
	pthread_mutex_destroy(&all->finishtype);
}