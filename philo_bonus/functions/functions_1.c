/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:03:56 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/14 16:44:24 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(int n)
{
	return (n >= 48 && n <= 57);
}

int	ft_isnumber(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_bzero(void *s, size_t n)
{
	memset(s, 0, n);
}
