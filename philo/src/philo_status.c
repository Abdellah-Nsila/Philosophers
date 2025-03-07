/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:33:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/07 14:40:23 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_colored_msg(time_t timestamp, int id, char *msg, int type)
{
	char	*format;

	format = "%s%ld %d %s\n%s";
	if (type == TAKING_FORK)
		printf(format, WHT, timestamp, id, msg, RESET);
	else if (type == THINKING)
		printf(format, BLU, timestamp, id, msg, RESET);
	else if (type == EATING)
		printf(format, GRN, timestamp, id, msg, RESET);
	else if (type == SLEEPING)
		printf(format, MAG, timestamp, id, msg, RESET);
	else if (type == DIED)
		printf(format, RED, timestamp, id, msg, RESET);
	else
		printf(format, BWHT, timestamp, id, msg, RESET);
}

void	ft_print_msg(t_data *data, t_philo *philo, char *msg, int type)
{
	time_t	timestamp;
	time_t	current_time;

	pthread_mutex_lock(&data->print_mutex);
	current_time = get_current_time();
	timestamp = current_time - philo->born_time;
	// timestamp = current_time - data->start_time;
	ft_colored_msg(timestamp, philo->id, msg, type);
	pthread_mutex_unlock(&data->print_mutex);
}
