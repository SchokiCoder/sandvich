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

#ifndef _SNVP_PARSE_H
#define _SNVP_PARSE_H

#include <stddef.h>

static const PARSE_ERR_CRITICAL_THRESHOLD = 1000;

enum ParseErrorKind
{
	PEK_UNEXPECTED_SYMBOL = 1000
}

struct ParseError
{
	enum ParseErrorKind kind;
	uint32_t row_begin;
	uint32_t col_begin;
	uint32_t row_end;
	uint32_t col_end;
}

struct ParseFile
{
	char *path;
	ParseError *errors;
}

struct ParseFile ParseFile_parse();

void ParseFile_clear(ParseFile*);

#endif /* _SNVP_PARSE_H */
