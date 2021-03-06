/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:12:11 by gleal             #+#    #+#             */
/*   Updated: 2022/03/21 17:01:35 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_BONUS_H
# define LIFE_BONUS_H

# include "philo_bonus.h"

int		philolife(t_philo *philo);
int		philopickforks(t_philo *philo);
int		philoeat(t_philo *philo);
int		philosleep(t_philo *philo);
int		philothink(t_philo *philo);
int		philokill(t_philo *philo);

//prepare_life.c

int		initlife(int argc, char **argv, t_all *philo);
sem_t	*create_semaphore(const char *str, sem_t **semph, int start_value);
int		error_semaphore(t_semphs *sm, int nbr);
int		prepare_semaphores(t_all *all);

//finish_sim.c

void	*check_ate(t_all *all);
void	checkdeathsetminate(t_all *all);
void	finish_sim(t_all *all);

//forks.c

int		starve(t_philo *philo);
int		eating(t_philo *philo);
void	leave_forks_on_the_table(pthread_mutex_t *right, pthread_mutex_t *left);

#endif
