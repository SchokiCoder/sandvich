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
#include <time.h>
#include <string.h>
#include "snv_test_bco.h"

/*
	If you change the code,
	DO ALSO change the manually converted c code !!!
*/
const char *CODE = "1*3 / 3 + 1 - 1";/*"1 + 2 / 3 * 4 - 5 + 11 * 2 - 4 / 8 - 1";*/

const snvint_t SOLUTION = 1;

void SPD_assert(const snvint_t result, const snvint_t solution)
{
	if (result != solution)
		printf("ERROR: result (%li) did not match solution (%li)\n", result, solution);
}

void SPD_bco_all()
{
	clock_t start, stop;
	struct BCO_obj obj;
	char src[128];
	strcpy(src, CODE);
	
	start = clock();
	
	obj = BCO_obj_compile(src);
	
	BCO_obj_exec(&obj);
	
	SPD_assert(obj.ints[0], SOLUTION);
	
	stop = clock();
	printf("%li clocks | byte compile and exec\n", (stop - start));
}

void SPD_bco_execonly()
{
	clock_t start, stop;
	struct BCO_obj obj;
	char src[128];
	strcpy(src, CODE);
	
	obj = BCO_obj_compile(src);
	
	start = clock();
	
	BCO_obj_exec(&obj);
	
	SPD_assert(obj.ints[0], SOLUTION);
	
	stop = clock();
	printf("%li clocks | byte exec only\n", (stop - start));
}

void SPD_nativec()
{
	clock_t start, stop;
	snvint_t result = 0;
	
	start = clock();
		
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
	
	SPD_assert(result, SOLUTION);
	
	stop = clock();
	printf("%li clocks | native c\n", (stop - start));
}

int main()
{
	/*SPD_interpret();*/
	SPD_bco_all();
	/*SPD_bco_execonly();*/
	SPD_nativec();
	
	return 0;
}

