/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:05:53 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/02 15:44:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    ft_init_data(t_data *data, int ac, char **av)
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

void	ft_destroy(t_data *data, int exit_code)
{
	ft_destroy_sem(data);
	exit(exit_code);
}
