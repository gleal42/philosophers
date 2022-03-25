/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:06:20 by gleal             #+#    #+#             */
/*   Updated: 2022/03/24 22:08:33 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	leave_forks_on_the_table(pthread_mutex_t *right, pthread_mutex_t *left)
{
	pthread_mutex_unlock(right);
	pthread_mutex_unlock(left);
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