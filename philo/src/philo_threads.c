/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:40:11 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/01 18:41:30 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO See this repo https://github.com/mcombeau/philosophers/blob/main/philo/sources/philosopher.c

#include "../includes/philo.h"

void	sim_start_delay(time_t start_time)
{
	while (get_current_time() < start_time)
		continue ;
}

t_bool	ft_philo_routine(t_data *data, t_philo *philo)
{
	// --------------------------- Simulate eating ----------------------------
	ft_eat(data, philo);

	//* Check death flag after eating
	if (ft_is_death(data) || data->num_of_philos < 2)
		return(false);
	// --------------------------- Simulate slepping ----------------------------
	ft_print_msg(data, philo, "is sleeping", SLEEP);
	ft_usleep(data, data->time_to_sleep);

	//* Check death flag after sleeping
	if (ft_is_death(data))
		return(false);
	// --------------------------- Simulate Thinking ----------------------------
	ft_print_msg(data, philo, "is thinking", THINK);
	return (true);
}


//TODO Test this fromthe repo n: 3  tested in you terminal (Remember me for this)
// t_bool	ft_philo_routine(t_data *data, t_philo *philo)
// {
// 	pthread_mutex_lock(philo->first_fork);
// 	ft_print_msg(data, philo, " has taken a fork", TAKE_FORK);
// 	pthread_mutex_lock(philo->second_fork);
// 	ft_print_msg(data, philo, " has taken a fork", TAKE_FORK);
// 	pthread_mutex_lock(&data->meal_mutex);
// 	ft_print_msg(data, philo, " is eating", EAT);
// 	philo->last_meal_time = get_current_time();
// 	philo->meals_eaten += 1;
// 	pthread_mutex_unlock(&data->meal_mutex);
// 	ft_usleep(data, data->time_to_eat);
// 	pthread_mutex_unlock(philo->first_fork);
// 	pthread_mutex_unlock(philo->second_fork);
	
// 	ft_print_msg(data, philo, "is sleeping", SLEEP);
// 	ft_usleep(data, data->time_to_sleep);
// 	ft_print_msg(data, philo, "is thinking", THINK);
// 	return (true);
// }

void	*ft_start_simulation(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_data	*data = philo->data;

	// sim_start_delay(data->start_time);
	if (philo->id % 2 == 0)
		ft_usleep(data, 1);
	pthread_mutex_lock(&data->meal_mutex);
	philo->born_time = get_current_time();
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&data->meal_mutex);
	while (ft_is_death(data) == false)
	{
		if (ft_philo_routine(data, philo) == false)
			break;
	}
	return (NULL);
}

void	ft_create_threads(t_data *data)
{
	int i;

	i = 0;
	// data->start_time = get_current_time() + (data->num_of_philos * 2 * 10);
	// data->start_time = get_current_time() + data->time_to_eat;
	data->start_time = get_current_time();
	while (i < data->num_of_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, &ft_start_simulation
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
