/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:21:38 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/14 16:44:31 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef enum s_bool
{
	false,
	true,
}	t_bool;

void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strdup(const char *s1);
int		ft_isdigit(int n);
int		ft_isnumber(char *str);
int		ft_handle_max_case(int sign);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
t_bool	ft_strlcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_write(long time, int id, const char *msg);

#endif 
