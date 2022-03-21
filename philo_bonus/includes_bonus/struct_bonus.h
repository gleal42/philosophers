/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:10:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/21 01:43:03 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_BONUS_H
# define STRUCT_BONUS_H

# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

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
}			t_gen;

typedef struct s_philo
{
	t_gen const			*gen;
	struct timeval		tval;
	int					nbr;
	char				*clr;
	sem_t				*satisfied;
	sem_t				*forkpile;
	sem_t				*carefulprinting;
	sem_t				*finishsim;
	pid_t				proc[201];
	double				lastsleep;
	double				act;
	double				lastmeal;
	int		ate;
}			t_philo;

typedef struct s_all
{
	t_gen	gen;
	t_philo	philo;
	pthread_mutex_t finishtype;
	pthread_t			check_ate;
	int		starve;
}			t_all;

#endif
