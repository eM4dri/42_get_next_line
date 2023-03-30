/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 18:51:46 by emadriga          #+#    #+#             */
/*   Updated: 2021/06/19 15:57:40 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

// size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
// {
// 	size_t			i;
// 	const size_t	dst_len = ft_strlen(dst);
// 	const size_t	src_len = ft_strlen(src);

// 	if (dst_len < dstsize)
// 	{
// 		i = 0;
// 		while (i < dstsize - dst_len - 1 && src[i] != '\0')
// 		{
// 			dst[dst_len + i] = src[i];
// 			i++;
// 		}
// 		dst[dst_len + i] = '\0';
// 	}
// 	if (dstsize <= dst_len)
// 		return (src_len + dstsize);
// 	return (src_len + dst_len);
// }

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*mem;
	unsigned char	*out;

	if (dst != src)
	{
		if (dst < src)
		{
			mem = (unsigned char *)src;
			out = (unsigned char *)dst;
			while (len-- > 0)
				*out++ = *mem++;
		}
		else
		{
			mem = (unsigned char *)src + len - 1;
			out = dst + len - 1;
			while (len--)
				*out-- = *mem--;
		}
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	char	*mem;

	mem = (char *)s;
	while (*mem > 0)
	{
		if (*mem == (char)c)
			return (mem);
		mem++;
	}
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*out;
	char	*mem;
	size_t	len;

	len = count * size;
	out = malloc(len);
	if (!out)
		return (0);
	mem = out;
	while (len-- > 0)
		*mem++ = '\0';
	return (out);
}
