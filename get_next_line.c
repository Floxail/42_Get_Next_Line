/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:56:23 by flvejux           #+#    #+#             */
/*   Updated: 2025/10/17 13:06:03 by flvejux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *stash)
{
	int		count;
	char	*buffer;

	count = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stash, '\n') && count > 0)
	{
		count = (int)read(fd, buffer, BUFFER_SIZE);
		if (count < 0)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		if (count == 0)
			return ;
		buffer[count] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (NULL);
	}
}

static char	*get_line(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
		return (NULL);
	tmp = ft_substr(str, 0, (i + 1) - ft_strlen(str));
	if (!tmp)
		return (0);
	tmp[i + 1] = '\0';
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*tmp;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	tmp = read_line(fd, buf);
	free (buf);
	if (!tmp)
		return (line);
	tmp = get_line(line);
	return (tmp);
}
