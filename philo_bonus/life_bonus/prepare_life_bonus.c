/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_life_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:20:19 by gleal             #+#    #+#             */
/*   Updated: 2022/03/19 21:22:07 by gleal            ###   ########.fr       */
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
	sem_unlink("satisfied");
	all->philo.finished_eating = sem_open("satisfied", O_CREAT, 0660, 0);
	if (all->philo.finished_eating == SEM_FAILED)
	{
		ft_putstr_fd("Error creating semaphore satisfied\n", 2);
		sem_unlink("satisfied");
		sem_close(all->philo.finished_eating);
		return (1);
	}
	sem_unlink("simcontinue");
	all->philo.simcontinue = sem_open("simcontinue", O_CREAT, 0660, 1);
	if (all->philo.simcontinue == SEM_FAILED)
	{
		ft_putstr_fd("Error creating semaphore simcontinue\n", 2);
		sem_unlink("simcontinue");
		sem_close(all->philo.simcontinue);
		return (1);
	}
	return (0);
}

