/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:05:25 by gleal             #+#    #+#             */
/*   Updated: 2022/03/24 21:49:15 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"

//utils.c

int		ft_atoi(const char *str);
long	calctime(const t_gen *gen);
int		is_inbetween_time(double min, double val, double max);

//utils2.c

char	*set_color(int clr);
int		is_input_uint(char **stack_a_args, int argc);
int		is_unsigned_integer(char *str);
int		is_all_digits(char *str);
int		is_within_lims(char *strg);

//utils3.c

int		ft_strlen(char *str);
long	ft_atol(const char *str);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *str, int n);

//mutex_ops.c

void	leave_forks_on_the_table(pthread_mutex_t *right, pthread_mutex_t *left);
int		is_dead(t_philo *philo);
void	rest_cutlery(t_philo *philo);

//mutex_create.c

int		create_gen_mutexes(t_all *all);
int		create_philo_mutexes(t_all *all, int i);
int		delete_other_philo_mutexes(t_all *all, int last);
int		delete_other_philo_mut(t_all *all, int last_created);

#endif
