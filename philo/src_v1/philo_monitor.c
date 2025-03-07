/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:02:28 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/06 14:36:28 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	ft_get_delay(t_data *data, t_state state)
{
	time_t  phase_allowance;

	if (state == EATING)
		phase_allowance = 0;
	else if (state == SLEEPING)
		phase_allowance = data->time_to_sleep;
	else if (state == THINKING)
		phase_allowance = data->time_to_eat / 2;
	else
        phase_allowance = 0;
	return (phase_allowance);

}

void	*ft_monitor(void *arg)
{
	t_data	*data = (t_data *)arg;
	time_t	current_time;
	int		i;

	while (ft_stop_simulation(data) == false)
	{
		i = 0;
		//TODO i want to fix state detlock first sfter that check other issue
		pthread_mutex_lock(&data->meal_mutex);
		while (i < data->num_of_philos)
		{
			//* Check death time
			// pthread_mutex_lock(&data->state_mutex);
			current_time = get_current_time();

			if ((current_time - data->philos[i].last_meal_time)
			> (data->time_to_die + ft_get_delay(data, data->philos[i].state)))
			// if ((current_time - data->philos[i].last_meal_time)
			// > data->time_to_die)
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
				// pthread_mutex_unlock(&data->state_mutex);
				return (NULL);
			}
			// pthread_mutex_unlock(&data->state_mutex);
			i++;
		}
		pthread_mutex_unlock(&data->meal_mutex);
		// usleep(100);
	}
	return (NULL);
}
