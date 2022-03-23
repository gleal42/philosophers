/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:05:08 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 18:35:35 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*mem;
	size_t			i;

	mem = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		mem[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

int	is_inbetween_time(double min, double val, double max)
{
	if (min <= val && val <= max)
		return (1);
	else
		return (0);
}



//pthread_mutex_lock(&all->philos[i].lastmeal);
//if (calctime(&all->gen)
//	>= all->philos[i].stat.lastmeal + all->gen.t_die)
//{
//	pthread_mutex_unlock(&all->philos[i].lastmeal);
//	if (lock_finishtype(all))
//		return ;
//	stop_activity(all);
//	printf("%ld %d died\n", (long)calctime(&all->gen), i + 1);
//	unlock_all_forks(all);
//	restart_activity(all);
//	pthread_mutex_unlock(&all->finishtype);
//	return ;
//}
//pthread_mutex_unlock(&all->philos[i].lastmeal);