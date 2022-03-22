/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:53:57 by gleal             #+#    #+#             */
/*   Updated: 2022/03/22 17:47:38 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

# include "philo.h"

void	*philolife(t_philo *philo);
void	philosleep(t_philo *philo);
void	philothink(t_philo *philo);

//prepare_life.c

int		initlife(int argc, char **argv, t_all *philo);
void	prepare_individuals(t_all	*all);
void	startsim_addphilos(t_all *all);
void	monitordie(t_all *all);

//finish_sim.c

void	check_ate_loop(t_all *all);
void	check_all_eat(t_all *all);
int		check_dead_philo(t_all *all, int i);
void	finish_sim(t_all *all);
void	unlock_all_forks(t_all *all);
int		did_philo_die(t_all *all, const int i);

//forks.c

void	philopickforks(t_philo *philo);
int		try_pick_first_fork(t_philo *philo);
int		try_pick_second_fork(t_philo *philo);

//eating.c

void	philoeat(t_philo *philo, pthread_mutex_t *right, pthread_mutex_t *left);
int		starve(t_philo *philo);
int		eating(t_philo *philo);

#endif
