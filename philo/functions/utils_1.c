/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:03:56 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/15 15:16:36 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
		ptr[i++] = (unsigned char)c;
	return (b);
}

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	src_len;

	src_len = ft_strlen(s1) + 1;
	dst = (char *) malloc(src_len);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, src_len);
	return (dst);
}
