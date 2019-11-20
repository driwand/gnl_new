/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkssiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:27:58 by abkssiba          #+#    #+#             */
/*   Updated: 2019/11/19 21:25:01 by abkssiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#define BUFFER_SIZE 99
//
//size_t	ft_strlen(const char *s)
//{
//    size_t i;
//
//    i = 0;
//    while (*s)
//    {
//        i++;
//        s++;
//    }
//    return (i);
//}
//
//char	*ft_strchr(const char *s, int c)
//{
//    size_t	i;
//    char	*str;
//    size_t	len;
//
//    len = ft_strlen(s);
//    str = (char*)s;
//    i = 0;
//    while (i < len + 1)
//    {
//        if (str[i] == (char)c)
//            return (&str[i+1]);
//        i++;
//    }
//    return (NULL);
//}
//
//char	*ft_strdup(const char *s1)
//{
//    char	*str;
//    size_t	len;
//    size_t i;
//
//    i = 0;
//    len = ft_strlen(s1);
//    str = malloc(len + 1);
//    if (str)
//    {
//        while (i < len)
//        {
//            str[i] = s1[i];
//            i++;
//        }
//        str[len] = 0;
//        return (str);
//    }
//    return (NULL);
//}
//
//char		*ft_strjoin(char *s1, char *s2)
//{
//    char	*str;
//    size_t	ls1;
//    size_t	ls2;
//    int	j;
//    int i;
//
//    i = -1;
//    if (!s1 || !s2)
//        return (NULL);
//    ls1 = ft_strlen(s1);
//    ls2 = ft_strlen(s2);
//    str = (char*)malloc(sizeof(char) * (ls1 + ls2 + 1));
//    if (!str)
//        return (NULL);
//    while (++i < (int) ls1)
//        str[i] = s1[i];
//    j = 0;
//    while (i < (int)(ls1 + ls2))
//    {
//        str[i++] = s2[j++];
//    }
//    str[ls1 + ls2] = '\0';
//    return (str);
//}
//
//char    *ft_substr(char *s, unsigned int start, size_t len)
//{
//    char    *str;
//    char    *p;
//    char    *r;
//    size_t    l;
//
//    if (!s)
//        return (NULL);
//    l = ft_strlen(&s[start]);
//    if (start > ft_strlen(s))
//        return (ft_strdup(""));
//    l = (l <= len) ? l : len;
//    if (!(str = (char *)malloc(l + 1)))
//        return (str);
//    p = (char*)(s + start);
//    r = str;
//    while (*p && l--)
//        *str++ = *p++;
//    *str = '\0';
//    return (r);
//}
//

int get_char_index(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	if (str[i] == '\0')
	    return (i);
	return (-1);
}

int get_rest(int x, char *to_save, char **line, int index)
{
    char *tmp;

    if (x < 0)
        return (-1);
    if (x == 0)
        index = get_char_index(to_save);
    if (x == 0 && !to_save[0])
        return (0);
    if (index != -1 || x == 0)
    {
        if (to_save[index] == '\n')
        {
            *line = ft_substr(to_save, 0, index);
            tmp = to_save;
            to_save = ft_strdup(&tmp[index + 1]);
            free(tmp);
            return (1);
        }
        else if (to_save[index] == '\0')
        {
            *line = ft_substr(to_save, 0, index);
            to_save[0] = '\0';
            return (1);
        }
        free(to_save);
        return(0);
    }
    return (0);
}

int get_next_line(int fd, char **line)
{
	static char *to_save[4864];
	char *buffer;
	int x;
	char *tmp;
    int index;

	buffer = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || !line)
	    return (-1);
	while ((x = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[x] = '\0';
		if (!to_save[fd])
			to_save[fd] = ft_strdup(buffer);
		else
		{
			tmp = to_save[fd];
			to_save[fd] = ft_strjoin(to_save[fd], buffer);
			free(tmp);
		}
        if ((index = get_char_index(to_save[fd])))
            break;
	}
	free(buffer);
	return (get_rest(x, to_save[fd], line, index));
}


int main()
{
    char *str;
    int i;

    int fd = open("rr", O_RDONLY);
    while ((i = get_next_line(fd, &str) > 0))
    {
        printf("%s\n", str);
        free(str);
    }
//    get_next_line(fd, &str);
//    printf("%s\n", str);
//    free(str);

// 	get_next_line(fd, &str);
// 	printf("%s\n", str);
//    free(str);
//
//    get_next_line(fd, &str);
//    printf("%s\n", str);
//    free(str);
//
//    get_next_line(fd, &str);
//    printf("%s\n", str);
//    free(str);
//
//    get_next_line(fd, &str);
//    printf("%s\n", str);
//    free(str);
    return 0;
}

