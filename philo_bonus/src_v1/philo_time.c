/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 07:31:56 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/27 17:20:03 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	get_current_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(t_philo *philo, time_t milliseconds)
{
	time_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		sem_wait(&philo->stop_sem);
		if (philo->stop_flag)
		{
			sem_post(&philo->stop_sem);
			break ;
		}
		sem_post(&philo->stop_sem);
		usleep(500);
	}
}

void	ft_start_delay(time_t start_time)
{
	while (get_current_time() < start_time)
		continue ;
}
