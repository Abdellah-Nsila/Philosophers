/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:27:44 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/14 16:46:03 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_bool	ft_take_forks(t_data *data, t_philo *philo)
{
	if (pthread_mutex_lock(philo->first_fork) != 0)
		return (false);
	ft_print_msg(data, philo, TAKING_FORK);
	if (data->num_of_philos < 2 || pthread_mutex_lock(philo->second_fork) != 0)
	{
		pthread_mutex_unlock(philo->first_fork);
		return (false);
	}
	ft_print_msg(data, philo, TAKING_FORK);
	return (true);
}

t_bool	ft_eat(t_data *data, t_philo *philo)
{
	ft_print_msg(data, philo, EATING);
	pthread_mutex_lock(&data->meal_mutex);
	philo->last_meal_time = ft_get_time();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&data->meal_mutex);
	ft_usleep(data, data->time_to_eat);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_lock(&data->meal_mutex);
	if (data->max_meals != -1 && philo->meals_eaten >= data->max_meals)
	{
		pthread_mutex_unlock(&data->meal_mutex);
		return (false);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (true);
}

void	ft_think(t_philo *philo)
{
	t_data	*data;
	time_t	time_to_think;

	data = philo->data;
	pthread_mutex_lock(&data->meal_mutex);
	time_to_think = (data->time_to_die
			- (ft_get_time() - philo->last_meal_time)
			- data->time_to_eat) / 2;
	pthread_mutex_unlock(&data->meal_mutex);
	if (time_to_think < 0)
		time_to_think = 0;
	else if (time_to_think > 200)
		time_to_think = 200;
	ft_print_msg(data, philo, THINKING);
	ft_usleep(data, time_to_think);
}

t_bool	ft_philo_routine(t_data *data, t_philo *philo)
{
	if (!ft_take_forks(data, philo))
		return (false);
	if (!ft_eat(data, philo))
		return (false);
	ft_print_msg(data, philo, SLEEPING);
	ft_usleep(data, data->time_to_sleep);
	ft_think(philo);
	return (true);
}

void	*ft_start_simulation(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	ft_start_delay(data->start_time);
	if (philo->id % 2 == 0)
		ft_usleep(data, 1);
	if (data->max_meals != -1 && philo->meals_eaten >= data->max_meals)
		return (pthread_mutex_unlock(&data->meal_mutex), NULL);
	pthread_mutex_unlock(&data->meal_mutex);
	while (true)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->stop_mutex);
		if (!ft_philo_routine(data, philo))
			break ;
	}
	return (NULL);
}
