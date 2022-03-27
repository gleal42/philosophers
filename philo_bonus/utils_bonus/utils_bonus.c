/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:05:08 by gleal             #+#    #+#             */
/*   Updated: 2022/03/27 00:08:54 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	nbr;

	sign = 1;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	nbr = 0;
	while (*str)
	{
		nbr *= 10;
		nbr += *str - '0';
		str++;
	}
	return (nbr * sign);
}

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

void	careful_print(const char *str, t_philo *philo)
{
	if (philo->ate >= philo->gen->eat_freq)
		usleep(20);
	sem_wait(philo->sm.carefulprinting);
	printf(str, philo->clr, (long)calctime(philo->gen), philo->nbr, RESET_COLOR);
	sem_post(philo->sm.carefulprinting);
}

void	regular_print(const char *str, t_philo *philo)
{
	printf(str, philo->clr, (long)calctime(philo->gen), philo->nbr, RESET_COLOR);
}
