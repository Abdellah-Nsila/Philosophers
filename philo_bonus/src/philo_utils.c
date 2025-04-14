/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:41:27 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/14 11:27:27 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_wait_thread(pthread_t thr)
{
	if (pthread_join(thr, NULL) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*ft_rand_semname(int id, char *base)
{
	char	*id_str;
	char	*name;

	id_str = ft_itoa(id);
	name = ft_strjoin(base, id_str);
	free(id_str);
	return (name);
}

void	ft_free_sem(t_sem *sem, t_bool is_allocated)
{
	if (!sem)
		return ;
	if (sem->ptr)
	{
		sem_close(sem->ptr);
		if (sem->name)
			sem_unlink(sem->name);
	}
	if (is_allocated && sem->name)
		free(sem->name);
	return ;
}
