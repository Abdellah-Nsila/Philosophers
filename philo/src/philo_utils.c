/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:44:12 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/09 16:03:18 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_bool	ft_stop_simulation(t_data *data)
{
	t_bool	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

void	ft_print_data(t_data *data)
{
	printf("num_of_philos: %d\n", data->num_of_philos);
	printf("time_to_die: %ld\n", data->time_to_die);
	printf("time_to_eat: %ld\n", data->time_to_eat);
	printf("time_to_sleep: %ld\n", data->time_to_sleep);
	printf("max_meals: %d\n", data->max_meals);
}

