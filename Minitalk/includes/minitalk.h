/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:38:39 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/21 09:21:57 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <signal.h>
# include "libft.h"
# include "ft_printf.h"
# define BUFFER 1000

void	send_bits(int server_id, unsigned char c);
int		is_unicode(char *s);
int		send_unicode(char *s, int server_id, int *n);

#endif
