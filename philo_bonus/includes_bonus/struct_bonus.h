/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:10:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/19 21:18:18 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_BONUS_H
# define STRUCT_BONUS_H

# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_stats
{
	double	lastsleep;
	double	act;
	double	lastmeal;
	int		finished_eating;
	int		died;
	int		ate;
}			t_stats;

typedef struct s_gen
{
	struct timeval	tval;
	double			tstlife;
	double			tendlife;
	int				philonbr;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				eat_freq;
	pid_t			philos[201];
}			t_gen;

typedef struct s_philo
{
	t_gen const			*gen;
	struct timeval		tval;
	t_stats				stat;
	int					nbr;
	char				*clr;
	pthread_t			check_death;
	pthread_t			check_ate;
	sem_t				*finished_eating;
	sem_t				*simcontinue;
}			t_philo;

typedef struct s_all
{
	t_gen	gen;
	t_philo	philo;
}			t_all;

#endif
