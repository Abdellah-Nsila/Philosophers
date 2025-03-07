/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:40:11 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/07 14:02:45 by abnsila          ###   ########.fr       */
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
	ft_print_msg(data, philo, "has taken a fork", TAKING_FORK);
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
		ft_print_msg(data, philo, "is thinking", THINKING);
	ft_usleep(data, time_to_think);
}

// void ft_think(t_philo *philo, t_bool start)
// {
//     t_data *data = philo->data;
//     time_t current = get_current_time();
//     time_t elapsed;
//     time_t remaining;
//     time_t baseline;
//     time_t time_to_think;
//     const time_t adjust = 2;  // adjustment in ms per extra philosopher

//     // Lock meal_mutex while reading last_meal_time
//     pthread_mutex_lock(&data->meal_mutex);
//     elapsed = current - philo->last_meal_time;
//     pthread_mutex_unlock(&data->meal_mutex);

//     // Calculate how much time remains until the philosopher would starve.
//     remaining = (data->time_to_die > elapsed) ? (data->time_to_die - elapsed) : 0;
//     // The baseline is the time needed for eating and sleeping.
//     baseline = data->time_to_eat + data->time_to_sleep;

//     // If we have extra time beyond the baseline, take half as thinking time,
//     // and subtract an adjustment based on the number of philosophers.
//     if (remaining > baseline)
//         time_to_think = (remaining - baseline) / 2 - ((data->num_of_philos - 1) * adjust);
//     else
//         time_to_think = 0;

//     // Clamp negative values to 0.
//     if (time_to_think < 0)
//         time_to_think = 0;
//     // If starting and no thinking time computed, give a minimal delay.
//     if (time_to_think == 0 && start)
//         time_to_think = 1;
//     // Optionally, cap the thinking time to avoid overly long pauses.
//     if (time_to_think > 100)
//         time_to_think = 100;

//     // Print the "is thinking" message if this is not the starting phase.
//     if (!start)
//         ft_print_msg(data, philo, "is thinking", THINKING);
    
//     ft_usleep(data, time_to_think);
// }


t_bool	ft_philo_routine(t_data *data, t_philo *philo)
{
	// if (ft_stop_simulation(data))
	// 	return (false);
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
				return (ft_destroy(data));
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
