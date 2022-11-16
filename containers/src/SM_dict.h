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

#ifndef SM_DICT_H
#define SM_DICT_H

#include <stdbool.h>
#include "SM_string.h"

typedef struct SM_DictPair
{
	usize key_djb2;
	SM_String key;
	SM_String value;
} SM_DictPair ;

typedef struct SM_Dict
{
	bool invalid;
	usize len;
	usize size;
	SM_DictPair *data;
} SM_Dict ;

SM_Dict SM_Dict_new( const usize inital_size );

SM_Dict SM_Dict_from_file( const char *filepath );

void SM_Dict_add( SM_Dict *dict, const char *restrict key, const char *restrict value );

bool SM_Dict_find( const SM_Dict *dict, const char *key, usize *index );

bool SM_Dict_write( const SM_Dict *dict, const char *filepath );

void SM_Dict_clear( SM_Dict *dict );

#endif // SM_DICT_H
