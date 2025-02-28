/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:00:03 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/28 11:21:57 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_simulate_eating(t_data *data, t_philo *philo)
{
	ft_print_msg(data, philo, "is eating", EAT);
	pthread_mutex_lock(&data->meal_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&data->meal_mutex);
	ft_usleep(data, data->time_to_eat);
	if (ft_is_death(data))
		return ;
	philo->meals_eaten++;
}

void ft_eat(t_data *data, t_philo *philo)
{
	// ---------------------------- Take First Fork ----------------------------
	pthread_mutex_lock(philo->first_fork);
	if (ft_is_death(data))
	{
		pthread_mutex_unlock(philo->first_fork);
		return;
	}
	ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);
	// --------------------------- Take Second Fork ----------------------------
	if (data->num_of_philos > 1)
	{
		pthread_mutex_lock(philo->second_fork);
		if (ft_is_death(data))
		{
			pthread_mutex_unlock(philo->second_fork);
			pthread_mutex_unlock(philo->first_fork);
			return;
		}
		ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);
		// --------------------------- Simulate eating ----------------------------
		ft_print_msg(data, philo, "is eating", EAT);
		pthread_mutex_lock(&data->meal_mutex);
		philo->last_meal_time = get_current_time();
		philo->meals_eaten++;
		pthread_mutex_unlock(&data->meal_mutex);
		ft_usleep(data, data->time_to_eat);
		// ft_simulate_eating(data, philo);
		pthread_mutex_unlock(philo->second_fork);
	}
	pthread_mutex_unlock(philo->first_fork);
}
