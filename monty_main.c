#include "monty.h"

/**
 * main - The entry point function for Monty Interpreter.
 * @ac: The number of arguments.
 * @av: The pointer to an array of inputed arguments.
 * Return: Always 0 (on Success).
 */

int main(int ac, char **av)
{
	FILE *fd = NULL;
	int exit_status = EXIT_SUCCESS;

	if (ac != 2)
		return (usage_error(1));

	fd = fopen(av[1], "r");
	if (fd == NULL)
		return (open_error(av[1]));

	exit_status = monty_run(fd);
	fclose(fd);
	return (exit_status);
	/**
	 * open_error(av[1]);
	 * monty_run(fd);
	 * exit(EXIT_SUCCESS);
	 * return (0);
	 */
}

/**
 * execute - Function that checks for a command "opcode" and execute the
 * function if there's a match.
 * @token: Tokane containing the opcode to execute.
 * @stack: Doubly linked list representation of a stack.
 * @line_num: Line number where the opcode was found.
 * Return: EXIT_SUCCESS in success, or EXIT_FAILURE on failure.
 */

int execute(char **token, stack_t **stack, unsigned int line_num)
{
	unsigned int i = 0;

	instruction_t op[] = {
		{"push", monty_push}
		{"pall", monty_pall},
		{"pint", monty_pint},
		/**
		 * {"pop", monty_pop},
		 * {"swap", monty_swap},
		 * {"add", monty_add},
		 * {"sub", monty_sub},
		 * {"mul", monty_mul},
		 * {"div", monty_div},
		 * {"mod", monty_mod},
		 * {"pchar", monty_pchar},
		 * {"pstr", monty_pstr},
		 * {"rotl", monty_rotl},
		 * {"rotr", monty_rotr},
		 */
		{"null", NULL}
	};

	for (i = 0; i < 14; i++)
	{
		if (strcmp(op[i].opcode, token[0]) == 0)
		{
			op[i].f(stack, line_num);
			return (EXIT_SUCCESS);
		}
	}
	free_stack(stack);
	fprintf(stderr, "L%i: unknown instruction %s\n", line_num, token[0]);
	return (EXIT_FAILURE);
}

#include "monty.h"

/**
 * monty_run - A function that runs a Monty bytecodes script.
 * @fd: File descriptor for an open Monty bytecodes script.
 * Return: EXIT_SUCCESS on success, or EXIT_FAILURE on error.
 */
int monty_run(FILE *fd)
{
	stack_t *stack = NULL;
	char *line = NULL, **token = NULL, delim[] = " \n\t\a\b";
	size_t len = 0, mode = 1;
	unsigned int line_num = 0, exit_status = EXIT_SUCCESS;

	while (getline(&line, &len, fd) != -1)
	{
		line_num++;
		if (empty_line(line, delim))
			continue;
		token = tokening(line, delim);
		if (token[0][0] == '#' || strcmp(token[0], "nop") == 0)
		{
			free(token);
			continue;
		}
		else if (strcmp(token[0], "stack") == 0)
			mode = 1;
		else if (strcmp(token[0], "queue") == 0)
			mode = 0;
		else if (strcmp(token[0], "push") == 0 && mode == 0)
			exit_status = monty_pushq(&stack, token, line_num);
		else if (strcmp(token[0], "push") == 0 && mode == 1)
			exit_status = monty_push(&stack, token, line_num);
		else
			exit_status = execute(token, &stack, line_num);
		free(token);
		if (exit_status == EXIT_FAILURE)
			break;
	}
	free_stack(&stack);
	free(line);
	return (exit_status);
}
