/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:00:03 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/25 18:22:32 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_simulate_eating(t_data *data, t_philo *philo)
{
	// Update last meal time
	pthread_mutex_lock(&data->meal_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&data->meal_mutex);

	// Eating
	ft_print_msg(data, philo, "is eating", EAT);
	philo->meals_eaten++;
	ft_usleep(data, data->time_to_eat);
}

void	ft_eat(t_data *data, t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork) == 0)
	{
		if (ft_is_death(data))
		{
			pthread_mutex_unlock(philo->r_fork);
			return ;
			// return (void)pthread_mutex_unlock(philo->r_fork);
		}
		ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);
		if (pthread_mutex_lock(philo->l_fork) == 0)
		{
			if (ft_is_death(data))
			{
				pthread_mutex_unlock(philo->r_fork);
				pthread_mutex_unlock(philo->l_fork);
				return ;
				// return (void)(pthread_mutex_unlock(philo->r_fork)
				// 				, pthread_mutex_unlock(philo->l_fork));
			}
			ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);
			ft_simulate_eating(data, philo);
			ft_usleep(data, 100);
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
		}
		else
			pthread_mutex_unlock(philo->r_fork);
	}
}
