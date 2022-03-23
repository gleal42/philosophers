/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:53:57 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 01:23:23 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

# include "philo.h"

void	*philolife(t_philo *philo);
int		philosleep(t_philo *philo);
int		philothink(t_philo *philo);

//prepare_life.c

int		initlife(int argc, char **argv, t_all *philo);
void	prepare_individuals(t_all	*all);
void	startsim_addphilos(t_all *all);
void	monitordie(t_all *all);

//finish_sim.c

void	check_ate_loop(t_all *all);
void	check_dead_loop(t_all *all);
void	finish_sim(t_all *all);
void	unlock_all_forks(t_all *all);
void	stop_activity(t_all *all);
void	restart_activity(t_all *all);

//forks.c

int		philopickforks(t_philo *philo);
int		try_pick_first_fork(t_philo *philo);
int		try_pick_second_fork(t_philo *philo);

//eating.c

int		philoeat(t_philo *philo, pthread_mutex_t *right, pthread_mutex_t *left);
int		starve(t_philo *philo);
int		eating(t_philo *philo);

#endif
