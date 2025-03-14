/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:38:31 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/14 09:50:46 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_destroy(t_data *data)
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
