/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_sim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:17:28 by gleal             #+#    #+#             */
/*   Updated: 2022/03/24 18:04:46 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int	finish_sim(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->gen.philonbr)
		pthread_join(all->philos[i].philo, NULL);
	i = -1;
	while (++i < all->gen.philonbr)
		pthread_mutex_destroy(&all->philos[i].right);
		i++;
	pthread_mutex_destroy(&all->satisfied);
	pthread_mutex_destroy(&all->finishsim);
	pthread_mutex_destroy(&all->lastmeal);
	free(all->philos);
	return (0);
}
