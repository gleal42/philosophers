/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 23:40:30 by gleal             #+#    #+#             */
/*   Updated: 2022/03/24 00:12:00 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	create_gen_mutexes(t_all *all)
{
	if (pthread_mutex_init(&all->satisfied, NULL) == EXIT_FAILURE)
		return (1);
	if (pthread_mutex_init(&all->finishtype, NULL) == EXIT_FAILURE)
	{
		pthread_mutex_destroy(&all->satisfied);
		return (1);
	}
	return (0);
}

int	delete_gen_mutexes(t_all *all)
{
	pthread_mutex_destroy(&all->satisfied);
	pthread_mutex_destroy(&all->finishtype);
	return (1);
}

int	create_philo_mutexes(t_all *all, int i)
{
	if (pthread_mutex_init(&all->philos[i].died, NULL) == EXIT_FAILURE)
		return (delete_gen_mutexes(all));
	if (pthread_mutex_init(&all->philos[i].lastmeal, NULL) == EXIT_FAILURE)
	{
		delete_gen_mutexes(all);
		delete_philo_mutexes(all, DIED, i);
		return (1);
	}
	if (pthread_mutex_init(&all->philos[i].right, NULL) == EXIT_FAILURE)
	{
		delete_gen_mutexes(all);
		delete_philo_mutexes(all, LASTMEAL, i);
		return (1);
	}
	if (pthread_mutex_init(&all->philos[i].checkfork, NULL) == EXIT_FAILURE)
	{
		delete_gen_mutexes(all);
		delete_philo_mutexes(all, RIGHT, i);
		return (1);
	}
	return (0);
}

int	delete_philo_mutexes(t_all *all, t_num_mut muttype, int i)
{
	if (muttype == DIED)
		pthread_mutex_destroy(&all->philos[i].died);
	else if (muttype == LASTMEAL)
	{
		pthread_mutex_destroy(&all->philos[i].died);
		pthread_mutex_destroy(&all->philos[i].lastmeal);
	}
	else if (muttype == RIGHT)
	{
		pthread_mutex_destroy(&all->philos[i].died);
		pthread_mutex_destroy(&all->philos[i].lastmeal);
		pthread_mutex_destroy(&all->philos[i].right);
	}
	else if (muttype == CHECKFORK)
	{
		pthread_mutex_destroy(&all->philos[i].died);
		pthread_mutex_destroy(&all->philos[i].lastmeal);
		pthread_mutex_destroy(&all->philos[i].right);
		pthread_mutex_destroy(&all->philos[i].checkfork);
	}
	return (delete_other_philo_mut(all, i - 1));
}

int	delete_other_philo_mut(t_all *all, int last_created)
{
	while (last_created >= 0)
	{
		pthread_mutex_destroy(&all->philos[last_created].died);
		pthread_mutex_destroy(&all->philos[last_created].lastmeal);
		pthread_mutex_destroy(&all->philos[last_created].right);
		pthread_mutex_destroy(&all->philos[last_created].checkfork);
		last_created--;
	}
	return (1);
}
