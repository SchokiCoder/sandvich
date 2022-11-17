/*
	schoki_misc
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

#ifndef SM_STRING_H
#define SM_STRING_H

#include <stdbool.h>
#include "SM_types.h"

static const usize SM_STRING_IMPLICIT_INITIAL_SIZE = 8;

usize SM_strlen( const char *cstr );

void SM_strcpy( char *restrict dest, const char *restrict src, usize len );

bool SM_strequal( const char *restrict a, const char *restrict b );

typedef struct SM_String
{
	usize len;
	usize size;
	char *str;
} SM_String ;

SM_String SM_String_new( const usize initial_size );

SM_String SM_String_from( const char *cstr );

SM_String SM_String_contain( const char *cstr );

void SM_String_copy( SM_String *restrict dest, SM_String *restrict src );

void SM_String_append( SM_String *restrict dest, SM_String *restrict addendum );

void SM_String_copy_cstr( SM_String *restrict dest, const char *restrict src );

void SM_String_append_cstr( SM_String *restrict dest, const char *restrict addendum );

bool SM_String_equal( const SM_String *restrict a, const SM_String *restrict b );

void SM_String_empty( SM_String *str );

void SM_String_clear( SM_String *str );

#endif // SM_STRING_H
