/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_life_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:20:19 by gleal             #+#    #+#             */
/*   Updated: 2022/03/20 17:19:51by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life_bonus.h"

int	initlife(int argc, char **argv, t_all *all)
{
	if (!is_input_integer(&argv[1]))
		return (1);
	all->gen.philonbr = ft_atoi(argv[1]);
	all->gen.t_eat = ft_atoi(argv[3]);
	all->gen.t_sleep = ft_atoi(argv[4]);
	all->gen.t_die = ft_atoi(argv[2]);
	if (argc == 6)
	{
		all->gen.eat_freq = ft_atoi(argv[5]);
		if (all->gen.eat_freq == 0)
			return (1);
	}
	else
		all->gen.eat_freq = 0;
	if (create_semaphore("satisfied", &all->philo.satisfied, 0) == EXIT_FAILURE)
		return (1);
	if (create_semaphore("forkpile", &all->philo.forkpile, all->gen.philonbr) == EXIT_FAILURE)
	{
		sem_unlink("satisfied");
		sem_close(all->philo.satisfied);
		return (1);
	}
	if (create_semaphore("carefulprint", &all->philo.carefulprinting, 1) == EXIT_FAILURE)
	{
		sem_unlink("satisfied");
		sem_close(all->philo.satisfied);
		sem_unlink("forkpiled");
		sem_close(all->philo.forkpile);
		return (1);
	}
	if (create_semaphore("finishsim", &all->philo.finishsim, 0) == EXIT_FAILURE)
	{
		sem_unlink("satisfied");
		sem_close(all->philo.satisfied);
		sem_unlink("forkpiled");
		sem_close(all->philo.forkpile);
		sem_unlink("carefulprint");
		sem_close(all->philo.carefulprinting);
		return (1);
	}
	return (0);
}

int create_semaphore(const char *str, sem_t **semph, int start_value)
{
	sem_unlink(str);
	*semph = sem_open(str, O_CREAT, 0660, start_value);
	if (*semph == SEM_FAILED)
	{
		ft_putstr_fd("Error creating semaphore ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
		sem_unlink(str);
		sem_close(*semph);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
