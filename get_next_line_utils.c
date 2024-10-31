/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:01:38 by benpicar          #+#    #+#             */
/*   Updated: 2024/10/28 12:24:36 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strcpycat(char *dest, char *src, char *src2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (src2[j] != '\0')
	{
		dest[i] = src2[j];
		i++;
		j++;
	}
	dest[i] = 0;
	return (dest);
}

char	*gnl_read(int fd, ssize_t *l)
{
	char	*p;
	ssize_t	n;

	p = ((char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)));
	if (! p)
		return (NULL);
	n = read(fd, p, BUFFER_SIZE);
	*l = n;
	if (n < 0)
	{
		free(p);
		return (NULL);
	}
	p[n] = 0;
	return (p);
}

size_t	gnl_strlen(char *str)
{
	size_t	i;

	if (! str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

ssize_t	gnl_strchar(char *str, int c)
{
	ssize_t	i;

	if (! str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if (c == 0)
		return (i);
	return (-1);
}

char	*gnl_free_buffer(char *buffer)
{
	if (buffer)
		free(buffer);
	return (NULL);
}
