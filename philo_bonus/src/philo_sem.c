/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:26:17 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/04 15:47:13 by abnsila          ###   ########.fr       */
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

char	*ft_rand_semname(int id, char *base)
{
	char	*id_str;
	char	*name;

	id_str = ft_itoa(id);
	name = ft_strjoin(base, id_str);
	free(id_str);
	return (name);
}

void	ft_create_psem(t_sem *sem, int socket, int id, char *base)
{
	sem->name = ft_rand_semname(id, base);
	sem_unlink(sem->name);
	// printf("----------- name: %s, soket: %d ------------\n", sem->name, socket);
	sem->ptr = sem_open(sem->name, O_CREAT | O_EXCL, 0644, socket);
	if (sem->ptr == SEM_FAILED)
	{
		perror("sem_open failed");
		exit(EXIT_FAILURE);
	}
}

void	ft_create_sem(t_sem *sem, char *name, int socket)
{
	sem->name = name;
	sem_unlink(sem->name);
	// printf("name: %s, soket: %d\n", sem->name, socket);
	sem->ptr = sem_open(sem->name, O_CREAT | O_EXCL, 0644, socket);
	if (sem->ptr == SEM_FAILED)
	{
		perror("sem_open failed");
		exit(EXIT_FAILURE);
	}
}

void	ft_init_sem(t_data *data)
{
	ft_create_sem(&data->forks_sem, FORKS_SEM, data->num_of_philos);
	ft_create_sem(&data->print_sem, PRINT_SEM, 1);
	ft_create_sem(&data->signal_sem, SIGNAL_SEM, 1);
	ft_create_sem(&data->emmiter_sem, EMMITER_SEM, 0);
	ft_create_sem(&data->done_sem, DONE_SEM, 0);
	ft_create_sem(&data->died_sem, DIED_SEM, 0);
}

void	ft_free_sem(t_sem *sem, t_bool is_allocated)
{
	if (!sem)
		return ;
	if (sem->ptr)
	{
		sem_close(sem->ptr);
		if (sem->name)
			sem_unlink(sem->name);
	}
	if (is_allocated && sem->name)
		free(sem->name);
	return ;
}

void	ft_destroy_sem(t_data *data)
{
	ft_free_sem(&data->forks_sem, false);
	ft_free_sem(&data->print_sem, false);
	ft_free_sem(&data->signal_sem, false);
	ft_free_sem(&data->emmiter_sem, false);
	ft_free_sem(&data->done_sem, false);
	ft_free_sem(&data->died_sem, false);
}
