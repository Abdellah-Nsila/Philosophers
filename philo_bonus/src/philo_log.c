/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:33:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/14 11:29:03 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void ft_colored_msg(time_t timestamp, int id, int type)
{
	if (type == TAKING_FORK)
		ft_colored_write(BWHT, timestamp, id, "has taken a fork", RESET);
	else if (type == THINKING)
		ft_colored_write(BBLU, timestamp, id, "is thinking", RESET);
	else if (type == EATING)
		ft_colored_write(BGRN, timestamp, id, "is eating", RESET);
	else if (type == SLEEPING)
		ft_colored_write(BMAG, timestamp, id, "is sleeping", RESET);
	else if (type == DIED)
		ft_colored_write(BRED, timestamp, id, "died", RESET);
}

void	ft_format_msg(time_t timestamp, int id, int type)
{
	if (type == TAKING_FORK)
		ft_write(timestamp, id, "has taken a fork");
	else if (type == THINKING)
		ft_write(timestamp, id, "is thinking");
	else if (type == EATING)
		ft_write(timestamp, id, "is eating");
	else if (type == SLEEPING)
		ft_write(timestamp, id, "is sleeping");
	else if (type == DIED)
		ft_write(timestamp, id, "died");
}

void	ft_print_msg(t_data *data, t_philo *philo, int type)
{
	time_t	timestamp;

	sem_wait(philo->done_sem.ptr);
	if (philo->is_done)
	{
		sem_post(philo->done_sem.ptr);
		return ;
	}
	sem_post(philo->done_sem.ptr);
	sem_wait(data->print_sem.ptr);
	timestamp = ft_get_time() - data->global_start_time;
	//* My own format
	ft_colored_msg(timestamp, philo->id, type);
	//* The mandatory format
	// ft_format_msg(timestamp, philo->id, type);
	sem_post(data->print_sem.ptr);
}
