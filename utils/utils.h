/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:05:25 by gleal             #+#    #+#             */
/*   Updated: 2022/03/14 18:57:53 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"

//utils.c

int		ft_atoi(const char *str);
double	calctime(struct timeval *time);
void	*ft_memset(void *b, int c, size_t len);
int		is_inbetween_time(double min, double val, double max);

//utils2.c

char	*set_color(int clr);
int		is_input_integer(char **stack_a_args);
int		is_integer(char *str);
int		is_all_digits(char *str);
int		is_within_lims(char *strg);

//utils3.c

int		ft_strlen(char *str);
long	ft_atol(const char *str);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *str, int n);

#endif
