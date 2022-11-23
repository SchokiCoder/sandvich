/*
	The Sandvich programming language
	Copyright (C) 2022	Andy Frank Schoknecht

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include "snv_test_bco.h"

snvint_t BCO_op_exec( const BCO_op op, const snvint_t a, const snvint_t b )
{
	switch (op)
	{
		case BCO_OP_ADD:
			return a + b;
			break;
		
		case BCO_OP_SUB:
			return a - b;
			break;
		
		case BCO_OP_MUL:
			return a * b;
			break;
		
		case BCO_OP_DIV:
			return a / b;
			break;
		
		default:
			printf("ERROR: unknown byte operation (%u) given, can not execute\n", op);
			break;
	}
	
	return 0;
}

struct BCO_obj BCO_obj_compile( char *src )
{
	size_t i;
	bool run = TRUE;
	struct BCO_obj result;
	bool operation_buffered = TRUE;
	BCO_op operation = BCO_OP_ADD;
	bool is_collecting = FALSE;
	char *number_begin;
	char temp;
	bool number_buffered = FALSE;
	snvint_t number;
	
	result.count_ints = 1;
	result.ints[0] = 0;
	
	result.count_stmts = 0;
	
	/* step chars */
	for (i = 0; run == TRUE; i++)
	{
		switch (src[i])
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (is_collecting == FALSE)
				{
					/* start collecting number */
					is_collecting = TRUE;
					number_begin = &src[i];
				}
				break;
			
			case '+':
				operation = BCO_OP_ADD;
				operation_buffered = TRUE;
				goto end_collecting;
			
			case '-':
				operation = BCO_OP_SUB;
				operation_buffered = TRUE;
				goto end_collecting;
			
			case '*':
				operation = BCO_OP_MUL;
				operation_buffered = TRUE;
				goto end_collecting;
			
			case '/':
				operation = BCO_OP_DIV;
				operation_buffered = TRUE;
				goto end_collecting;
			
			case '\0':
				run = FALSE;
				goto end_collecting;
				
			case ' ': end_collecting:
				if (is_collecting == TRUE)
				{
					/* stop collecting number */
					is_collecting = FALSE;
					
					/* convert collected number into actual int */
					temp = src[i];
					src[i] = '\0';
					number = atol(number_begin);
					src[i] = temp;
					
					number_buffered = TRUE;
				}
				break;
			
			default:
				printf("ERROR: invalid character (%c) received\n", src[i]);
				break;
		}
		
		/* if operation is in buffer */
		if (operation_buffered == TRUE && number_buffered == TRUE)
		{
			/* add new statement */
			result.stmts[result.count_stmts].operation = operation;
			result.stmts[result.count_stmts].a.is_index = TRUE;
			result.stmts[result.count_stmts].a.integer.index = 0;
			result.stmts[result.count_stmts].b.is_index = FALSE;
			result.stmts[result.count_stmts].b.integer.value = number;
			result.count_stmts++;
			operation_buffered = FALSE;
printf("op: %i\nnum: %li\n", operation, number);
		}
	}

	return result;
}

void BCO_obj_exec( struct BCO_obj *self )
{
	size_t i;
	size_t index;
	snvint_t value;
	
	for (i = 0; i < self->count_stmts; i++)
	{
		if (self->stmts[i].a.is_index == FALSE)
		{
			printf("ERROR: tried to use value as variable index");
			return;
		}
		
		index = self->stmts[i].a.integer.index;
		value = self->stmts[i].b.integer.value;
		
		self->ints[index] = BCO_op_exec(self->stmts[i].operation, self->ints[index], value);
	}
}

