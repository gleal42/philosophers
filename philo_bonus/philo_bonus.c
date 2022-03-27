/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:47:28 by gleal             #+#    #+#             */
/*   Updated: 2022/03/27 02:39:45 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	if (argc < 5)
		ft_putstr_fd("Forgot arguments\n", 2);
	else if (argc >= 5 && argc <= 6)
		philosophers(argc, argv);
	else
		ft_putstr_fd("Too many arguments\n", 2);
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
		pthread_mutex_unlock(&all->finishtype);
		i++;
	}
	sem_wait(all->philo.sm.carefulprinting);
	if (print_satisfied_message(all))
		return ((void *)1);
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
