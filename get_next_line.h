/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:15:00 by rwassim           #+#    #+#             */
/*   Updated: 2025/05/01 17:50:42 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

char	*ft_strchr(char *s, int c);
size_t  ft_strlen(char *s);
char	*ft_strdup(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dest, void *src, size_t n);
char	*ft_verify(char *tmp, char *buff);
void	ft_extract(char **ptr);
char	*ft_free(char **ptr_tmp, char **ptr_buff, ssize_t b);
char	*get_next_line(int fd);

#endif