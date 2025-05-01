/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:19:35 by rwassim           #+#    #+#             */
/*   Updated: 2025/05/01 17:50:29 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//taille a malloc 
size_t  ft_strlen(char *s)
{
	size_t  i;
	
	i = 0;
	while (s[i])
		i++;
	return (i);
}

//copie de la chaine et la retourne deja aloue
char	*ft_strdup(char *s)
{
	char	*dup;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * (size + 1));
	if (dup == NULL)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

//pour gerer ma static et les tmp
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*strmalloc;

	i = 0;
	if (start >= ft_strlen(s) || len == 0)
	{
		strmalloc = malloc(sizeof(char) * (len + 1));
		strmalloc[i] = '\0';
		return (strmalloc);
	}
	strmalloc = malloc(sizeof(char) * (len + 1));
	if (strmalloc == NULL)
		return (NULL);
	while (s[start] && i < len)
	{
		strmalloc[i] = s[start];
		start++;
		i++;
	}
	strmalloc[i] = '\0';
	return (strmalloc);
}

//pour copie sans malloc
void	*ft_memcpy(void *dest, void *src, size_t n)
{
	size_t			i;
	
	i = 0;
	if (src == NULL && dest == NULL)
		return (0);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

// chercher le \n 
char	*ft_strchr(char *s, int c)
{
	if (!s && c != '\0')
		return (0);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}