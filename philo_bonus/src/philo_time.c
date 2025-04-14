/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 07:31:56 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/14 11:29:52 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	ft_get_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(t_philo *philo, time_t milliseconds) {
	time_t start = ft_get_time();
	(void)philo;

	while ((ft_get_time() - start) < milliseconds)
	{
		usleep(500);
	}
}

void	ft_start_delay(time_t start_time)
{
	while (ft_get_time() < start_time)
		continue ;
}
