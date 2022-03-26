/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:10:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/26 17:18:01 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_BONUS_H
# define STRUCT_BONUS_H

# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_semphs
{
	char	*str[4];
	sem_t	*sms[4];
	int		start_val[4];
	sem_t	*satisfied;
	sem_t	*forkpile;
	sem_t	*carefulprinting;
	sem_t	*finishsim;
}			t_semphs;

typedef struct s_stat
{
	double		lastmeal;
	int			ate;
	int			died;
	int			forks_held;
}			t_stat;

typedef struct s_gen
{
	double			tstlife;
	int				philonbr;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				eat_freq;
}			t_gen;

typedef struct s_philo
{
	t_gen const			*gen;
	char				*clr;
	pid_t				proc[201];
	int					nbr;
	t_semphs			sm;
	t_stat				stat;
	pthread_t			mon_own_death;
	pthread_t			mon_finish_sim;
	pthread_mutex_t		lastmealtime;
	pthread_mutex_t		isdone;
	pthread_mutex_t		forksheldcheck;
}			t_philo;

typedef struct s_all
{
	t_gen				gen;
	t_philo				philo;
	pthread_t			check_ate;
	pthread_t			check_finish;
	pthread_mutex_t		finishtype;
	int					deadfinish;
}			t_all;

#endif
