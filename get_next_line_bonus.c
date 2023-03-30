/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 18:55:38 by emadriga          #+#    #+#             */
/*   Updated: 2021/06/25 23:35:42 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define LINE_FOUND 1

static char	*ft_strjoin_free(char *s1, char const *s2)
{
	const size_t	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	char			*join;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	join = ft_calloc(sizeof(char), len);
	if (!join)
		return (0);
	ft_strlcat(join, s1, len);
	ft_strlcat(join, s2, len);
	free(s1);
	return (join);
}

static char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	len_s1;

	len_s1 = ft_strlen(s1) + 1;
	copy = ft_calloc(sizeof(char), len_s1);
	if (!copy)
		return (0);
	ft_memmove(copy, s1, len_s1);
	return (copy);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	const size_t	len_s = ft_strlen(s);
	char			*out;
	size_t			i;

	if (!s)
		return (NULL);
	if (len_s <= (size_t)start)
		return (ft_strdup(""));
	i = 0;
	if (len_s < len)
		len = len_s - start;
	out = ft_calloc(sizeof(char), (len + 1));
	if (!out)
		return (0);
	while (s[start + i] != '\0' && i < len)
	{
		out[i] = s[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

static int	get_next_line2(int readable, char **s, char **line)
{
	const char	*strchr_n = ft_strchr(*s, '\n');
	char		*str_aux;

	if (readable < 0)
		return (-1);
	else if (readable == 0 && !*s)
		return (0);
	if (strchr_n)
	{
		*line = ft_substr(*s, 0, strchr_n - *s);
		str_aux = ft_strdup(strchr_n + 1);
		free(*s);
		*s = str_aux;
		return (1);
	}
	*line = ft_strdup(*s);
	free(*s);
	*s = NULL;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*s[FD_SETSIZE];
	char		*buff;
	int			readable;

	if (BUFFER_SIZE < 1 || !line || fd < 0 || fd > FD_SETSIZE)
		return (-1);
	if (s[fd] != NULL && ft_strchr(s[fd], '\n'))
		return (get_next_line2(LINE_FOUND, &s[fd], line));
	buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	readable = read(fd, buff, BUFFER_SIZE);
	while (readable >= 0)
	{
		if (!s[fd])
			s[fd] = ft_strdup(buff);
		else
			s[fd] = ft_strjoin_free(s[fd], buff);
		if (ft_strchr(s[fd], '\n') || readable < BUFFER_SIZE)
			break ;
		readable = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (get_next_line2(readable, &s[fd], line));
}
