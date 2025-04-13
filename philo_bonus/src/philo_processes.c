/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:46:11 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/13 17:57:29 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_done_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (i < data->num_of_philos)
	{
		printf("Now\n");
		sem_wait(data->done_sem.ptr);
		i++;
	}
	printf("GG\n");
	sem_post(data->died_sem.ptr);
	return (NULL);
}

t_bool	ft_launch_processes(t_data *data, pid_t pids[PHILO_MAX])
{
	int	i;

	i = 0;
	data->global_start_time = get_current_time() + (data->num_of_philos * 20);
	while (i < data->num_of_philos)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (false);
		if (pids[i] == 0)
			ft_child_process(data, i + 1);
		i++;
	}
	if (pthread_create(&(data->done_monitor), NULL, &ft_done_monitor, data))
		return (false);
	if (pthread_join(data->done_monitor, NULL))
		return (false);
	while (i < data->num_of_philos && waitpid(pids[i], NULL, 0))
	{
		// waitpid(pids[i], NULL, 0);
		i++;
	}
	return (true);
}
