/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:45:07 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/20 14:29:31 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "functions.h"
# include "colors.h"
# include <math.h>
# include <time.h>
# include <sys/wait.h>
# include <pthread.h>

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
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				fuel;
	int				*arr;
	int				score;
	pthread_mutex_t	mutex_arr[4];
	pthread_cond_t	cond_arr[4];
	int				stove[4];
}				t_philo;

#endif 