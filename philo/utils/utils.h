/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:05:25 by gleal             #+#    #+#             */
/*   Updated: 2022/03/25 17:19:22 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"

//sim_utils.c

double	calctime(const t_gen *gen);
int		is_inbetween_time(double min, double val, double max);
char	*set_color(int clr);

//input_utils.c

int		is_input_uint(char **stack_a_args, int argc);
int		is_unsigned_integer(char *str);
int		is_all_digits(char *str);
int		is_within_lims(char *strg);

//gen_utils.c

int		ft_atoi(const char *str);
int		ft_strlen(char *str);
long	ft_atol(const char *str);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *str, int n);

//mutex_ops.c

void	leave_forks_on_the_table(pthread_mutex_t *right, pthread_mutex_t *left);
void	death_bed(t_philo *philo);

//mutex_create_destroy.c

int		create_gen_mutexes(t_all *all);
int		delete_gen_mutexes(t_all *all);
int		create_philo_mutexes(t_all *all, int i);
int		delete_other_philo_mutexes(t_all *all, int last);

#endif
