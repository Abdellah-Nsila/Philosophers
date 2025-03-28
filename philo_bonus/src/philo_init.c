/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:05:53 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/28 17:22:15 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

char	*ft_rand_semname(t_sem *sem)
{
	return (ft_itoa((long)ft_time_now() + (long)sem));
}

void	ft_create_sem(t_sem *sem, int socket)
{
	sem->name = ft_rand_semname(sem);
	sem->sem = sem_open(FORKS, O_CREAT | O_EXCL, 0644, socket);
	if (sem->sem == SEM_FAILED)
	{
		perror("sem_open failed");
		exit(EXIT_FAILURE);
	}
}

void	ft_init_sem(t_data *data)
{
	ft_create_sem(&data->forks_sem, data->num_of_philos);
	ft_create_sem(&data->print_sem, 1);
	ft_create_sem(&data->done_sem, 0);
	ft_create_sem(&data->died_sem, 0);
}
