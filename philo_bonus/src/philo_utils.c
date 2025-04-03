/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:41:27 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/03 17:41:47 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_wait_thread(pthread_t thr)
{
	if (pthread_join(thr, NULL) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
