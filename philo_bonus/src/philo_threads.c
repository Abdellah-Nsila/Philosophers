/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:46:13 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/03 13:45:04 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_launch_died_signal(t_data *data, t_philo *philo)
{
	time_t	timestamp;

	// Begin the signal process
	sem_wait(&data->signal_sem.ptr);
	// Enable the global died semaphore
	sem_wait(&philo->done_sem.ptr);
	sem_post(&data->died_sem.ptr);
	// Enable the current died flag
	if (philo->is_done)
	{
		sem_post(&philo->done_sem.ptr);
		return ;
	}
	sem_post(&philo->done_sem.ptr);
	philo->is_done = true;

	sem_wait(&data->print_sem);
	timestamp = get_current_time() - data->global_start_time;
	ft_colored_msg(timestamp, philo->id, DIED);
	sem_post(&data->print_sem);
	
	sem_post(&data->signal_sem);
	return (NULL);
}

void	ft_self_monitor(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	
	philo = (t_philo *)arg;
	data = philo->data;
	while (true)
	{
		// Check done flag
		sem_wait(&philo->done_sem.ptr);
		if (philo->is_done)
		{
			sem_post(&philo->done_sem.ptr);
			break ;
		}
		sem_post(&philo->done_sem.ptr);
		
		// Check Die condition
		sem_wait(&philo->meal_sem.ptr);
		if ((get_current_time() - philo->last_meal_time) > data->time_to_die)
		{
			sem_post(&philo->meal_sem.ptr);
			ft_launch_died_signal(data, philo);
			break ;
		}
		sem_post(&philo->meal_sem.ptr);
	}
	return (NULL);
}

void	ft_global_monitor(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	sem_wait(&data->died_sem.ptr);
	sem_post(&data->died_sem.ptr);

	sem_wait(&philo->done_sem.ptr);
	philo->is_done = true;
	sem_post(&philo->done_sem.ptr);

	return (NULL);
}

int	ft_philo_init(int id, t_data *data, t_philo *philo)
{
	philo->id = id;
	philo->data = data;
	ft_create_sem(&data->done_sem, 1);
	ft_create_sem(&data->died_sem, 1);

	philo->last_meal_time = data->global_start_time;
	if (pthread_create(&(philo->self_monitor), NULL, &ft_self_monitor, philo))
		return (EXIT_FAILURE);
	if (pthread_create(&(philo->global_monitor), NULL, &ft_global_monitor, philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
