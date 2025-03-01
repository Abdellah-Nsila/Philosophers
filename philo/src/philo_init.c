/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:53:27 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/01 17:49:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void ft_init_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		if (i % 2)
		{
			data->philos[i].first_fork = &data->forks_mutex[(i + 1) % data->num_of_philos];
			data->philos[i].second_fork = &data->forks_mutex[i];
		}
		else
		{
			data->philos[i].first_fork = &data->forks_mutex[i];
			data->philos[i].second_fork = &data->forks_mutex[(i + 1) % data->num_of_philos];
		}
		i++;
	}
}

// f1 = 0   f2 = 1
// f1 = 1   f2 = 0
// 0 1  

void	ft_init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->forks_mutex[i], NULL);
		i++;
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
	data->philos = ft_calloc(data->num_of_philos, sizeof(t_philo));
	data->forks_mutex = ft_calloc(data->num_of_philos, sizeof(pthread_mutex_t));
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	ft_init_philos(data);
	ft_init_forks(data);
}
