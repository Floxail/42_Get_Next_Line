/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:56:23 by flvejux           #+#    #+#             */
/*   Updated: 2025/10/18 09:42:32 by flvejux          ###   ########.fr       */
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
			break ;
		buffer[count] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (NULL);
	}
	free(buffer);
	return (stash);
}

static char	*get_line(char **stash)
{
	char	*nl;
	char	*tmp;
	char	*line;

	if (!*stash || !**stash)
		return (NULL);
	nl = ft_strchr(*stash, '\n');
	if (nl != NULL)
	{
		line = ft_substr(*stash, 0, nl - *stash + 1);
		tmp = ft_strdup(nl + 1);
		free(*stash);
		*stash = tmp;
		if (!stash || !line)
			return (NULL);
	}
	else
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
		if (!line)
			return (NULL);
	}
	return (line);
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
