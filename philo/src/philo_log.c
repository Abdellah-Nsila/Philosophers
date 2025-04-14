/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:33:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/14 14:39:06 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_format_msg(time_t timestamp, int id, int type)
{
	char	*format;

	format = "%ld %d %s\n";
	if (type == TAKING_FORK)
		printf(format, timestamp, id, "has taken a fork");
	else if (type == THINKING)
		printf(format, timestamp, id, "is thinking");
	else if (type == EATING)
		printf(format, timestamp, id, "is eating");
	else if (type == SLEEPING)
		printf(format, timestamp, id, "is sleeping");
	else if (type == DIED)
		printf(format, timestamp, id, "died");
}

void	ft_print_msg(t_data *data, t_philo *philo, int type)
{
	time_t	current_time;
	time_t	timestamp;

	pthread_mutex_lock(&data->print_mutex);
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		pthread_mutex_unlock(&data->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&data->stop_mutex);
	current_time = ft_get_time();
	timestamp = current_time - data->start_time;
	ft_format_msg(timestamp, philo->id, type);
	pthread_mutex_unlock(&data->print_mutex);
}
