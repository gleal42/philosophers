/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:18:30 by gleal             #+#    #+#             */
/*   Updated: 2022/03/26 19:30:53 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

int	create_philo_mutexes(t_philo *philo)
{
	if (pthread_mutex_init(&philo->lastmealtime, NULL))
	{
		error_mutex(philo, "lastmealtime");
		return (1);
	}
	if (pthread_mutex_init(&philo->isdone, NULL))
	{
		error_mutex(philo, "isdone");
		pthread_mutex_destroy(&philo->lastmealtime);
		return (1);
	}
	if (pthread_mutex_init(&philo->forksheldcheck, NULL))
	{
		error_mutex(philo, "forksheldcheck");
		pthread_mutex_destroy(&philo->lastmealtime);
		pthread_mutex_destroy(&philo->isdone);
		return (1);
	}
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

int	error_mutex(t_philo *philo, char *str)
{
	int	i;

	ft_putstr_fd("Error creating mutex ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	i = 0;
	while (i <= 3)
	{
		sem_unlink(philo->sm.str[i]);
		sem_close(philo->sm.sms[i]);
		i++;
	}
	return (EXIT_FAILURE);
}
