/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:45:07 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/15 15:49:00 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "functions.h"
# include <time.h>
# include <sys/wait.h>
# include <pthread.h>

# define THREADS 10

typedef struct s_philo
{
	pthread_mutex_t	mutex;
	int				*i;
	int				score;
}				t_philo;

#endif 