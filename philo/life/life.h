/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:53:57 by gleal             #+#    #+#             */
/*   Updated: 2022/03/27 03:52:28 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

# include "philo.h"

//init_sim.c

int		initlife(int argc, char **argv, t_all *philo);
int		prepare_individuals(t_all	*all);
int		startsim_addphilos(t_all *all);
void	monitordie(t_all *all);
int		remove_remain_philos_mutexes(t_all *all, int last);

//life.c

void	*philolife(t_philo *philo);
int		philosleep(t_philo *philo);
int		philothink(t_philo *philo);
int		protected_printing(const char *str, t_philo *philo);

//forks.c

int		philopickforks(t_philo *philo);
int		try_pick_first_fork(t_philo *philo, pthread_mutex_t *fstfork);
int		try_pick_second_fork(t_philo *philo,
			pthread_mutex_t *fstfork, pthread_mutex_t *secfork);

//eating.c

int		philoeat(t_philo *philo, pthread_mutex_t *right, pthread_mutex_t *left);
void	*starve(t_philo *philo);

//monitor.c

int		check_ate_loop(t_all *all, int i);
void	check_finish_loop(t_all *all);

//finish_sim.c

int		finish_sim(t_all *all);
void	unlock_all_forks(t_all *all);
int		lock_finishtype(t_all *all);

#endif
