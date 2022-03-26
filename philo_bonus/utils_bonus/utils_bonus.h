/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:13:49 by gleal             #+#    #+#             */
/*   Updated: 2022/03/26 18:28:52 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "philo_bonus.h"

//utils.c

int		ft_atoi(const char *str);
double	calctime(const t_gen *gen);
void	*ft_memset(void *b, int c, size_t len);
int		is_inbetween_time(double min, double val, double max);
int		careful_print(const char *str, t_philo *philo);
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

void	unlock_finish_simulation(t_all *all);
void	waitremainphilo(t_all *all, int *philoindex);
void	unlock_carefulprinting(t_all *all);
void	unlock_satisfied(t_all *all);
void	philo_drop_forks(t_philo *philo);

#endif
