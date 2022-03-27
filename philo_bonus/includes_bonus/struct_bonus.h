/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:10:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/27 16:42:28 by gleal            ###   ########.fr       */
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
	int		sem_val[4];
	sem_t	*satisfied;
	sem_t	*forkpile;
	sem_t	*carefulprinting;
	sem_t	*finishsim;
}			t_semphs;

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
	int					nbr;
	char				*clr;
	pid_t				proc[10000];
	t_semphs			sm;
	double				act;
	double				lastmeal;
	int					ate;
	pthread_t			monitor_dead;
	pthread_mutex_t		lastmealcheck;
}			t_philo;

typedef struct s_all
{
	t_gen				gen;
	t_philo				philo;
	pthread_mutex_t		finishtype;
	pthread_t			check_ate;
	pthread_t			check_finish;
	int					starve;
}			t_all;

#endif
