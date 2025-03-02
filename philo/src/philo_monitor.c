/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:02:28 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/02 10:24:33 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_monitor(void *arg)
{
	t_data	*data = (t_data *)arg;
	time_t	current_time;
	int		i;

	// sim_start_delay(data->start_time);
	while (!ft_is_death(data))
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			pthread_mutex_lock(&data->meal_mutex);
			current_time = get_current_time();
			if (current_time - data->philos[i].last_meal_time > data->time_to_die)
			{
				// printf("time: %ld\n", current_time - data->philos[i].last_meal_time);
				pthread_mutex_lock(&data->death_mutex);
				ft_print_msg(data, &data->philos[i], "died", DIE);
				data->someone_died = 1;
				pthread_mutex_unlock(&data->death_mutex);
				pthread_mutex_unlock(&data->meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->meal_mutex);
			i++;
		}
		// usleep(100); // Reduce CPU usage
	}
	return (NULL);
}
