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

#ifndef _SNV_TEST_BCO_H
#define _SNV_TEST_BCO_H

#include <stddef.h>
#include "snv_test_bool.h"

/* Sandvich definitions */
/* in this test version integers are always signed and 32 to 64 bit long */
typedef long int snvint_t;

/* Byte Code Operations */
enum BCO_ops
{
	BCO_OP_ADD = 1,
	BCO_OP_SUB = 2,
	BCO_OP_MUL = 3,
	BCO_OP_DIV = 4
};

typedef enum BCO_ops BCO_op;

/*
	the parameters can be swapped, without the user noticing :/
*/
long BCO_op_exec( const BCO_op, const long, const long );

union BCO_int
{
	size_t index;
	snvint_t value;
};

struct BCO_intref
{
	bool is_index;	/* flags, if this is an actual variable */
	union BCO_int integer;
};

struct BCO_stmt
{
	BCO_op operation;
	struct BCO_intref a;
	struct BCO_intref b;
};

/* evil arbitrary limits >:D */
#define BCO_OBJ_MAX_VARIABLES 64
#define BCO_OBJ_MAX_STATEMENTS 64

struct BCO_obj
{
	/* variable storage */
	size_t count_ints;
	snvint_t ints[BCO_OBJ_MAX_VARIABLES];
	
	/* statements */
	size_t count_stmts;
	struct BCO_stmt stmts[BCO_OBJ_MAX_STATEMENTS];
};

struct BCO_obj BCO_obj_compile( char* );

void BCO_obj_exec( struct BCO_obj* );

#endif /* _SNV_TEST_BCO_H */

