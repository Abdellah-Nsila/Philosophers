/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:45:07 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/21 16:52:14 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "functions.h"
# include "colors.h"
# include <math.h>
# include <time.h>
#include <sys/time.h>
# include <pthread.h>

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

# ifndef INT_MIN
#  define INT_MIN -2147483648
# endif

// typedef struct s_philo
// {
// 	pthread_mutex_t	mutex;
// 	pthread_cond_t	cond;
// 	int				fuel;
// 	int				*arr;
// 	int				score;
// 	pthread_mutex_t	mutex_arr[4];
// 	pthread_cond_t	cond_arr[4];
// 	int				stove[4];
// }				t_philo;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	
}				t_philo;

typedef struct s_data
{
	t_philo		*philos;
	size_t		death_time;
	size_t		eat_time;
	size_t		sleep_time;
	size_t		start_time;
}				t_data;

#endif 