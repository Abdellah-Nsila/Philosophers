/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:02:28 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/05 14:57:27 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_monitor(void *arg)
{
	t_data	*data = (t_data *)arg;
	time_t	current_time;
	int		i;

	while (ft_stop_simulation(data) == false)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			//* Check death time
			pthread_mutex_lock(&data->meal_mutex);
			current_time = get_current_time();
			if (current_time - data->philos[i].last_meal_time > data->time_to_die)
			{
				//* Set ON The stop flag
				pthread_mutex_lock(&data->stop_mutex);
				data->stop = 1;
				pthread_mutex_unlock(&data->stop_mutex);
				//* Print death msg
				pthread_mutex_lock(&data->print_mutex);
				current_time = get_current_time();
				ft_colored_msg(current_time - data->start_time, data->philos[i].id, "died", DIED);
				//* Unlock Mutex and return
				pthread_mutex_unlock(&data->print_mutex);
				pthread_mutex_unlock(&data->meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->meal_mutex);
			i++;
		}
		// usleep(100);
	}
	return (NULL);
}
