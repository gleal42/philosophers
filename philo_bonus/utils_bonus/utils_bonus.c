/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:05:08 by gleal             #+#    #+#             */
/*   Updated: 2022/03/21 18:02:52 by gleal            ###   ########.fr       */
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

double	calctime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((double)(time.tv_sec * 1000 + time.tv_usec / 1000));
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
	sem_wait(philo->sm.carefulprinting);
	philo->act = calctime() - philo->gen->tstlife;
	printf(str, philo->clr, (long)philo->act, philo->nbr, RESET_COLOR);
	sem_post(philo->sm.carefulprinting);
}

void	regular_print(const char *str, t_philo *philo)
{
	philo->act = calctime() - philo->gen->tstlife;
	printf(str, philo->clr, (long)philo->act, philo->nbr, RESET_COLOR);
}
