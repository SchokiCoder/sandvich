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

#include <stdlib.h>
#include "SM_string.h"

usize SM_strlen( const char *cstr )
{
	usize result = 0;

	while (cstr[result] != '\0')
		result++;

	return result + 1;
}

void SM_strcpy( char *restrict dest, const char *restrict src, usize len )
{
	for (usize i = 0; i < len; i++)
    {
        dest[i] = src[i];
    }

    dest[len - 1] = '\0';
}

bool SM_strequal( const char *restrict a, const char *restrict b )
{
	const usize a_len = SM_strlen(a);
	const usize b_len = SM_strlen(b);

	if (a_len != b_len)
		return false;

	for (usize i = 0; i < a_len; i++)
    	if (a[i] != b[i])
    		return false;

	return true;
}

void SM_String_grow( SM_String *str )
{
	str->size *= 2;
	str->str = realloc(str->str, str->size);
}

void SM_String_ensure_size( SM_String *str, usize size )
{
	while (str->size < size)
    	SM_String_grow(str);
}

SM_String SM_String_new( const usize inital_size )
{
	SM_String result = {
		.len = 0,
		.str = malloc(inital_size),
		.size = inital_size
	};

	return result;
}

SM_String SM_String_from( const char *cstr )
{
	SM_String result = SM_String_new(SM_STRING_IMPLICIT_INITIAL_SIZE);
	const usize strlen = SM_strlen(cstr);

	SM_String temp = {
		.str = (char*) cstr,
		.len = strlen - 1,
		.size = strlen
	};

	SM_String_copy(&result, &temp);

	return result;
}

SM_String SM_String_contain( const char *cstr )
{
    const usize strlen = SM_strlen(cstr);
    const SM_String result = {
    	.len = strlen - 1,
    	.size = 0,
    	.str = (char*) cstr
    };

    return result;
}

void SM_String_copy( SM_String *restrict dest, SM_String *restrict src )
{
	SM_String_ensure_size(dest, src->len + 1);

	SM_strcpy(dest->str, src->str, src->len + 1);

    dest->len = src->len;
}

void SM_String_append( SM_String *restrict dest, SM_String *restrict addendum )
{
	SM_String_ensure_size(dest, dest->len + addendum->len + 1);

	SM_strcpy(&dest->str[dest->len], addendum->str, addendum->len + 1);

	dest->len += addendum->len;
}

void SM_String_copy_cstr( SM_String *restrict dest, const char *restrict src )
{
	const usize src_len = SM_strlen(src);
	SM_String_ensure_size(dest, src_len);

	SM_strcpy(dest->str, src, src_len);

	dest->len = src_len - 1;
}

void SM_String_append_cstr( SM_String *restrict dest, const char *restrict addendum )
{
	const usize add_len = SM_strlen(addendum);
	SM_String_ensure_size(dest, dest->len + add_len);

	SM_strcpy(&dest->str[dest->len], addendum, add_len);

	dest->len += add_len - 1;
}

bool SM_String_equal( const SM_String *restrict a, const SM_String *restrict b )
{
	if (a->len != b->len)
		return false;

	for (usize i = 0; i < a->len; i++)
		if (a->str[i] != b->str[i])
			return false;

	return true;
}

void SM_String_empty( SM_String *str )
{
	str->str[0] = '\0';
    str->len = 0;
}

void SM_String_clear( SM_String *str )
{
	free(str->str);
	str->len = 0;
	str->size = 0;
}
