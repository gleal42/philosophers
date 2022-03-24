/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:05:08 by gleal             #+#    #+#             */
/*   Updated: 2022/03/24 18:21:52 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
