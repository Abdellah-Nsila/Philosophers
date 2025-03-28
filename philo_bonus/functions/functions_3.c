/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:17:12 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/28 17:17:34 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_storeint(char *ptr, unsigned int n, int index, int sign)
{
	if (index >= sign)
	{
		if (n > 9)
			ft_storeint(ptr, (n / 10), (index - 1), sign);
		ptr[index] = (n % 10) + 48;
	}
}

static int	ft_getlen(unsigned int n)
{
	if (n > 9)
		return (1 + ft_getlen(n / 10));
	return (1);
}

char	*ft_itoa(int n)
{
	unsigned int		number;
	size_t				len;
	int					sign;
	char				*ptr;

	number = n;
	len = 0;
	sign = 0;
	if (n < 0)
	{
		number = -n;
		sign = 1;
	}
	len = sign + ft_getlen(number);
	ptr = (char *) malloc(((len + 1) * sizeof(char)));
	if (!ptr)
		return (NULL);
	ft_storeint(ptr, number, len - 1, sign);
	if (sign)
		ptr[0] = '-';
	ptr[len] = '\0';
	return (ptr);
}
