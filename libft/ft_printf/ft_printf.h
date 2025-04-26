/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:17:10 by tmateja           #+#    #+#             */
/*   Updated: 2024/10/10 14:54:30 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int	ft_printf(const char *str, ...);
int	ft_putchar(char c);
int	ft_put_str(char *str);
int	ft_put_ptr(unsigned long long ptr);
int	ft_put_num(int num);
int	ft_put_unum(unsigned int num);
int	ft_low_hex(unsigned long long num);
int	ft_upper_hex(unsigned long long num);

#endif
