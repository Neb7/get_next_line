/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:01:06 by benpicar          #+#    #+#             */
/*   Updated: 2024/10/28 12:24:12 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*d;
	ssize_t		l;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	d = NULL;
	if (gnl_strchar(buffer, '\n') < 0)
	{
		buffer = gnl_suite(buffer, fd, &l);
		if (l != BUFFER_SIZE && gnl_strchar(buffer, '\n') < 0)
			d = gnl_substr(buffer, 0, gnl_strlen(buffer));
	}
	if (!buffer)
		return (NULL);
	if (!d && gnl_strchar(buffer, '\n') != -1)
		d = gnl_substr(buffer, 0, (gnl_strchar(buffer, '\n') + 1));
	if (!d && gnl_strchar(buffer, '\n') != -1)
		return (gnl_moinslbuffer(buffer, gnl_strlen(buffer)));
	if (d)
	{
		buffer = gnl_moinslbuffer(buffer, gnl_strlen(d));
		return (d);
	}
	return (get_next_line(fd));
}

char	*gnl_moinslbuffer(char *buffer, size_t t)
{
	char	*p;

	if (t == (gnl_strlen(buffer)))
	{
		free(buffer);
		return (NULL);
	}
	p = gnl_substr(buffer, t, (gnl_strlen(buffer) - t));
	free(buffer);
	return (p);
}

char	*gnl_mettrea0(void)
{
	char	*d;

	d = ((char *)malloc(sizeof(char)));
	if (!d)
		return (NULL);
	d[0] = 0;
	return (d);
}

char	*gnl_substr(char *s, unsigned int start, size_t len)
{
	char	*d;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= gnl_strlen(s))
	{
		d = gnl_mettrea0();
		if (!d)
			return (NULL);
	}
	else
	{
		i = gnl_strlen(&s[start]);
		if ((i > len))
			i = len;
		d = (char *)malloc(sizeof(char) * (i + 1));
		if (!d)
			return (NULL);
		d[i] = 0;
		while (i-- > 0)
			d[i] = s[start + i];
	}
	return (d);
}

char	*gnl_suite(char *buffer, int fd, ssize_t *l)
{
	char	*buf;
	char	*p;
	size_t	len_buf;

	p = gnl_read(fd, l);
	if (!p)
		return (gnl_free_buffer(buffer));
	if (!p[0] && *l != BUFFER_SIZE && !buffer)
	{
		free(p);
		return (NULL);
	}
	if (!buffer)
		return (p);
	len_buf = gnl_strlen(buffer) + gnl_strlen(p);
	buf = ((char *)malloc(sizeof(char) * (len_buf + 1)));
	if (!buf)
		return (NULL);
	buf = gnl_strcpycat(buf, buffer, p);
	free(buffer);
	free(p);
	return (buf);
}
