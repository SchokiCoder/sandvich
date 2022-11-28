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
#include <stddef.h>
#include <string.h>
#include <time.h>




typedef int bool;
#define TRUE 1
#define FALSE 0




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
snvint_t BCO_op_exec (const BCO_op op, const snvint_t a, const snvint_t b)
{
printf ("op (%i, %li, %li)\n", op, a, b);
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
        printf ("ERROR: unknown byte operation (%u) given, can not execute\n",
                op);
        break;
    }

  return 0;
}

union BCO_int
{
  size_t index;
  snvint_t value;
};

struct BCO_intref
{
  bool is_index;    /* flags, if this is an actual variable */
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

void
BCO_obj_add_stmt (struct BCO_obj *self, bool *is_op_buf, bool *is_intb_buf,
                  const BCO_op op_buf, const struct BCO_intref inta,
                  const struct BCO_intref intb)
{
  /* if operation is in buffer */
  if (*is_op_buf == TRUE && *is_intb_buf == TRUE)
    {
      self->stmts[self->count_stmts].operation = op_buf;
      self->stmts[self->count_stmts].a = inta;
      self->stmts[self->count_stmts].b = intb;
      self->count_stmts++;
      *is_op_buf = FALSE;
      *is_intb_buf = FALSE;
    }
}

void
end_collecting (bool *is_collecting, char *src, char *num_str,
                const size_t pos, snvint_t *result, bool *result_set)
{
  char str_end_repl_buf;
  
  if (*is_collecting == TRUE)
    {
      /* stop collecting number */
      *is_collecting = FALSE;

      /* convert collected number into actual int */
      str_end_repl_buf = src[pos];
      src[pos] = '\0';
      *result = atol (num_str);
      src[pos] = str_end_repl_buf;

      *result_set = TRUE;
    }
}

struct BCO_obj BCO_obj_compile (char *src)
{
  size_t i;
  bool run = TRUE;
  struct BCO_obj result;
  
  bool is_collecting = FALSE;
  char *num_str;
  
  bool is_op_buf = TRUE;
  BCO_op op_buf = BCO_OP_ADD;
  
  bool is_intb_buf = FALSE;
  struct BCO_intref inta, intb;
  
  inta.is_index = TRUE;
  inta.integer.index = 0;
  
  intb.is_index = FALSE;
  intb.integer.value = 0;

  result.count_ints = 1;
  result.ints[0] = 0;

  result.count_stmts = 0;

  /* step chars */
  for (i = 0; run == TRUE; i++)
    {
printf ("i: src[%li] = %c\n", i, src[i]);
printf ("\nis_collecting: %i\nnum_str: \"%s\"\nis_op_buf: %i\nop_buf: %i\nis_intb_buf: %i\nintb: %li\n\n",
        is_collecting, num_str, is_op_buf, op_buf, is_intb_buf, intb.integer.value);
printf (" || \n \\/ \n");
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
                num_str = &src[i];
              }
            break;

          case '+':
            /* end collecting and get number */
            end_collecting (&is_collecting, src, num_str, i,
                            &intb.integer.value, &is_intb_buf);
            
            /* try add stmt */
            BCO_obj_add_stmt (&result, &is_op_buf, &is_intb_buf, op_buf, inta,
                              intb);
            
            /* buffer operation */
            op_buf = BCO_OP_ADD;
            is_op_buf = TRUE;
            break;

          case '-':
            /* end collecting and get number */
            end_collecting (&is_collecting, src, num_str, i,
                            &intb.integer.value, &is_intb_buf);
            
            /* try add stmt */
            BCO_obj_add_stmt (&result, &is_op_buf, &is_intb_buf, op_buf, inta,
                              intb);
            
            /* buffer operation */
            op_buf = BCO_OP_SUB;
            is_op_buf = TRUE;
            break;

          case '*':
            /* end collecting and get number */
            end_collecting (&is_collecting, src, num_str, i,
                            &intb.integer.value, &is_intb_buf);
            
