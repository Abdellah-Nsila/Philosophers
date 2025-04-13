/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:33:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/13 20:01:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void ft_write(const char *color, long time, int id, const char *msg, const char *reset)
{
    // Write color
    write(1, color, ft_strlen(color));
    
    // Write timestamp
    ft_putnbr(time);
    write(1, " ", 1);
    
    // Write philosopher ID
    ft_putnbr(id);
    write(1, " ", 1);
    
    // Write message
    write(1, msg, ft_strlen(msg));
    
    // Write newline and reset color
    write(1, "\n", 1);
    write(1, reset, ft_strlen(reset));
}

void ft_colored_msg(time_t timestamp, int id, int type)
{
    if (type == TAKING_FORK)
        ft_write(BWHT, timestamp, id, "has taken a fork", RESET);
    else if (type == THINKING)
        ft_write(BBLU, timestamp, id, "is thinking", RESET);
    else if (type == EATING)
        ft_write(BGRN, timestamp, id, "is eating", RESET);
    else if (type == SLEEPING)
        ft_write(BMAG, timestamp, id, "is sleeping", RESET);
    else if (type == DIED)
        ft_write(BRED, timestamp, id, "died", RESET);
}






// void	ft_colored_msg(time_t timestamp, int id, int type)
// {
// 	char	*format;

// 	format = "%s%ld %d %s\n%s";
// 	if (type == TAKING_FORK)
// 		printf(format, BWHT, timestamp, id, "has taken a fork", RESET);
// 	else if (type == THINKING)
// 		printf(format, BBLU, timestamp, id, "is thinking", RESET);
// 	else if (type == EATING)
// 		printf(format, BGRN, timestamp, id, "is eating", RESET);
// 	else if (type == SLEEPING)
// 		printf(format, BMAG, timestamp, id, "is sleeping", RESET);
// 	else if (type == DIED)
// 		printf(format, BRED, timestamp, id, "died", RESET);
// 	fflush(stdout);
// }

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
