/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:53:40 by gleal             #+#    #+#             */
/*   Updated: 2022/03/08 18:11:41 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "life.h"

int		initlife(int argc, char **argv, t_all *all)
{
	gettimeofday(&all->gen.st_t, NULL);
	all->gen.nbr = ft_atoi(argv[1]);
	all->gen.t_die = ft_atoi(argv[2]);
	all->gen.t_eat = ft_atoi(argv[3]);
	all->gen.t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		all->gen.eat_freq = ft_atoi(argv[5]);
		if (all->gen.eat_freq == 0)
			return (1);
	}
	else
		all->gen.eat_freq = 0;
	all->philos.gen = (const)all->gen;
	return (0);
}

void	philoeat(t_philo *philo)
{
	gettimeofday(&philo->cur_t, NULL);
	printf("%ld is eating\n", 
	(philo->cur_t.tv_sec - philo->st_t.tv_sec) * 1000 + 
	(philo->cur_t.tv_usec - philo->st_t.tv_usec)/1000);
	usleep(philo-> * 1000);
}

void	philosleep(t_all *all)
{
	gettimeofday(&all->new_ph, NULL);
	printf("%ld is sleeping\n", 
	(all->new_ph.tv_sec - all->st_ph.tv_sec) * 1000 + 
	(all->new_ph.tv_usec - all->st_ph.tv_usec)/1000);
	usleep(all->t_sleep * 1000);
}

void	philothink(t_all *all)
{
	gettimeofday(&all->new_ph, NULL);
	printf("%ld is thinking\n",
	(all->new_ph.tv_sec - all->st_ph.tv_sec) * 1000 + 
	(all->new_ph.tv_usec - all->st_ph.tv_usec)/1000); 
}