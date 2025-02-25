/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:40:11 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/25 18:37:35 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO See this repo https://github.com/mcombeau/philosophers/blob/main/philo/sources/philosopher.c

#include "../includes/philo.h"

void	sim_start_delay(size_t start_time)
{
	while (get_current_time() < start_time)
		continue ;
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_data	*data = philo->data;

	while (1)
	{
		pthread_mutex_lock(&data->meal_mutex);
		philo->last_meal_time = get_current_time();
		pthread_mutex_unlock(&data->meal_mutex);
		sim_start_delay(data->start_time);
		//* Check death flag before attempting to eat
		if (ft_is_death(data))
			break ;
		ft_eat(data, philo);

		//* Check death flag after eating
		if (ft_is_death(data))
			break ;
		ft_print_msg(data, philo, "is sleeping", SLEEP);
		ft_usleep(data, data->time_to_sleep);

		//* Check death flag after sleeping
		if (ft_is_death(data))
			break ;
		ft_print_msg(data, philo, "is thinking", THINK);
	}
	return (NULL);
}

void	ft_create_threads(t_data *data)
{
	int i;

	i = 0;
	data->start_time = get_current_time() + (data->num_of_philos * 2 * 10);
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &ft_philo_routine
			, &data->philos[i]) != 0)
				ft_destroy(data);
		i++;
	}
	if (pthread_create(&data->monitor, NULL, &ft_monitor, data) != 0)
		ft_destroy(data);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			ft_destroy(data);
		i++;
	}
	if (pthread_join(data->monitor, NULL) != 0)
		ft_destroy(data);
}
