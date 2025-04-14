/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:47:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/14 15:35:47 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_launch_died_signal(t_data *data, t_philo *philo)
{
	int		i;
	time_t	timestamp;

	sem_wait(data->signal_sem.ptr);
	sem_post(data->died_sem.ptr);
	sem_wait(philo->done_sem.ptr);
	if (philo->is_done)
	{
		sem_post(philo->done_sem.ptr);
		sem_post(data->signal_sem.ptr);
		return ;
	}
	philo->is_done = true;
	sem_post(philo->done_sem.ptr);
	i = -1;
	while (++i < data->num_of_philos)
		sem_wait(data->emmiter_sem.ptr);
	sem_wait(data->print_sem.ptr);
	timestamp = ft_get_time() - data->global_start_time;
	ft_format_msg(timestamp, philo->id, DIED);
	sem_post(data->print_sem.ptr);
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
		usleep(1000);
		sem_wait(philo->done_sem.ptr);
		if (philo->is_done)
		{
			sem_post(philo->done_sem.ptr);
			break ;
		}
		sem_post(philo->done_sem.ptr);
		sem_wait(philo->meal_sem.ptr);
		if ((ft_get_time() - philo->last_meal_time) > data->time_to_die)
		{
			sem_post(philo->meal_sem.ptr);
			return (ft_launch_died_signal(data, philo), NULL);
		}
		sem_post(philo->meal_sem.ptr);
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
	sem_post(data->died_sem.ptr);
	sem_wait(philo->done_sem.ptr);
	philo->is_done = true;
	sem_post(philo->done_sem.ptr);
	sem_post(data->emmiter_sem.ptr);
	sem_post(data->done_sem.ptr);
	return (NULL);
}
