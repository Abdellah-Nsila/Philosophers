/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:46:11 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/02 15:59:59 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_child_process(t_data *data, int i)
{
	t_philo	philo;

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
			ft_child_process(data, i);
		i++;
	}
}
