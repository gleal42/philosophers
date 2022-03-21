/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:13:49 by gleal             #+#    #+#             */
/*   Updated: 2022/03/20 17:47:26 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "philo_bonus.h"

//utils.c

int		ft_atoi(const char *str);
double	calctime(struct timeval *time);
void	*ft_memset(void *b, int c, size_t len);
int		is_inbetween_time(double min, double val, double max);
void	careful_print(const char *str, t_philo *philo);
void	regular_print(const char *str, t_philo *philo);

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
void	ft_putstr_fd(const char *str, int n);

#endif
