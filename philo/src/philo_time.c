/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 07:31:56 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/09 16:02:02 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	get_current_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_usleep(t_data *data, time_t milliseconds)
{
    time_t start = get_current_time();
    while ((get_current_time() - start) < milliseconds)
    {
        if (ft_stop_simulation(data))
            break;
        usleep(100);
    }
}


void	ft_start_delay(time_t start_time)
{
	while (get_current_time() < start_time)
		continue ;
}
