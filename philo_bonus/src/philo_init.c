/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:49:31 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/14 10:48:57 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_init_sem(t_data *data)
{
	sem_unlink(FORKS);
	sem_unlink(PRINT);
	data->forks_sem = sem_open(FORKS, O_CREAT | O_EXCL, 0644, data->num_of_philos);
	if (data->forks_sem == SEM_FAILED)
	{
		perror("sem_open (forks_sem)");
		exit(EXIT_FAILURE);
	}
	data->print_sem = sem_open(PRINT, O_CREAT | O_EXCL, 0644, 1);
	if (data->print_sem == SEM_FAILED)
	{
		perror("sem_open (print_sem)");
		sem_close(data->forks_sem);
		sem_unlink(FORKS);
		exit(EXIT_FAILURE);
	}
}

void	ft_init_data(t_data *data, int ac, char **av)
{
	ft_bzero(data, sizeof(t_data));
	data->num_of_philos = (int)ft_atol(av[1]);
	data->time_to_die = (time_t)ft_atol(av[2]);
	data->time_to_eat = (time_t)ft_atol(av[3]);
	data->time_to_sleep = (time_t)ft_atol(av[4]);
	if (ac == 6)
		data->max_meals = (int)ft_atol(av[5]);
	else
		data->max_meals = -1;
	ft_init_sem(data);
}
