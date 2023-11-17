#ifndef __MONTY_H__
#define __MONTY_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>
/*#include <fnctl.h>*/

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/**
 * struct glob_s - variables
 * @arg: value
 * @fd: pointer to the monty file
 * @line: Line to content
 * @flg: flag change 
 * Description: Takes value through program
 */
typedef struct glob_s
{
	char *arg;
	FILE *fd;
	char *content;
	int flg
} glob_t;

extern glob_t global;

int main(int argc, char *argv[])
int execute(char *content, stack_t **head, unsigned int counter, FILE *fd);
char *_realloc(char *ptr, unsigned int old_size, unsigned int new_size);
ssize_t getstdin(char **lineptr, int fd);
char  *clean_line(char *content);

void monty_push(stack_t **head, unsigned int number);
void monty_pall(stack_t **head, unsigned int number);
void monty_pint(stack_t **head, unsigned int number);
void monty_pop(stack_t **head, unsigned int counter);
void monty_swap(stack_t **head, unsigned int counter);
void monty_add(stack_t **head, unsigned int counter);
void monty_nop(stack_t **head, unsigned int counter);
void monty_sub(stack_t **head, unsigned int counter);
void montey_div(stack_t **head, unsigned int counter);
void monty_mul(stack_t **head, unsigned int counter);
void monty_mod(stack_t **head, unsigned int counter);
void monty_pchar(stack_t **head, unsigned int counter);
void monty_pstr(stack_t **head, unsigned int counter);
void monty_rotl(stack_t **head, unsigned int counter);
void monty_rotr(stack_t **head, __attribute__((unused)) unsigned int counter);

void addnode(stack_t **head, int n);
void addqueue(stack_t **head, int n);

void free_stack(stack_t *head);
void monty_queue(stack_t **head, unsigned int counter);
void monty_stack(stack_t **head, unsigned int counter);


#endif /* __MONTY_H__ */