            /* try add stmt */
            BCO_obj_add_stmt (&result, &is_op_buf, &is_intb_buf, op_buf, inta,
                              intb);
            
            /* buffer operation */
            op_buf = BCO_OP_MUL;
            is_op_buf = TRUE;
            break;

          case '/':
            /* end collecting and get number */
            end_collecting (&is_collecting, src, num_str, i,
                            &intb.integer.value, &is_intb_buf);
            
            /* try add stmt */
            BCO_obj_add_stmt (&result, &is_op_buf, &is_intb_buf, op_buf, inta,
                              intb);
            
            /* buffer operation */
            op_buf = BCO_OP_DIV;
            is_op_buf = TRUE;
            break;

          case '\0':
            run = FALSE;

          case ' ':
            /* end collecting and get number */
            end_collecting (&is_collecting, src, num_str, i,
                            &intb.integer.value, &is_intb_buf);
            
            /* try add stmt */
            BCO_obj_add_stmt (&result, &is_op_buf, &is_intb_buf, op_buf, inta,
                              intb);
            break;

          default:
            printf ("ERROR: invalid character (%c) received\n", src[i]);
            break;
        }
printf ("\nis_collecting: %i\nnum_str: \"%s\"\nis_op_buf: %i\nop_buf: %i, is_intb_buf: %i\nintb: %li\n\n",
        is_collecting, num_str, is_op_buf, op_buf, is_intb_buf, intb.integer.value);
printf ("--------------------\n");
    }

  return result;
}

void BCO_obj_exec (struct BCO_obj *self)
{
  size_t i;
  size_t index;
  snvint_t value;

  for (i = 0; i < self->count_stmts; i++)
    {
      if (self->stmts[i].a.is_index == FALSE)
        {
          printf ("ERROR: tried to use value as variable index");
          return;
        }

      index = self->stmts[i].a.integer.index;
      value = self->stmts[i].b.integer.value;

      self->ints[index] = BCO_op_exec (self->stmts[i].operation,
                                       self->ints[index],
                                       value);
    }
}

/*
    If you change the code,
    DO ALSO change the manually converted c code !!!
*/
const char *CODE = "1+2 / 3 * 4 - 5 + 11 * 2 - 4 / 8 - 1";

const snvint_t SOLUTION = 1;

void SPD_assert (const snvint_t result, const snvint_t solution)
{
  if (result != solution)
    printf ("ERROR: result (%li) did not match solution (%li)\n",
            result,
            solution);
}

void SPD_bco_all ()
{
  clock_t start, stop;
  struct BCO_obj obj;
  char src[128];
  strcpy (src, CODE);

  start = clock ();

  obj = BCO_obj_compile (src);

  BCO_obj_exec (&obj);

  SPD_assert (obj.ints[0], SOLUTION);

  stop = clock ();
  printf ("%li clocks | byte compile and exec\n", (stop - start));
}

/*
void SPD_bco_execonly ()
{
  clock_t start, stop;
  struct BCO_obj obj;
  char src[128];
  strcpy (src, CODE);

  obj = BCO_obj_compile (src);

  start = clock ();

  BCO_obj_exec (&obj);

  SPD_assert (obj.ints[0], SOLUTION);

  stop = clock ();
  printf ("%li clocks | byte exec only\n", (stop - start));
}

void SPD_nativec ()
{
  clock_t start, stop;
  snvint_t result = 0;

  start = clock ();

  outdated;
  result += 1;
  result += 2;
  result /= 3;
  result *= 4;
  result -= 5;
  result += 11;
  result *= 2;
  result -= 4;
  result /= 8;
  result -= 1;

  SPD_assert (result, SOLUTION);

  stop = clock ();
  printf ("%li clocks | native c\n", (stop - start));
}
*/

int main ()
{
  /*SPD_interpret ();*/
  SPD_bco_all ();
  /*SPD_bco_execonly ();*/
  /*SPD_nativec ();*/

  return 0;
}

