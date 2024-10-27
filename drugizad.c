#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define EXIT_SUCCESS 1

typedef struct _person* position;
typedef struct _person {
	char fname[20];
	char lname[20];
	int byear;
	
	position next;

}person;


position create_person(char* firstname, char* lastname, int birthyear);
int print_list(position head);
int print_person(position person1);

int append(position head, char* firstname, char* lastname, int birthyear);
int prepend(position head, char* firstname, char* lastname, int birthyear);

void delete_person(position head, char* first_name);

position find_by_lname(position head, char* last_name);

int main() {
	char lname1[20];
	char fname1[20];
	char firstname[20];
	char lastname[20];
	int birthyear;

	position head=NULL; //initializing head
	head = (position)malloc(sizeof(person));
	if (head == NULL) {
		printf("Error allocating memory\n");
		return -1;
	}

	strcpy(head->fname, "");
	strcpy(head->lname, "");
	head->byear = 0;
	head->next = NULL;

	printf("enter the data you want to add to the BEGINNING of the list\n");
	scanf("%s %s %d", firstname, lastname, &birthyear);
	prepend (head, firstname, lastname, birthyear); //adding person to the beginning (A)

	printf("\nlist now looks like this (1) :\n"); 
	print_list(head); //printing the list (B)

	printf("enter the data you want to add to the END of the list\n"); 
	scanf("%s %s %d", firstname, lastname, &birthyear);
	append(head, firstname, lastname, birthyear); //adding person to the end (C)


	printf("\nlist now looks like this (2) :\n");
	print_list(head);

	printf("\nenter the last name of the person you want to find\n"); 
	scanf("%s", lname1);
	position wanted_person=NULL;
	wanted_person = find_by_lname(head, lname1); //finding the element in the list (D)
	if (wanted_person == NULL) {
		printf("no person with such last name");
	}
	else { 
		print_person(wanted_person); //printing that person
	}

	printf("\nenter the first name of the person you want to delete\n");
	scanf("%s", &fname1);
	delete_person(head, fname1); //deleting the person from the list (E)

	printf("\nlist now looks like this (3) :\n");
	print_list(head);


	position temp = head->next; //freeing up space in the memory
	while (temp != NULL) {
		position to_free = temp;
		temp = temp->next;
		free(to_free);
	}
	free(head);


	return 0;

}

position create_person( char* firstname, char* lastname, int birthyear) {
	position new_person = NULL;
	new_person = (position)malloc(sizeof(person));
	if (new_person == NULL) {
		printf("Error alocating memory\n");
		return NULL;
	}
	strcpy(new_person->fname, firstname);
	strcpy(new_person->lname, lastname);
	new_person->byear = birthyear;
	new_person->next = NULL;
	return new_person;

}

int print_list(position head) {
	position temp = head->next;
	printf("\nFirst Name:\tLast Name:\tBirth year:\n");
	while (temp != NULL) {
		printf("%s\t\t%s\t\t%d\n", temp->fname, temp->lname, temp->byear);
		temp = temp->next;

	}
	return EXIT_SUCCESS;
}

int print_person(position person1) {
	printf("First name: %s\nLast name: %s\nBirth Year: %d\n", person1->fname, person1->lname, person1->byear);

}

int prepend(position head, char* firstname, char* lastname, int birthyear) {
	position new_person = NULL;
	new_person = create_person(firstname, lastname, birthyear);


	if (new_person == NULL) {
		return -1;
	}

	new_person->next = head->next;
	head->next = new_person;  

	return EXIT_SUCCESS;
}

int append(position head, char* firstname, char* lastname, int birthyear) {
	position new_person = create_person(firstname, lastname, birthyear);
	
	position temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = new_person;



return EXIT_SUCCESS;

}

position find_by_lname(position head, char* last_name) {
	position temp = head->next;
	while (temp != NULL) {
		if (strcmp(temp->lname, last_name) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;

}

void delete_person(position head, char* first_name) {
	position temp = head;
	while (temp->next != NULL) {
		if (strcmp(temp->next->fname, first_name) == 0) {
			position to_delete = temp->next;
			temp->next = to_delete->next;
			free(to_delete);
			return;
		}
		temp = temp->next;
	}
}