/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:54:14 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/04 16:47:24 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_bool	ft_take_forks(t_data *data, t_philo *philo)
{
	if (sem_wait(data->forks_sem.ptr) != 0)
		return (false);
	ft_print_msg(data, philo, TAKING_FORK);
	if (data->num_of_philos < 2 || sem_wait(data->forks_sem.ptr) != 0)
	{
		sem_post(data->forks_sem.ptr);
		return (false);
	}
	ft_print_msg(data, philo, TAKING_FORK);
	return (true);
}

t_bool	ft_eat(t_data *data, t_philo *philo)
{
	sem_wait(philo->meal_sem.ptr);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten += 1;
	ft_print_msg(data, philo, EATING);
	sem_post(philo->meal_sem.ptr);
	ft_usleep(philo, data->time_to_eat);
	sem_post(data->forks_sem.ptr);
	sem_post(data->forks_sem.ptr);
	// Check max meals condition
	if (data->max_meals != -1 && (philo->meals_eaten >= data->max_meals))
	{
		sem_wait(philo->done_sem.ptr);
		philo->is_done = true;
		sem_post(philo->done_sem.ptr);
		sem_post(data->done_sem.ptr);
		return (false);
	}
	// Check done status ...
	sem_wait(philo->done_sem.ptr);
	if (philo->is_done)
	{
		sem_post(philo->done_sem.ptr);
		return (false) ;
	}
	sem_post(philo->done_sem.ptr);
	return (true);
}

void	ft_think(t_philo *philo)
{
	t_data	*data;
	time_t	time_to_think;

	data = philo->data;
	sem_wait(philo->meal_sem.ptr);
	time_to_think = (data->time_to_die
		- (get_current_time() - philo->last_meal_time)
		- data->time_to_eat) / 2;
	sem_post(philo->meal_sem.ptr);
	if (time_to_think < 0)
		time_to_think = 0;
	else if (time_to_think > 200)
		time_to_think = 200;
	ft_print_msg(data, philo, THINKING);
	ft_usleep(philo, time_to_think);
}

t_bool	ft_philo_routine(t_data *data, t_philo *philo)
{
	if (!ft_take_forks(data, philo))
		return (false);
	if (!ft_eat(data, philo))
		return (false);
	ft_print_msg(data, philo, SLEEPING);
	ft_usleep(philo, data->time_to_sleep);
	ft_think(philo);
	return (true);
}

void	*ft_start_simulation(t_data *data, t_philo *philo)
{
	// printf("Philo: %d ft_start_simulation\n", philo->id);
	ft_start_delay(data->global_start_time);
	if (philo->id % 2 == 0)
		ft_usleep(philo, 1);
	while (true)
	{
		// Execute the routine
		if (!ft_philo_routine(data, philo))
			break ;
	}
	return (NULL);
}
