/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 07:31:56 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/07 17:09:46 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	get_current_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// void	ft_usleep(t_philo *philo, time_t milliseconds)
// {
// 	(void)philo;
// 	time_t	start;

// 	start = get_current_time();
// 	while (((get_current_time() - start) < milliseconds))
// 	{
// 		usleep(10000);
// 		sem_wait(philo->done_sem.ptr);
// 		if (philo->is_done)
// 		{
// 			sem_post(philo->done_sem.ptr);
// 			return ;
// 		}
// 		sem_post(philo->done_sem.ptr);
// 		usleep(10000);
// 	}
// }

void	ft_usleep(t_philo *philo, time_t milliseconds)
{
	time_t start = get_current_time();
	time_t elapsed;

	while ((elapsed = get_current_time() - start) < milliseconds) {
		if (elapsed > milliseconds / 2) {
			usleep(1000);  // Shorter sleeps as deadline approaches
		} else {
			usleep(500);
		}
		sem_wait(philo->done_sem.ptr);
		if (philo->is_done) {
			sem_post(philo->done_sem.ptr);
			return;
		}
		sem_post(philo->done_sem.ptr);
	}
}


void	ft_start_delay(time_t start_time)
{
	while (get_current_time() < start_time)
		continue ;
}
