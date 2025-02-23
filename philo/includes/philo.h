/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:45:07 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/23 11:56:27 by abnsila          ###   ########.fr       */
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

# ifndef LONG_MAX
#  define LONG_MAX 9223372036854775807
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
	pthread_t		thread;
	int				id;
	int				meals_eaten;
    size_t			last_meal_time;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				num_of_philos;  // Total philosophers
	int				max_meals;      // Optional: meals per philosopher
	size_t			time_to_die;    // Max time without eating (ms)
	size_t			time_to_eat;    // Eating duration (ms)
	size_t			time_to_sleep;  // Sleeping duration (ms)
	size_t			start_time;     // Simulation start timestamp
	pthread_mutex_t	*forks_mutex;   // Array of mutexes (forks)
	pthread_mutex_t	print_mutex;    // Protect logging
	pthread_mutex_t	death_mutex;    // Protect death flag
	int				someone_died;   // Global death flag
}				t_data;

#endif
