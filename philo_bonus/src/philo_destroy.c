/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:38:31 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/13 17:00:32 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_destroy(t_data *data)
{
	sem_close(data->forks_sem);
	sem_close(data->print_sem);
	sem_unlink(FORKS);
	sem_unlink(PRINT);
}