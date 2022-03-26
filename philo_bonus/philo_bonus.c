/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:13:51 by gleal             #+#    #+#             */
/*   Updated: 2022/03/26 19:13:52 by gleal            ###   ########.fr       */
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
	if (pthread_mutex_init(&all.finishtype, NULL))
	{
		error_mutex(&all.philo, "finishtype");
		return ;
	}
	all.deadfinish = 0;
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
			philolife(philo);
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
	if (all->deadfinish)
	{
		pthread_mutex_unlock(&all->finishtype);
		return ((void *)0);
	}
	printf("%s%ld all philosophers ate %d times 🏆\n%s", WHITE,
		(long)calctime(&all->gen), all->gen.eat_freq, RESET);
	pthread_mutex_unlock(&all->finishtype);
	unlock_finish_simulation(all);
	sem_post(all->philo.sm.carefulprinting);
	return ((void *)0);
}

void	finishsim(t_all *all)
{
	int		philoindex;

	waitpid(-1, &philoindex, 0);
	pthread_mutex_lock(&all->finishtype);
	all->deadfinish = 1;
	pthread_mutex_unlock(&all->finishtype);
	if (philoindex != -1)
	{
		unlock_finish_simulation(all);
		unlock_carefulprinting(all);
		waitremainphilo(all, &philoindex);
	}
	unlock_satisfied(all);
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
