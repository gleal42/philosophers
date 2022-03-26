/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:13:49 by gleal             #+#    #+#             */
/*   Updated: 2022/03/26 19:24:40 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "philo_bonus.h"

//init_utils_bonus.c

int		create_philo_mutexes(t_philo *philo);
sem_t	*create_semaphore(const char *str, sem_t **semph, int start_value);
int		error_semaphore(t_semphs *sm, int nbr);
int		error_mutex(t_philo *philo, char *str);

//sim_utils_bonus.c

double	calctime(const t_gen *gen);
int		is_inbetween_time(double min, double val, double max);
int		careful_print(const char *str, t_philo *philo);
void	regular_print(const char *str, t_philo *philo);
char	*set_color(int clr);

//input_utils_bonus.c

int		is_input_integer(char **stack_a_args);
int		is_integer(char *str);
int		is_all_digits(char *str);
int		is_within_lims(char *strg);

//gen_utils_bonus.c

int		ft_strlen(char *str);
void	ft_putstr_fd(const char *str, int n);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
int		ft_isdigit(int c);

//finishsim_bonus.c

void	unlock_finish_simulation(t_all *all);
void	waitremainphilo(t_all *all, int *philoindex);
void	unlock_satisfied(t_all *all);
void	unlock_carefulprinting(t_all *all);
void	philo_drop_forks(t_philo *philo);

#endif
