#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS
#define EXIT_SUCCESS 1
#define BUFFER_SIZE 1024

typedef struct _person* position;
typedef struct _person {
	char fname[20];
	char lname[20];
	int byear;

	position next;

}person;


position create_person(char* firstname, char* lastname, int birthyear);
position find_by_lname(position head, char* last_name);
position find_by_fname(position head, char* first_name);
position find_person_before(position head, char* first_name);

int print_list(position head);
int print_person(position person1);

int append(position head, char* firstname, char* lastname, int birthyear);
int prepend(position head, char* firstname, char* lastname, int birthyear);
int add_person_after(position head, char* before_person_fname);
int add_person_before(position head, char* after_person_fname);

void delete_person(position head, char* first_name);
void copy_list_to_file(position head);
void read_list_from_file(position head);

int main() {
	char lname1[20];
	char fname1[20];
	char firstname[20];
	char lastname[20];
	int birthyear;
	int ans;


	position head = (position)malloc(sizeof(person));
	if (head == NULL) {
		printf("Error allocating memory\n");
		return -1;
	}

	strcpy(head->fname, "");
	strcpy(head->lname, "");
	head->byear = 0;
	head->next = NULL;
	printf(
		"(1) Print list\n"
		"(2) Add person to the beginning of the list\n"
		"(3) Add person to the end of the list\n"
		"(4) Find person by last name\n"
		"(5) Delete person by entering first name\n"
		"(6) Add person after a specific person in the list\n"
		"(7) Add person before a specific person in the list\n"
		"(8) Copy the list into the file\n"
		"(9) Read the list from the file\n"
		"(0) Exit\n");
	do {
		printf("\nEnter the number associated to the action you want to do\n");
		scanf("%d", &ans);

		switch (ans)
		{
		case 0:
			break;
		case 1:
			print_list(head);
			break;
		case 2:
			printf("Enter the first name, last name and birthyear of a person you want to add to the BEGINNING of the list\n");
			scanf("%s %s %d", firstname, lastname, &birthyear);
			prepend(head, firstname, lastname, birthyear);
			break;
		case 3:
			printf("Enter the first name, last name and birthyear of a person you want to add to the END of the list\n");
			scanf("%s %s %d", firstname, lastname, &birthyear);
			append(head, firstname, lastname, birthyear);
			break;
		case 4:
			printf("\nEnter the last name of the person you want to find\n");
			scanf("%s", lname1);
			position last_person = find_by_lname(head, lname1);
			print_person(last_person);
			break;
		case 5:
			printf("\nEnter the first name of the person you want to delete\n");
			scanf("%s", &fname1);
			delete_person(head, fname1);
			break;
		case 6:
			printf("\nEnter the first name of the person after whom you want to add a person\n");
			scanf("%s", fname1);
			add_person_after(head, fname1);
			break;
		case 7:
			printf("\nEnter the first name of the person before whom you want to add a person\n");
			scanf("%s", fname1);
			add_person_before(head, fname1);
			break;
		case 8:
			copy_list_to_file(head);
		case 9:
			read_list_from_file(head);
		default:
			break;
		}

	} while (ans != 0);


	position temp = head->next;
	while (temp != NULL) {
		position to_free = temp;
		temp = temp->next;
		free(to_free);
	}
	free(head);

	return 0;
}

position create_person(char* firstname, char* lastname, int birthyear) {
	position new_person = NULL;
	new_person = (person*)malloc(sizeof(person));
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
	//printf("\nlist looks like this: \n");
	printf("\nFirst Name:\tLast Name:\tBirth year:\n");
	while (temp != NULL) {
		printf("%s\t\t%s\t\t%d\n", temp->fname, temp->lname, temp->byear);
		temp = temp->next;

	}
	return EXIT_SUCCESS;
}

int print_person(position person1) {
	if (person1 == NULL) {
		printf("no person with such last name");
	}
	else {
		printf("First name: %s\nLast name: %s\nBirth Year: %d\n", person1->fname, person1->lname, person1->byear);
	}

	return EXIT_SUCCESS;
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

position find_by_fname(position head, char* first_name) {
	position temp = head->next;
	while (temp != NULL) {
		if (strcmp(temp->fname, first_name) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;

}

position find_person_before(position head, char* first_name) {
	position temp = head;
	while (temp->next != NULL) {
		if (strcmp(temp->next->fname, first_name) == 0) {
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

int add_person_after(position head, char* before_person_fname) {
	char firstname[20];
	char lastname[20];
	int birthyear;

	printf("\nEnter the first name, last name and birthyear of the person you want to add \n");
	scanf("%s %s %d", firstname, lastname, &birthyear);

	position new_person = create_person(firstname, lastname, birthyear);
	position before_person = find_by_fname(head, before_person_fname);
	new_person->next = before_person->next;
	before_person->next = new_person;

	return EXIT_SUCCESS;

}

int add_person_before(position head, char* after_person_fname) {
	char firstname[20];
	char lastname[20];
	int birthyear;

	printf("\nEnter the first name, last name and birthyear of the person you want to add \n");
	scanf("%s %s %d", firstname, lastname, &birthyear);

	position new_person = create_person(firstname, lastname, birthyear);
	position after_person = find_by_fname(head, after_person_fname);
	position before_person = find_person_before(head, after_person->fname);
	new_person->next = after_person;
	before_person->next = new_person;

	return EXIT_SUCCESS;

}

void copy_list_to_file(position head) {
	char* filename = "lista.txt";
	FILE* fp = NULL;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("\nerorr opening file\n");
		return;
	}
	position temp = head->next;
	fprintf(fp, "First Name:\tLast Name:\tBirth year:\n");
	while (temp != NULL) {
		fprintf(fp, "%s\t\t%s\t\t%d\n", temp->fname, temp->lname, temp->byear);
		temp = temp->next;
	}
	fclose(fp);
	printf("Successfully copied list to a file\n");
}

void read_list_from_file(position head) {
	char firstname[20];
	char lastname[20];
	int birthyear;

	char* filename = "lista.txt";
	FILE* fp = NULL;
	char buffer[BUFFER_SIZE];
	int row_counter = 0;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("\nerorr opening file\n");
		return;
	}

	while (fscanf(fp, "%s %s %d", firstname, lastname, &birthyear) == 3)
		append(head, firstname, lastname, birthyear);

	fclose(fp);
	printf("Successfully copied data from a file to the list\n");
}