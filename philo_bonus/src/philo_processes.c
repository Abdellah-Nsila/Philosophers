/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:42:08 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/13 17:02:07 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_bool	ft_philo_routine(t_data *data)
{
	// t_philo	*philo;

	// philo = data->philo;
	printf("Thread From proc: %d\n", data->id);
	return (true);
}

void	*ft_start_simulation(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	printf("Thread From proc: %d\n", data->id);
	return (NULL);
}

void	ft_launch_processes(t_data *data, pid_t pids[PHILO_MAX])
{
	t_philo	*philo;
	int		i;

	philo = data->philo;
	i = 0;
	while (i < data->num_of_philos)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			exit(EXIT_FAILURE);
		if (pids[i] == 0)
		{
			printf("gg\n");
			data->id = i + 1;
			pthread_create(&philo->routine_thread, NULL, &ft_start_simulation, data);
			pthread_join(philo->routine_thread, NULL);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

