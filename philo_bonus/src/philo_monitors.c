/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:47:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/05 17:19:46 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_launch_died_signal(t_data *data, t_philo *philo)
{
	int		i;
	time_t	timestamp;

	// Begin the signal process
	sem_wait(data->signal_sem.ptr);
	
	// Enable the global died semaphore
	sem_wait(philo->done_sem.ptr);
	sem_post(data->died_sem.ptr);
	
	// Enable the current died flag
	if (philo->is_done)
	{
		sem_post(philo->done_sem.ptr);
		return ;
	}
	philo->is_done = true;
	sem_post(philo->done_sem.ptr);

	// Wait until all philos stop
	i = 0;
	while (i < data->num_of_philos)
	{
		sem_wait(data->emmiter_sem.ptr);
		i++;
	}

	// Print died log msg
	sem_wait(data->print_sem.ptr);
	timestamp = get_current_time() - data->global_start_time;
	ft_colored_msg(timestamp, philo->id, DIED);
	sem_post(data->print_sem.ptr);
	
	// End of signal process
	sem_post(data->signal_sem.ptr);
	return ;
}

void	*ft_self_monitor(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	
	philo = (t_philo *)arg;
	data = philo->data;
	ft_start_delay(data->global_start_time);
	while (true)
	{
		usleep(500);
		
		// Check Die condition
		sem_wait(philo->meal_sem.ptr);
		if ((get_current_time() - philo->last_meal_time) > data->time_to_die)
		{
			sem_post(philo->meal_sem.ptr);
			ft_launch_died_signal(data, philo);
			break ;
		}
		sem_post(philo->meal_sem.ptr);

				// Check done flag
		sem_wait(philo->done_sem.ptr);
		if (philo->is_done)
		{
			sem_post(philo->done_sem.ptr);
			break ;
		}
		sem_post(philo->done_sem.ptr);
	}
	return (NULL);
}

void	*ft_global_monitor(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	sem_wait(data->died_sem.ptr);
	// printf("%sDeath Detected\n%s", BRED, RESET);
	sem_post(data->died_sem.ptr);

	sem_wait(philo->done_sem.ptr);
	philo->is_done = true;
	sem_post(philo->done_sem.ptr);
	sem_post(data->emmiter_sem.ptr);
	sem_post(data->done_sem.ptr);

	return (NULL);
}
