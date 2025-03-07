/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:27:44 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/07 14:59:53 by abnsila          ###   ########.fr       */
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
	if (time_to_think > 400)
		time_to_think = 100;
	if (start == false)
		ft_print_msg(data, philo, "is thinking", THINKING);
	ft_usleep(data, time_to_think);
}

t_bool	ft_philo_routine(t_data *data, t_philo *philo)
{
	//* ---------------------------- Taking Fork 1 ----------------------------
	pthread_mutex_lock(philo->first_fork);
	ft_print_msg(data, philo, "has taken a fork", TAKING_FORK);
	//* ---------------------------- Taking Fork 2 ----------------------------
	pthread_mutex_lock(philo->second_fork);
	ft_print_msg(data, philo, "has taken a fork", TAKING_FORK);
	//* ---------------------------- Eating ----------------------------
	pthread_mutex_lock(&data->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&data->meal_mutex);
	ft_print_msg(data, philo, "is eating", EATING);
	ft_usleep(data, data->time_to_eat);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	//* ---------------------------- Sleeping ----------------------------
	ft_print_msg(data, philo, "is sleeping", SLEEPING);
	ft_usleep(data, data->time_to_sleep);
	//* ---------------------------- Thinking ----------------------------
	ft_think(philo, false);
	return (true);
}

void	*ft_start_simulation(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	
	philo = (t_philo *)arg;
	data = philo->data;
	// philo->born_time = get_current_time();
	while (true)
	{
		ft_philo_routine(data, philo);
	}
	
	return (NULL);
}
