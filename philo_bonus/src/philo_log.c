/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:33:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/13 16:34:26 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_colored_msg(time_t timestamp, int id, int type)
{
	char	*format;

	format = "%s%ld %d %s\n%s";
	if (type == TAKING_FORK)
		printf(format, BWHT, timestamp, id, "has taken a fork", RESET);
	else if (type == THINKING)
		printf(format, BBLU, timestamp, id, "is thinking", RESET);
	else if (type == EATING)
		printf(format, BGRN, timestamp, id, "is eating", RESET);
	else if (type == SLEEPING)
		printf(format, BMAG, timestamp, id, "is sleeping", RESET);
	else if (type == DIED)
		printf(format, BRED, timestamp, id, "died", RESET);
}

void	ft_format_msg(time_t timestamp, int id, int type)
{
	char	*format;

	format = "%ld %d %s\n";
	if (type == TAKING_FORK)
		printf(format, timestamp, id, "has taken a fork");
	else if (type == THINKING)
		printf(format, timestamp, id, "is thinking");
	else if (type == EATING)
		printf(format, timestamp, id, "is eating");
	else if (type == SLEEPING)
		printf(format, timestamp, id, "is sleeping");
	else if (type == DIED)
		printf(format, timestamp, id, "died");
}

void	ft_print_msg(t_data *data, t_philo *philo, int type)
{
	time_t	timestamp;
	(void)philo;
	
	// Check Done flag
	sem_wait(philo->done_sem.ptr);
	if (philo->is_done)
	{
		sem_post(philo->done_sem.ptr);
		return ;
	}
	sem_post(philo->done_sem.ptr);

	// Log
	// sem_wait(data->cond_sem.ptr);
	sem_wait(data->print_sem.ptr);
	timestamp = get_current_time() - data->global_start_time;
	//* My own format
	ft_colored_msg(timestamp, philo->id, type);
	//? printf("%ld Status is %d\n",timestamp, type);
	//* The mandatory format
	// ft_format_msg(timestamp, philo->id, type);
	sem_post(data->print_sem.ptr);
	// sem_post(data->cond_sem.ptr);
}
