/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:05:08 by gleal             #+#    #+#             */
/*   Updated: 2022/03/26 18:18:15 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

double	calctime(const t_gen *gen)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((double)(time.tv_sec * 1000 + time.tv_usec / 1000 - gen->tstlife));
}

int	is_inbetween_time(double min, double val, double max)
{
	if (min <= val && val <= max)
		return (1);
	else
		return (0);
}

//printf("%ld %d yooo philo 🏆\n", (long)calctime(philo->gen), philo->nbr);
int	careful_print(const char *str, t_philo *philo)
{
	sem_wait(philo->sm.carefulprinting);
	pthread_mutex_lock(&philo->isdone);
	if (philo->stat.died)
	{
		pthread_mutex_unlock(&philo->isdone);
		pthread_mutex_destroy(&philo->lastmealtime);
		pthread_mutex_destroy(&philo->isdone);
		pthread_mutex_destroy(&philo->forksheldcheck);
		sem_post(philo->sm.carefulprinting);
		return (1);
	}
	pthread_mutex_unlock(&philo->isdone);
	printf(str, philo->clr, (long)calctime(philo->gen), philo->nbr, RESET);
	sem_post(philo->sm.carefulprinting);
	return (0);
}

void	regular_print(const char *str, t_philo *philo)
{
	printf(str, philo->clr,
		(long)calctime(philo->gen), philo->nbr, RESET);
}

char	*set_color(int clr)
{
	t_colors	newcolor;

	newcolor = clr % 4;
	if (newcolor == lred)
		return (LRED);
	else if (newcolor == lgrn)
		return (LGRN);
	else if (newcolor == yel)
		return (YEL);
	else
		return (LBLU);
}
