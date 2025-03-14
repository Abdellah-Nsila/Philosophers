/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:42:08 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/14 09:46:53 by abnsila          ###   ########.fr       */
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
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	printf("Thread From proc: %d\n", data->id);
	return (NULL);
}


void	ft_child_process(t_data *data)
{
	t_philo	philo;

	philo.data = data;
	printf("The Child PID: %d\n", getpid());
	if (pthread_create(&(philo.routine_thread), NULL, &ft_start_simulation, &philo) != 0)
		perror("create");
	if (pthread_join(philo.routine_thread, NULL) != 0)
		perror("join");
}

void	ft_launch_processes(t_data *data, pid_t pids[PHILO_MAX])
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			exit(EXIT_FAILURE);
		if (pids[i] == 0)
		{
			data->id = i + 1;
			ft_child_process(data);
			ft_destroy(data);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

