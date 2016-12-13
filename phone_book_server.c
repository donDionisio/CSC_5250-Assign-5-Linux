/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "phone_book.h"
#include "server_util.h"

void push(entry *head, entry *e) {
	if(head == NULL) {
		head = e;
	}
	else {
		entry *current = head;
		while(current) {
			if(current->next == NULL) {
				current->next = e;
				break;
			}
			current = current->next;
		}
	}
}

r_val *
add_to_database_1_svc(entry *argp, struct svc_req *rqstp)
{
	static r_val  result;
	char phone_book_entry[256];

	printf("args %s, %s\n", argp->name, argp->number);
	FILE *fp = fopen("./database.txt", "a");

	strcpy(phone_book_entry, argp->name);
	strcat(phone_book_entry, "# ");
	strcat(phone_book_entry, argp->number);
	strcat(phone_book_entry, "\n");

	printf("entry : %s\n", phone_book_entry);

	if(fputs(phone_book_entry, fp) < 0) {
		perror("Error writing to file");

		result.num = -1;
		result.message = malloc(sizeof(char) * 64);
		strcpy(result.message, "Working");
		result.head = NULL;
	}
	else {
		result.num = ++COUNT;
		result.message = malloc(sizeof(char) * 64);
		strcpy(result.message, "Working");

		result.head = malloc(sizeof(entry));
		result.head->name = malloc(sizeof(char) * 63);
		result.head->number = malloc(sizeof(char) * 63);

		strcpy(result.head->name, argp->name);
		strcpy(result.head->number, argp->number);

		result.head->next = NULL;
	}

	fclose(fp);
	return(&result);
}

r_val *
remove_from_database_1_svc(char **argp, struct svc_req *rqstp)
{
	static r_val  result;
	char c;
	int i;
	int finished_search = 0;
	int found_entry = 0;

	// Build data structure to hold entries
	entry *head = NULL;

	FILE *fp;
	if((fp = fopen("database.txt", "r")) < 0) {
		perror("Error opening file for read");
		return NULL;
	}

	while(!finished_search) {
		i = 0;

		entry *e = malloc(sizeof(entry));
		e->name = malloc(sizeof(char) * 128);
		e->number = malloc(sizeof(char) * 16);
		e->next = NULL;

		e->name[0] = '\0';
		e->number[0] = '\0';

		while((c = fgetc(fp)) != '#') {
			if(c == EOF) {
				break;
			}

			e->name[i] = c;
			e->name[++i] = '\0';
		}

		// Read space
		c = fgetc(fp);
		i = 0;

		while((c = fgetc(fp)) != '\n') {
			if(c == EOF) {
				finished_search = 1;
				break;
			}

			e->number[i] = c;
			e->number[++i] = '\0';
		}

		if(!finished_search) {
			push(head, e);
		}
	}

	entry *current = head;
	entry *trail_current;

	while(current) {
		if(strcmp(current->name, *argp) == 0) {
			found_entry = 1;
			COUNT--;

			if(current == head) {
				if(head->next == NULL) {
					free(head->name);
					free(head->number);
					free(head);
				}
				else {
					trail_current = head;
					head = head->next;

					free(trail_current->name);
					free(trail_current->number);
					free(trail_current);
				}
			}
			else {
				trail_current->next = current->next;

				free(current->name);
				free(current->number);
				free(current);
			}
		}
		else {
			trail_current = current;
			current = current->next;
		}
	}

	fclose(fp);

	if((fp = fopen("database.txt", "w")) < 0) {
		perror("Error opening file for read");
		return NULL;
	}

	// while(current) {
	// 	current = current->next;
	// }

	if(!found_entry) {
		result.num = -1;
		result.message = malloc(sizeof(char) * 128);

		strcpy(result.message, "Entry not found");
	}
	else {
		result.num = COUNT;
		result.message = malloc(sizeof(char) * 64);
		strcpy(result.message, "Working");
	}

	fclose(fp);
	return &result;
}

r_val *
lookup_name_1_svc(char **argp, struct svc_req *rqstp)
{
	static r_val  result;

	/*
	 * insert server code here
	 */

	return &result;
}

r_val *
list_1_svc(void *argp, struct svc_req *rqstp)
{
	static r_val  result;

	/*
	 * insert server code here
	 */

	return &result;
}

int *
quit_1_svc(void *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */

	return &result;
}

int *
terminate_1_svc(void *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */

	return &result;
}
