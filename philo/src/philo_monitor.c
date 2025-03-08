/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:16:45 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/08 15:24:12 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_bool	ft_did_everyone_eat(t_data *data)
{
	int		i;
	t_bool	all_eaten;

	i = 0;
	all_eaten = true;
	pthread_mutex_lock(&data->meal_mutex);
	while (i < data->num_of_philos)
	{
		if (data->philos[i].meals_eaten < data->max_meals)
		{
			all_eaten = false;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	if (all_eaten)
	{
		pthread_mutex_lock(&data->stop_mutex);
		data->stop = true;
		pthread_mutex_unlock(&data->stop_mutex);
	}
	return (all_eaten);
}

t_bool	ft_did_anyone_die(t_data *data)
{
	int		i;
	time_t	current_time;

	i = 0;
	current_time = get_current_time();
	pthread_mutex_lock(&data->meal_mutex);
	while (i < data->num_of_philos)
	{
		if ((current_time - data->philos[i].last_meal_time) > data->time_to_die)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = true;
			pthread_mutex_unlock(&data->stop_mutex);
			pthread_mutex_lock(&data->print_mutex);
			ft_colored_msg(current_time - data->start_time, data->philos[i].id, DIED);
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_unlock(&data->meal_mutex);
			return (true);
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (false);
}

// void	*ft_monitor(t_data *data)
void	*ft_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	ft_start_delay(data->start_time);
	while (true)
	{
		if (data->max_meals != -1 && ft_did_everyone_eat(data))
			return (NULL);
		if (ft_did_anyone_die(data))
			return (NULL);
	}
	return (NULL);
}
