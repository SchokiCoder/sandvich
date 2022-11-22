/* this is actually slower than compile AND execute together */
snvint_t interpret(char *src)
{
	snvint_t result = 0;
	BCO_op operation = BCO_OP_ADD;
	
	bool run = TRUE;
	size_t i;
	bool is_collecting = FALSE;
	char *number_begin;
	char temp;
	snvint_t number;
	
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
				goto step_exec;
			
			case '-':
				operation = BCO_OP_SUB;
				goto step_exec;
			
			case '*':
				operation = BCO_OP_MUL;
				goto step_exec;
			
			case '/':
				operation = BCO_OP_DIV;
				goto step_exec;
			
			case '\0':
				run = FALSE;
				goto step_exec;
				
			case ' ': step_exec:
				if (is_collecting == TRUE)
				{
					/* stop collecting number */
					is_collecting = FALSE;
					
					/* convert collected number into actual int */
					temp = src[i];
					src[i] = '\0';
					
					number = atol(number_begin);

					src[i] = temp;

					/* execute stored operation */
					result = BCO_op_exec(operation, result, number);
				}
				break;
			
			default:
				printf("ERROR: invalid character (%c) received\n", src[i]);
				break;
		}
	}

	return result;
}

void SPD_interpret()
{
	clock_t start, stop;
	snvint_t result;
	char src[128];
	strcpy(src, CODE);
	
	start = clock();
	
	result = interpret(src);
	
	SPD_assert(result, SOLUTION);
	
	stop = clock();
	printf("%li clocks | interpret\n", (stop - start));
}
