/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:44:12 by benpicar          #+#    #+#             */
/*   Updated: 2024/11/28 19:21:23 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_vector	*ft_new_vector(void)
{
	t_vector	*new;

	new = (t_vector *)malloc(sizeof(t_vector));
	if (!new)
		return ((t_vector *) NULL);
	new->buf = (char *)malloc(sizeof(char) * 2);
	if (!(new->buf))
		return (free(new), (t_vector *) NULL);
	new->index = 0;
	new->max_len = 2;
	new->buf[0] = 0;
	new->buf[1] = 0;
	return (new);
}

t_vector	*ft_add_char_vector(char *s, t_vector *vector, size_t len)
{
	char	*dbl;

	if (vector->index + len <= vector->max_len)
	{
		ft_memcpy(&vector->buf[vector->index], s, len);
		vector->index = vector->index + len;
	}
	else
	{
		dbl = (char *)malloc(sizeof(char) * ((vector->max_len * 2) + len));
		if (!(dbl))
			return ((t_vector *) NULL);
		ft_memcpy(dbl, vector->buf, vector->max_len);
		vector->max_len = (vector->max_len * 2) + len;
		free(vector->buf);
		vector->buf = dbl;
		ft_memcpy(&vector->buf[vector->index], s, len);
		vector->index = vector->index + len;
	}
	return (vector);
}

void	ft_free_all(t_buffer **start, t_buffer *tmp, t_buffer *tmp2, \
t_buffer *tmp3)
{
	bool		check;

	check = false;
	tmp3 = *start;
	if (tmp3 == tmp)
		check = true;
	else
		while (tmp3->next != tmp)
			tmp3 = tmp3->next;
	if (tmp != NULL)
	{
		tmp2 = tmp->next;
		free(tmp->vec->buf);
		free(tmp->vec);
		free(tmp);
	}
	tmp = *start;
	if (check)
		*start = tmp2;
	else
	{
		tmp3->next = tmp2;
	}
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest != NULL && src != NULL)
	{
		while (n >= sizeof(long long))
		{
			((long long *)dest)[i] = ((long long *)src)[i];
			i++;
			n = n - sizeof(long long);
		}
		i = i * sizeof(long long);
		while (n > 0)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			n--;
			i++;
		}
	}
	return (dest);
}

ssize_t	ft_memchar(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr = (const unsigned char *)s;

	i = 0;
	if (s != NULL)
	{
		while (i < n)
		{
			if (ptr[i] == (unsigned char)c)
				return (i);
			i++;
		}
	}
	return (-1);
}
