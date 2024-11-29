/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:33:32 by benpicar          #+#    #+#             */
/*   Updated: 2024/11/28 16:36:23 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_vector
{
	char	*buf;
	size_t	index;
	size_t	max_len;
}	t_vector;

typedef struct s_buffer
{
	t_vector		*vec;
	int				fd;
	struct s_buffer	*next;
	bool			end;
}	t_buffer;

/*Get_next_line*/

char		*get_next_line(int fd);
char		*ft_gnl_read(t_buffer *actual, char **d, ssize_t idx_nl);
char		*ft_gnl_dest(char **d, char *buf, ssize_t idx, t_buffer \
*actual);
t_buffer	*ft_actual_fd(t_buffer **start, int fd);
t_buffer	*ft_new_struct(int fd);

/*Get_next_line_utils*/

t_vector	*ft_new_vector(void);
t_vector	*ft_add_char_vector(char *s, t_vector *vector, size_t len);
void		ft_free_all(t_buffer **start, t_buffer *tmp, t_buffer *tmp2, \
t_buffer *tmp3);
void		*ft_memcpy(void *dest, const void *src, size_t n);
ssize_t		ft_memchar(const void *s, int c, size_t n);

#endif