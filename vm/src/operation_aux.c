/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operation_aux.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 22:34:22 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/09/16 17:23:52 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					switch_endianness(int n, size_t size)
{
	int				res;

	res = 0;
	if (size == 1)
		return (n);
	else if (size == 2)
		res = ((n >> 8) | (n << 8)) & 0xFFFF;
	else if (size == 4)
	{
		res |= ((n >> (8 * 3)) & 0x000000FF);
		res |= ((n << (8 * 1)) & 0x00FF0000);
		res |= ((n >> (8 * 1)) & 0x0000FF00);
		res |= ((n << (8 * 3)) & 0xFF000000);
	}
	return (res);
}

int					ustr_to_int(unsigned char *field, int position, int size)
{
	unsigned char	current_byte;
	unsigned int	res;
	int				i;
	int				shift;

	res = 0;
	i = 0;
	while (i < size)
	{
		current_byte = field[(position + i) % MEM_SIZE];
		shift = (((size - 1) * 8) - (i * 8));
		res |= (unsigned int)current_byte << shift;
		i++;
	}
	return (switch_endianness(res, size));
}

void				int_to_ustr(int value, unsigned char *field,\
					int position, int size)
{
	unsigned char	current_byte;
	unsigned int	mask;
	int				shift;
	int				i;

	i = 0;
	value = switch_endianness(value, size);
	while (i < size)
	{
		shift = (((size - 1) * 8) - (i * 8));
		mask = 0xFF << shift;
		current_byte = (unsigned char)((value & mask) >> shift);
		field[(position + i) % MEM_SIZE] = current_byte;
		++i;
	}
}
