/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:46:11 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/03 16:06:49 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_done_monitor(void *arg)
{
	printf("ft_done_monitor here\n");
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (i < data->num_of_philos)
	{
		sem_wait(data->done_sem.ptr);
		i++;
	}
	sem_post(data->died_sem.ptr);
	return (NULL);
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
			ft_child_process(data, i + 1);
		i++;
	}
	if (pthread_create(&(data->done_monitor), NULL, &ft_done_monitor, data))
		exit(EXIT_FAILURE);
	if (pthread_join(data->done_monitor, NULL))
		exit(EXIT_FAILURE);
	while (i < data->num_of_philos)
	{	
		waitpid(pids[i], NULL, 0);
		i++;
	}
}
