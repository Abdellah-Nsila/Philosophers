/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:27:44 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/09 15:53:00 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	else if (time_to_think > 400)
		time_to_think = 100;
	if (start == false)
		ft_print_msg(data, philo, THINKING);
	ft_usleep(data, time_to_think);
}

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
	pthread_mutex_lock(&data->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&data->meal_mutex);
	ft_print_msg(data, philo, EATING);
	ft_usleep(data, data->time_to_eat);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return (true);
}

t_bool	ft_philo_routine(t_data *data, t_philo *philo)
{
	if (!ft_take_forks(data, philo))
		return (false);
	
	if (!ft_eat(data, philo))
		return (false);
	
	ft_print_msg(data, philo, SLEEPING);
	ft_usleep(data, data->time_to_sleep);
	
	ft_think(philo, false);
	
	return (true);
}

void	*ft_start_simulation(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_data  *data = philo->data;

	ft_start_delay(data->start_time);
	if (philo->id % 2 == 0)
		ft_think(philo, true);
	while (!ft_stop_simulation(data))
	{
		if (!ft_philo_routine(data, philo))
			break;
	}
	return (NULL);
}
