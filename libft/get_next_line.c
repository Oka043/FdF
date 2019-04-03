/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaktion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 00:22:05 by olaktion          #+#    #+#             */
/*   Updated: 2018/08/23 15:09:49 by olaktion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_newline(char *str)
{
	int		len;
	int		j;
	char	*newline;

	len = 0;
	while (str[len])
		len++;
	newline = (char*)malloc(sizeof(char) * len + 1);
	j = 0;
	while (str[j] != '\n' && j < len)
	{
		newline[j] = str[j];
		j++;
	}
	newline[j] = '\0';
	return (newline);
}

static char	*ft_join_free(char *buffer, char *newline)
{
	char	*tmp;

	if (!buffer || !newline)
		return (NULL);
	if (!(tmp = ft_strjoin(newline, buffer)))
		return (NULL);
	free(newline);
	newline = NULL;
	return (tmp);
}

static char	*ft_del(char *str)
{
	int		j;
	char	*newline;

	j = 0;
	while (str[j] != '\n' && str[j])
		j++;
	if ((str[j] && !str[j + 1]) || !str[j])
	{
		ft_strdel(&str);
		return (NULL);
	}
	newline = ft_strdup(str + j + 1);
	ft_strdel(&str);
	return (newline);
}

int			get_next_line(const int fd, char **line)
{
	static t_f	files[4096];
	int			re;
	char		str[BUFF_SIZE + 1];

	if (fd < 0 || BUFF_SIZE < 1 || !line || read(fd, line, 0) < 0)
		return (-1);
	if (!files[fd].buf)
		if (!(files[fd].buf = ft_strnew(1)))
			return (-1);
	while (!(ft_strchr(files[fd].buf, '\n')))
	{
		re = read(fd, str, BUFF_SIZE);
		if (re == -1)
			return (-1);
		str[re] = '\0';
		files[fd].buf = ft_join_free(str, files[fd].buf);
		if ((re == 0 && *(files[fd].buf) == '\0') || !(files[fd].buf))
			return (0);
		if (re == 0)
			break ;
	}
	*line = ft_newline(files[fd].buf);
	files[fd].buf = ft_del(files[fd].buf);
	return (1);
}
