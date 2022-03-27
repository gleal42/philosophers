/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_life_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:52:24 by gleal             #+#    #+#             */
/*   Updated: 2022/03/27 02:39:53 by gleal            ###   ########.fr       */
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
	return (prepare_semaphores(all));
}

int	prepare_semaphores(t_all *all)
{
	int	i;

	all->philo.sm.str[0] = "satisfied";
	all->philo.sm.str[1] = "forkpile";
	all->philo.sm.str[2] = "carefulprint";
	all->philo.sm.str[3] = "finishsim";
	all->philo.sm.sem_val[0] = 0;
	all->philo.sm.sem_val[1] = all->gen.philonbr;
	all->philo.sm.sem_val[2] = 1;
	all->philo.sm.sem_val[3] = 0;
	i = 0;
	while (i < 4)
	{
		if (create_semaphore(all->philo.sm.str[i], &all->philo.sm.sms[i],
				all->philo.sm.sem_val[i]) == SEM_FAILED)
			return (error_semaphore(&all->philo.sm, i));
		i++;
	}
	all->philo.sm.satisfied = all->philo.sm.sms[0];
	all->philo.sm.forkpile = all->philo.sm.sms[1];
	all->philo.sm.carefulprinting = all->philo.sm.sms[2];
	all->philo.sm.finishsim = all->philo.sm.sms[3];
	return (0);
}

sem_t	*create_semaphore(const char *str, sem_t **semph, int start_value)
{
	sem_unlink(str);
	*semph = sem_open(str, O_CREAT, 0660, start_value);
	return (*semph);
}

int	error_semaphore(t_semphs *sm, int nbr)
{
	int	i;

	ft_putstr_fd("Error creating semaphore ", 2);
	ft_putstr_fd(sm->str[nbr], 2);
	ft_putstr_fd("\n", 2);
	i = 0;
	while (i <= nbr)
	{
		sem_unlink(sm->str[i]);
		sem_close(sm->sms[i]);
		i++;
	}
	return (EXIT_FAILURE);
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
