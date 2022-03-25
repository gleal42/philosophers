/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_create_destroy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:19:35 by gleal             #+#    #+#             */
/*   Updated: 2022/03/25 17:19:37 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	create_gen_mutexes(t_all *all)
{
	if (pthread_mutex_init(&all->satisfied, NULL) == EXIT_FAILURE)
		return (1);
	if (pthread_mutex_init(&all->finishsim, NULL) == EXIT_FAILURE)
	{
		pthread_mutex_destroy(&all->satisfied);
		return (1);
	}
	if (pthread_mutex_init(&all->lastmeal, NULL) == EXIT_FAILURE)
	{
		pthread_mutex_destroy(&all->satisfied);
		pthread_mutex_destroy(&all->finishsim);
		return (1);
	}
	return (0);
}

int	delete_gen_mutexes(t_all *all)
{
	pthread_mutex_destroy(&all->satisfied);
	pthread_mutex_destroy(&all->finishsim);
	pthread_mutex_destroy(&all->lastmeal);
	return (1);
}

int	create_philo_mutexes(t_all *all, int i)
{
	if (pthread_mutex_init(&all->philos[i].right, NULL) == EXIT_FAILURE)
	{
		delete_gen_mutexes(all);
		delete_other_philo_mutexes(all, i - 1);
		return (1);
	}
	return (0);
}

int	delete_other_philo_mutexes(t_all *all, int last)
{
	while (last >= 0)
	{
		pthread_mutex_destroy(&all->philos[last].right);
		last--;
	}
	return (1);
}
