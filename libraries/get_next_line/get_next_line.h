/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:29:14 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/08/15 23:16:18 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*save_leftover(char *str);
char	*extract_line(char *str);
int		ft_strlen(char const *str);
char	*ft_strsearch(char const *str, int c);
char	*ft_append(char *s1, char *s2);
int		len_count(char *str);
char	*ft_strdup(char *s);
char	*read_until_newline(int fd, char **leftover, int *bytes_read);
char	*handle_eof_error(int bytes_read, char **leftover);

#endif