/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:53:57 by gleal             #+#    #+#             */
/*   Updated: 2022/03/14 20:07:16 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

# include "philo.h"

void	*philolife(t_philo *philo);
void	philopickforks(t_philo *philo);
void	philoeat(t_philo *philo, t_fork *forkone, t_fork *forktwo);
void	philosleep(t_philo *philo);
void	philothink(t_philo *philo);

//prepare_life.c

int		initlife(int argc, char **argv, t_all *philo);
void	prepare_individuals(t_all	*all);
void	create_individuals(t_all *all);

//finish_sim.c

void	check_finish_sim(t_all *all);
void	checkdeathsetminate(t_all *all);
void	finish_sim(t_all *all);
void	pick_fork(t_philo *philo, t_fork *pickedfork);

//forks.c

void	starve(t_philo *philo);
void	eating(t_philo *philo);
void	leave_forks_on_the_table(t_fork *forkone, t_fork *forktwo);

#endif
