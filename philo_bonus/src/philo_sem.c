/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:26:17 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/14 11:27:36 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_create_psem(t_sem *sem, int socket, int id, char *base)
{
	sem->name = ft_rand_semname(id, base);
	sem_unlink(sem->name);
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
	ft_create_sem(&data->half_sem, HALF_SEM, data->num_of_philos / 2);
	ft_create_sem(&data->print_sem, PRINT_SEM, 1);
	ft_create_sem(&data->signal_sem, SIGNAL_SEM, 1);
	ft_create_sem(&data->emmiter_sem, EMMITER_SEM, 0);
	ft_create_sem(&data->done_sem, DONE_SEM, 0);
	ft_create_sem(&data->died_sem, DIED_SEM, 0);
}

void	ft_destroy_sem(t_data *data)
{
	ft_free_sem(&data->forks_sem, false);
	ft_free_sem(&data->half_sem, false);
	ft_free_sem(&data->print_sem, false);
	ft_free_sem(&data->signal_sem, false);
	ft_free_sem(&data->emmiter_sem, false);
	ft_free_sem(&data->done_sem, false);
	ft_free_sem(&data->died_sem, false);
}
