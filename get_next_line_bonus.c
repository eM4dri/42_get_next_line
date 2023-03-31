/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 18:55:38 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/31 02:09:46 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define LINE_FOUND 1

static char	*ft_strjoin_free(char *s1, const char *s2)
{
	const size_t	len_s1 = ft_strlen(s1);
	const size_t	len_s2 = ft_strlen(s2);
	char			*join;
	size_t			i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	join = ft_calloc(sizeof(char), len_s1 + len_s2 + 1);
	if (!join)
		return (0);
	i = -1;
	while (s1[++i] != '\0')
		join[i] = s1[i];
	i = -1;
	while (s2[++i] != '\0')
		join[i + len_s1] = s2[i];
	free(s1);
	return (join);
}

static char	*ft_strdup(const char *src)
{
	const size_t	len = ft_strlen(src);
	size_t			i;
	char			*copy;

	copy = ft_calloc(sizeof(char), len + 1);
	if (!copy)
		return (0);
	if (copy != src)
	{
		if (copy < src)
		{
			i = -1;
			while (src[++i] != '\0')
				copy[i] = src[i];
		}
		else
		{
			i = len;
			while (i--)
				copy[i] = src[i];
		}
	}
	return (copy);
}

static char	*ft_substr_ini(char const *s, size_t len)
{
	char			*out;
	size_t			i;

	if (!s)
		return (NULL);
	i = 0;
	out = ft_calloc(sizeof(char), (len + 1));
	if (!out)
		return (0);
	while (i < len)
	{
		out[i] = s[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

static int	get_next_line2(int readable, char **s, char **line)
{
	char	*strchr_n;
	char	*str_aux;

	if (readable < 0)
		return (-1);
	else if (readable == 0 && !*s)
		return (0);
	strchr_n = ft_strchr(*s, '\n');
	if (strchr_n)
	{
		*line = ft_substr_ini(*s, strchr_n - *s);
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
	int			i;

	if (BUFFER_SIZE < 1 || !line || fd < 0 || fd > FD_SETSIZE)
		return (-1);
	if (s[fd] != NULL && ft_strchr(s[fd], '\n'))
		return (get_next_line2(LINE_FOUND, &s[fd], line));
	buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	readable = read(fd, buff, BUFFER_SIZE);
	i = 0;
	while (readable >= 0)
	{
		buff[readable] = '\0';
		if (!s[fd])
			s[fd] = ft_strdup(buff);
		else
			s[fd] = ft_strjoin_free(s[fd], buff);
		if (ft_strchr(&s[fd][BUFFER_SIZE * i++], '\n') || readable < BUFFER_SIZE)
			break ;
		readable = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (get_next_line2(readable, &s[fd], line));
}
