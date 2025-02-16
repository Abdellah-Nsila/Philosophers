/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:45:07 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/16 14:59:41 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "functions.h"
# include <math.h>
# include <time.h>
# include <sys/wait.h>
# include <pthread.h>

# define THREADS 2

typedef struct s_philo
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				fuel;
	int				*arr;
	int				score;
}				t_philo;

#endif 