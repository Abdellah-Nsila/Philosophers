/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:54:14 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/27 14:13:27 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_init_philo(t_data *data, t_philo *philo)
{
	philo->meals_eaten = 0;
	philo->stop_flag = false;
	philo->data = data;
	sem_init(&philo->meal_sem, 0, 1);
	sem_init(&philo->stop_sem, 0, 1);
}

void	ft_launch_threads(t_data *data, t_philo *philo)
{
	ft_init_philo(data, philo);
	philo->last_meal_time = data->global_start_time;
	
	// Routine Thread
	if (pthread_create(&(philo->routine_thread), NULL, &ft_start_simulation, philo) != 0)
		ft_exit_process(data, philo, EXIT_FAILURE);
	
	// Monitor Thread
	if (pthread_create(&(philo->monitor_thread), NULL, &ft_philo_monitor, philo) != 0)
		ft_exit_process(data, philo, EXIT_FAILURE);
	
	
	if (pthread_join(philo->routine_thread, NULL) != 0)
		ft_exit_process(data, philo, EXIT_FAILURE);
		
	if (pthread_join(philo->monitor_thread, NULL) != 0)
		ft_exit_process(data, philo, EXIT_FAILURE);
		
	ft_exit_process(data, philo, philo->exit_code);
}
