/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:33:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/08 15:09:56 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_colored_msg(time_t timestamp, int id, int type)
{
	char	*format;
	(void)type;

	format = "%s%ld %d %s\n%s";
	if (type == TAKING_FORK)
		printf(format, BWHT, timestamp, id, "has taken a fork", RESET);
	else if (type == THINKING)
		printf(format, BBLU, timestamp, id, "is thinking", RESET);
	else if (type == EATING)
		printf(format, BGRN, timestamp, id, "is eating", RESET);
	else if (type == SLEEPING)
		printf(format, BMAG, timestamp, id, "is sleeping", RESET);
	else if (type == DIED)
		printf(format, BRED, timestamp, id, "died", RESET);
	else
		printf(format, BWHT, timestamp, id, "just a test", RESET);
}

void	ft_print_msg(t_data *data, t_philo *philo, int type)
{
	time_t	timestamp;
	time_t	current_time;

	current_time = get_current_time();
	timestamp = current_time - data->start_time;
	pthread_mutex_lock(&data->print_mutex);
	ft_colored_msg(timestamp, philo->id, type);
	pthread_mutex_unlock(&data->print_mutex);
}
