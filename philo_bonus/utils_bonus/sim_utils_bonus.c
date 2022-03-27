/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 02:30:48 by gleal             #+#    #+#             */
/*   Updated: 2022/03/27 02:38:17 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

double	calctime(const t_gen *gen)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((double)(time.tv_sec * 1000 + time.tv_usec / 1000 - gen->tstlife));
}

void	careful_print(const char *str, t_philo *philo)
{
	sem_wait(philo->sm.carefulprinting);
	printf(str, philo->clr,
		(long)calctime(philo->gen), philo->nbr, RESET);
	sem_post(philo->sm.carefulprinting);
}

void	regular_print(const char *str, t_philo *philo)
{
	printf(str, philo->clr,
		(long)calctime(philo->gen), philo->nbr, RESET);
}

int	print_satisfied_message(t_all *all)
{
	pthread_mutex_lock(&all->finishtype);
	if (all->starve)
	{
		pthread_mutex_unlock(&all->finishtype);
		return (1);
	}
	printf("%s%ld all philosophers ate %d times 🏆\n%s",
		WHITE, (long)calctime(&all->gen), all->gen.eat_freq, RESET);
	sem_post(all->philo.sm.finishsim);
	pthread_mutex_unlock(&all->finishtype);
	return (0);
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
