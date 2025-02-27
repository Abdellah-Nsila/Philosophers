/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:40:11 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/27 11:53:29 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO See this repo https://github.com/mcombeau/philosophers/blob/main/philo/sources/philosopher.c

#include "../includes/philo.h"

void	sim_start_delay(time_t start_time)
{
	while (get_current_time() < start_time)
		continue ;
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_data	*data = philo->data;

	// sim_start_delay(data->start_time);
	if (philo->id % 2 == 0)
		ft_usleep(data, 1);
	//TODO Why the born time is not init correctly before use it ??
	pthread_mutex_lock(&data->meal_mutex);
	philo->born_time = get_current_time();
	philo->last_meal_time = get_current_time();
	printf("born time for %d: %ld\n",philo->id, philo->born_time);
	pthread_mutex_unlock(&data->meal_mutex);
	while (ft_is_death(data) == false)
	{
		// --------------------------- Simulate eating ----------------------------
		ft_eat(data, philo);

		//* Check death flag after eating
		if (ft_is_death(data) || data->num_of_philos < 2)
			break ;
		// --------------------------- Simulate slepping ----------------------------
		ft_print_msg(data, philo, "is sleeping", SLEEP);
		ft_usleep(data, data->time_to_sleep);

		//* Check death flag after sleeping
		if (ft_is_death(data))
			break ;
		// --------------------------- Simulate Thinking ----------------------------
		ft_print_msg(data, philo, "is thinking", THINK);
		// ft_usleep(data, 10);
	}
	return (NULL);
}

void	ft_create_threads(t_data *data)
{
	int i;

	i = 0;
	// data->start_time = get_current_time() + (data->num_of_philos * 2 * 10);
	while (i < data->num_of_philos)
	{
		// data->philos[i].last_meal_time = data->start_time;
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
	// while (i < data->num_of_philos)
	// {
	// 	if (pthread_detach(data->philos[i].thread) != 0)
	// 		ft_destroy(data);
	// 	i++;
	// }
	if (pthread_join(data->monitor, NULL) != 0)
		ft_destroy(data);
}
