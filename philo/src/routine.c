/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviscogl <aviscogl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:00:33 by naterrie          #+#    #+#             */
/*   Updated: 2023/07/12 01:23:58 by aviscogl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

int	ft_start_routine(t_info *info)
{
	int				i;
	struct timeval	time;

	i = 0;
	gettimeofday(&time, NULL);
	printf("kk\n");
	while (i < info->number_ph)
	{
		if (pthread_create(&info->philo[i].thread, NULL, \
			&ft_philo_routine, &info->philo[i]) != 0)
		{
			printf("Philo error: pthread_create\n");
			exit(1);
		}
		i++;
	}
	info->start = ft_get_time();
	while ( i < info->number_ph)
	{
		if (pthread_join(info->philo[i].thread, NULL))
			return (printf("Philo error: pthread_join\n"), free(info->philo), exit(1), 1);
		i++;
	}
	return (0);
}