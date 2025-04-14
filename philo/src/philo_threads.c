/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:57:06 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/14 11:32:54 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_join_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		if (data->philos[i].thread)
			pthread_join(data->philos[i].thread, NULL);
	}
	pthread_join(data->monitor, NULL);
}

void	ft_create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time() + (data->num_of_philos * 20);
	while (i < data->num_of_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL
				, &ft_start_simulation, &data->philos[i]) != 0)
			return (ft_join_threads(data));
		i++;
	}
	if (pthread_create(&data->monitor, NULL, &ft_monitor, data) != 0)
		return (ft_join_threads(data));
	ft_join_threads(data);
}
