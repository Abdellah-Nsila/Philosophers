/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:40:11 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/03 17:51:39 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO See this repo https://github.com/mcombeau/philosophers/blob/main/philo/sources/philosopher.c

#include "../includes/philo.h"

void	sim_start_delay(time_t start_time)
{
	while (get_current_time() < start_time)
		continue ;
}

void	ft_think(t_philo *philo, t_bool start)
{
	t_data	*data;
	time_t	time_to_think;

	data = philo->data;
	pthread_mutex_lock(&data->meal_mutex);
	time_to_think = (data->time_to_die 
		- (get_current_time() - philo->last_meal_time)
		- data->time_to_eat) / 2;
	pthread_mutex_unlock(&data->meal_mutex);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && start == true)
		time_to_think = 1;
	if (time_to_think > 400)
		time_to_think = 100;
	if (start == false)
		ft_print_msg(data, philo, "is thinking", THINK);
	ft_usleep(data, time_to_think);
}

//TODO Test this fromthe repo n: 3  tested in you terminal (Remember me for this)
t_bool	should_skip_turn(t_data *data, t_philo *philo)
{
	int	i;
	int	min_meals;

	pthread_mutex_lock(&data->meal_mutex);
	min_meals = data->philos[0].meals_eaten;
	for (i = 1; i < data->num_of_philos; i++)
	{
		if (data->philos[i].meals_eaten < min_meals)
			min_meals = data->philos[i].meals_eaten;
	}
	pthread_mutex_unlock(&data->meal_mutex);

	if (philo->meals_eaten > min_meals + 1)
		return (true);
	return (false);
}

t_bool	ft_philo_routine(t_data *data, t_philo *philo)
{
	// Attempt to take forks
	pthread_mutex_lock(philo->first_fork);
	if (ft_stop_simulation(data))
	{
		pthread_mutex_unlock(philo->first_fork);
		return (false);
	}
	ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);

	if (ft_stop_simulation(data) || data->num_of_philos < 2)
	{
		pthread_mutex_unlock(philo->first_fork);
		return (false);
	}

	pthread_mutex_lock(philo->second_fork);
	if (ft_stop_simulation(data))
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return (false);
	}
	ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);

	if (ft_is_death(data))
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return (false);
	}
	
	// Eat
	pthread_mutex_lock(&data->meal_mutex);
	ft_print_msg(data, philo, "is eating", EAT);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&data->meal_mutex);

	if (ft_is_death(data))
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return (false);
	}

	ft_usleep(data, data->time_to_eat);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);

	if (ft_stop_simulation(data))
		return (false);

	// Sleep
	ft_print_msg(data, philo, "is sleeping", SLEEP);
	ft_usleep(data, data->time_to_sleep);

	if (ft_stop_simulation(data))
		return (false);

	// Think
	// ft_print_msg(data, philo, "is thinking", THINK);
	ft_think(philo, false);
	return (true);
}

void	*ft_start_simulation(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_data	*data = philo->data;
	
	sim_start_delay(data->start_time);
	if (philo->id % 2)
		ft_think(philo, true);
	while (1)
	{
		if (ft_philo_routine(data, philo) == false)
			break;
		if (data->max_meals != -1 && philo->meals_eaten >= data->max_meals)
			break;
	}
	return (NULL);
}

void	ft_create_threads(t_data *data)
{
	int i;

	i = 0;
	data->start_time = get_current_time() + (data->num_of_philos * 20);
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
	if (pthread_join(data->monitor, NULL) != 0)
		ft_destroy(data);
}
