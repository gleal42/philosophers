/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:17:45 by gleal             #+#    #+#             */
/*   Updated: 2022/03/26 19:18:46 by gleal            ###   ########.fr       */
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
	all->philo.sm.start_val[0] = 0;
	all->philo.sm.start_val[1] = all->gen.philonbr;
	all->philo.sm.start_val[2] = 1;
	all->philo.sm.start_val[3] = 0;
	i = 0;
	while (i < 4)
	{
		if (create_semaphore(all->philo.sm.str[i], &all->philo.sm.sms[i],
				all->philo.sm.start_val[i]) == SEM_FAILED)
			return (error_semaphore(&all->philo.sm, i - 1));
		i++;
	}
	all->philo.sm.satisfied = all->philo.sm.sms[0];
	all->philo.sm.forkpile = all->philo.sm.sms[1];
	all->philo.sm.carefulprinting = all->philo.sm.sms[2];
	all->philo.sm.finishsim = all->philo.sm.sms[3];
	return (0);
}
