/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:38:31 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/27 14:13:38 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_destroy_semaphores(t_data *data)
{
	if (data->forks_sem != SEM_FAILED)
	{
		sem_close(data->forks_sem);
		sem_unlink(FORKS);
	}
	if (data->print_sem != SEM_FAILED)
	{
		sem_close(data->print_sem);
		sem_unlink(PRINT);
	}
}

void    ft_exit_process(t_data *data, t_philo *philo, int exit_code)
{
    if (data->forks_sem != SEM_FAILED)
        sem_close(data->forks_sem);
    if (data->print_sem != SEM_FAILED)
        sem_close(data->print_sem);
    if (philo)
    {
        sem_destroy(&philo->meal_sem);
        sem_destroy(&philo->stop_sem);
    }
    exit(exit_code);
}

void	ft_exit(t_data *data, int exit_code)
{
	ft_destroy_semaphores(data);
	exit(exit_code);
}
