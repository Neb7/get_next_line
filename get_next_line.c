/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:32:41 by benpicar          #+#    #+#             */
/*   Updated: 2024/11/28 19:21:43 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buffer	*buffer = NULL;
	t_buffer		*actual;
	char			*d;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	d = NULL;
	if (!buffer)
		buffer = ft_new_struct(fd);
	if (!buffer)
		return (ft_free_all(&buffer, buffer, NULL, NULL), free(d), NULL);
	actual = ft_actual_fd(&buffer, fd);
	if (!actual)
		return (ft_free_all(&buffer, actual, NULL, NULL), free(d), NULL);
	if (!(ft_gnl_read(actual, &d, ft_memchar(actual->vec->buf, '\n', \
	actual->vec->index))))
		return (ft_free_all(&buffer, actual, NULL, NULL), free(d), NULL);
	if (actual->end)
		ft_free_all(&buffer, actual, NULL, NULL);
	return (d);
}

char	*ft_gnl_read(t_buffer *actual, char **d, ssize_t idx_nl)
{
	int		readed;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	readed = read(actual->fd, buf, BUFFER_SIZE);
	if (readed < 0)
		return (free(buf), NULL);
	while (readed > 0)
	{
		if (!ft_add_char_vector(buf, actual->vec, readed))
			return (free(buf), NULL);
		idx_nl = ft_memchar(actual->vec->buf, '\n', actual->vec->index);
		if (idx_nl != -1)
			break ;
		readed = read(actual->fd, buf, BUFFER_SIZE);
	}
	if (readed == 0 && idx_nl < 0)
		actual->end = true;
	free(buf);
	if (idx_nl != -1)
		return (ft_gnl_dest(d, actual->vec->buf, idx_nl, actual));
	else
		return (ft_gnl_dest(d, actual->vec->buf, actual->vec->index, actual));
}

char	*ft_gnl_dest(char **d, char *buf, ssize_t idx, t_buffer *actual)
{
	if ((size_t)idx != actual->vec->index)
	{
		d[0] = (char *)malloc(sizeof(char) * (idx + 2));
		if (!(d[0]))
			return (NULL);
		ft_memcpy(d[0], buf, idx + 1);
		d[0][idx + 1] = 0;
		ft_memcpy(buf, &buf[idx + 1], (actual->vec->index - (idx + 1)));
		actual->vec->index = actual->vec->index - (idx + 1);
		return (d[0]);
	}
	else if (actual->vec->index > 0)
	{
		d[0] = (char *)malloc(sizeof(char) * (idx + 1));
		if (!(d[0]))
			return (NULL);
		ft_memcpy(d[0], buf, idx);
		d[0][idx] = 0;
		actual->vec->index = 0;
		return (d[0]);
	}
	return (NULL);
}

t_buffer	*ft_actual_fd(t_buffer **start, int fd)
{
	t_buffer	*tmp;

	tmp = *start;
	if (tmp->fd == fd)
		return (tmp);
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->fd == fd)
			return (tmp);
	}
	tmp->next = ft_new_struct(fd);
	return (tmp->next);
}

t_buffer	*ft_new_struct(int fd)
{
	t_buffer	*new;

	new = (t_buffer *)malloc(sizeof(t_buffer) * 1);
	if (!new)
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	new->vec = ft_new_vector();
	if (!new->vec)
		return (free(new), NULL);
	new->end = false;
	return (new);
}
