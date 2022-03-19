/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:12:11 by gleal             #+#    #+#             */
/*   Updated: 2022/03/19 18:46:10 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_BONUS_H
# define LIFE_BONUS_H

# include "philo_bonus.h"

void	*philolife(t_philo *philo);
void	philopickforks(t_philo *philo);
void	philoeat(t_philo *philo);
void	philosleep(t_philo *philo);
void	philothink(t_philo *philo);

//prepare_life.c

int		initlife(int argc, char **argv, t_all *philo);
void	prepare_individuals(t_all	*all);

//finish_sim.c

void	*check_ate(t_all *all);
void	checkdeathsetminate(t_all *all);
void	finish_sim(t_all *all);

//forks.c

void	starve(t_philo *philo);
void	eating(t_philo *philo);
void	leave_forks_on_the_table(pthread_mutex_t *right, pthread_mutex_t *left);

#endif
