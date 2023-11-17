#include "monty.h"

/**
 * monty_push - add node to the stack
 * @head: stack head
 * @counter: line_number
 * Return: no return
*/
void monty_push(stack_t **head, unsigned int counter)
{
	int n, j = 0, flag = 0;

	if (global.arg)
	{
		if (global.arg[0] == '-')
			j++;
		for (; global.arg[j] != '\0'; j++)
		{
			if (global.arg[j] > 57 || global.arg[j] < 48)
				flag = 1; }
		if (flag == 1)
		{ fprintf(stderr, "L%d: usage: push integer\n", counter);
			fclose(global.fd);
			free(global.content);
			free_stack(*head);
			exit(EXIT_FAILURE); }}
	else
	{ fprintf(stderr, "L%d: usage: push integer\n", counter);
		fclose(global.fd);
		free(global.content);
		free_stack(*head);
		exit(EXIT_FAILURE); }
	n = atoi(global.arg);
	if (global.flg == 0)
		addnode(head, n);
	else
		addqueue(head, n);
}

/**
 * monty_pall - prints the stack
 * @head: stack head
 * @counter: no used
 * Return: no return
*/
void monty_pall(stack_t **head, unsigned int counter)
{
	stack_t *h;
	(void)counter;

	h = *head;
	if (h == NULL)
		return;
	while (h)
	{
		printf("%d\n", h->n);
		h = h->next;
	}
}

/**
 * monty_pint - prints the top
 * @head: stack head
 * @counter: line_number
 * Return: no return
*/
void monty_pint(stack_t **head, unsigned int counter)
{
	if (*head == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", counter);
		fclose(global.fd);
		free(global.content);
		free_stack(*head);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*head)->n);
}

/**
 * f_pop - prints the top
 * @head: stack head
 * @counter: line_number
 * Return: no return
*/
void f_pop(stack_t **head, unsigned int counter)
{
	stack_t *h;

	if (*head == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", counter);
		fclose(global.fd);
		free(global.content);
		free_stack(*head);
		exit(EXIT_FAILURE);
	}
	h = *head;
	*head = h->next;
	free(h);
}

/**
 * f_swap - adds the top two elements of the stack.
 * @head: stack head
 * @counter: line_number
 * Return: no return
*/
void f_swap(stack_t **head, unsigned int counter)
{
	stack_t *h;
	int len = 0, aux;

	h = *head;
	while (h)
	{
		h = h->next;
		len++;
	}
	if (len < 2)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", counter);
		fclose(global.fd);
		free(global.content);
		free_stack(*head);
		exit(EXIT_FAILURE);
	}
	h = *head;
	aux = h->n;
	h->n = h->next->n;
	h->next->n = aux;
}
