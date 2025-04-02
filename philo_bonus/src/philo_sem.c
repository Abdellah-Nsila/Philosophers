/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:26:17 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/02 15:45:10 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// TODO Nice now go :
// TODO 	Make the global init data, basic and global info (times + sem)
// TODO 	Create Processes, and the global monitor
// TODO 	Each child process must have a self die and global monitors threads
// TODO 	The process itself is the routine
// TODO 	Handle exit and clear data 
// TODO 	Be sure to work with all sem that you have now

char	*ft_rand_semname(t_sem *sem)
{
	return (ft_itoa((long)ft_time_now() + (long)sem));
}

void	ft_create_sem(t_sem *sem, int socket)
{
	sem->name = ft_rand_semname(sem);
	sem->ptr = sem_open(sem->name, O_CREAT | O_EXCL, 0644, socket);
	if (sem->ptr == SEM_FAILED)
	{
		perror("sem_open failed");
		exit(EXIT_FAILURE);
	}
}

void	ft_init_sem(t_data *data)
{
	ft_create_sem(&data->forks_sem, data->num_of_philos);
	ft_create_sem(&data->print_sem, 1);
	ft_create_sem(&data->signal_sem, 0);
	ft_create_sem(&data->done_sem, 0);
	ft_create_sem(&data->died_sem, 0);
}

void	ft_free_sem(t_sem *sem)
{
	if (!sem)
		return ;
	if (sem->ptr)
	{
		sem_close(sem->ptr);
		if (sem->name)
			sem_unlink(sem->name);
	}
	if (sem->name)
		free(sem->name);
	return ;
}

void	ft_destroy_sem(t_data *data)
{
	ft_free(&data->forks_sem);
	ft_free(&data->print_sem);
	ft_free(&data->signal_sem);
	ft_free(&data->done_sem);
	ft_free(&data->died_sem);
}
