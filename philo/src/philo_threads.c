/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:40:11 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/05 14:56:55 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO See this repo https://github.com/mcombeau/philosophers/blob/main/philo/sources/philosopher.c

#include "../includes/philo.h"

// meal -> stop -> print

void	sim_start_delay(time_t start_time)
{
	while (get_current_time() < start_time)
		continue ;
}

void	ft_signle_philo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->first_fork);
	ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);
	ft_usleep(data, data->time_to_die);
	pthread_mutex_unlock(philo->first_fork);
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

t_bool	ft_philo_routine(t_data *data, t_philo *philo)
{
	if (ft_stop_simulation(data))
		return (false);
	//* ---------------------------- Taking Fork 1 ----------------------------
	pthread_mutex_lock(philo->first_fork);
	ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);
	//* ---------------------------- Taking Fork 2 ----------------------------
	pthread_mutex_lock(philo->second_fork);
	ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);
	//* ---------------------------- Eating ----------------------------
	pthread_mutex_lock(&data->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&data->meal_mutex);
	ft_print_msg(data, philo, "is eating", EAT);
	ft_usleep(data, data->time_to_eat);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	//* ---------------------------- Sleeping ----------------------------
	ft_print_msg(data, philo, "is sleeping", SLEEP);
	ft_usleep(data, data->time_to_sleep);
	//* ---------------------------- Thinking ----------------------------
	ft_think(philo, false);
	return (true);
}

void	*ft_start_simulation(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_data	*data = philo->data;
	
	sim_start_delay(data->start_time);
	if (philo->id % 2 == 0)
		ft_think(philo, true);
	if (data->num_of_philos == 1)
		return (ft_signle_philo(philo), NULL);
	while (1)
	{
		if (ft_philo_routine(data, philo) == false)
			break ;
		if (ft_stop_simulation(data))
			break ;
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
