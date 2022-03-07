/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:31:43 by gleal             #+#    #+#             */
/*   Updated: 2022/03/07 21:09:07by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	philoeat(t_philo *philo)
{
	gettimeofday(&philo->new_ph, NULL);
	printf("%ld is eating\n", 
	(philo->new_ph.tv_sec - philo->st_ph.tv_sec) * 1000 + 
	(philo->new_ph.tv_usec - philo->st_ph.tv_usec)/1000);
}

void	philosleep(t_philo *philo)
{
	gettimeofday(&philo->new_ph, NULL);
	printf("%ld is sleeping\n", 
	(philo->new_ph.tv_sec - philo->st_ph.tv_sec) * 1000 + 
	(philo->new_ph.tv_usec - philo->st_ph.tv_usec)/1000);
}

void	philothink(t_philo *philo)
{
	gettimeofday(&philo->new_ph, NULL);
	printf("%ld is thinking\n",
	(philo->new_ph.tv_sec - philo->st_ph.tv_sec) * 1000 + 
	(philo->new_ph.tv_usec - philo->st_ph.tv_usec)/1000); 
}

void	philolife(int argc, char **argv)
{
	t_philo philo;

	(void)argc;
	(void)argv;
	gettimeofday(&philo.st_ph, NULL);
	philoeat(&philo);
	philosleep(&philo);
	philothink(&philo);
}

int	main(int argc, char **argv)
{
	//if (argc >= 5 && argc <= 6)
		philolife(argc, argv);
}