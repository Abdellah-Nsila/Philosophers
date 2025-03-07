/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:57:06 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/07 15:00:57 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_current_time() + (data->num_of_philos * 20);
	while (i < data->num_of_philos)
	{
		data->philos[i].born_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL
			, &ft_start_simulation, &data->philos[i]) != 0)
				return (ft_join_threads(data));
		i++;
	}
	pthread_create(&data->monitor, NULL, ft_monitor, &data);
	ft_join_threads(data);
	
}

void	ft_join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->philos[i].thread)
			if (pthread_join(data->philos[i].thread, NULL) != 0)
				ft_destroy(data);
		i++;
	}
	if (data->monitor)
		if (pthread_join(data->monitor, NULL) != 0)
			ft_destroy(data);
}
