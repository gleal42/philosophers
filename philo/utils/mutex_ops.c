/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:06:20 by gleal             #+#    #+#             */
/*   Updated: 2022/03/25 17:16:41 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	leave_forks_on_the_table(pthread_mutex_t *fstfork,
		pthread_mutex_t *secfork)
{
	pthread_mutex_unlock(fstfork);
	pthread_mutex_unlock(secfork);
}

void	death_bed(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->finishsim);
		if (philo->gen->endlife)
		{
			pthread_mutex_unlock(philo->finishsim);
			return ;
		}
		pthread_mutex_unlock(philo->finishsim);
	}
}
