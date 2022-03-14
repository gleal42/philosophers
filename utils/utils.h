/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:05:25 by gleal             #+#    #+#             */
/*   Updated: 2022/03/13 19:33:16 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"

int		ft_atoi(const char *str);
double	calctime(struct timeval *time);
void	*ft_memset(void *b, int c, size_t len);
int		is_inbetween_time(double min, double val, double max);
int		initlife(int argc, char **argv, t_all *philo);
char	*set_color(int clr);

#endif
