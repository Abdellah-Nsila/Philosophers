/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:42:08 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/14 10:39:32 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_child_process(t_data *data)
{
	t_philo	philo;

	philo.data = data;
	philo.last_meal_time = data->global_start_time;
	ft_launch_threads(data, &philo);
}

void	ft_launch_processes(t_data *data, pid_t pids[PHILO_MAX])
{
	int	i;

	i = 0;
	data->global_start_time = get_current_time() + (data->num_of_philos * 20);
	while (i < data->num_of_philos)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			exit(EXIT_FAILURE);
		if (pids[i] == 0)
		{
			data->id = i + 1;
			ft_child_process(data);
			ft_exit(data, EXIT_SUCCESS);
		}
		i++;
	}
}
