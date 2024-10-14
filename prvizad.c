#define _CRT_SECURE_NO_WARNINGS
#define ERROR_OPENING_FILE 1
#define ERROR_ALLOCATTING_MEMORY 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024


int broj_redova(char* filename);
void spremanje(char* filename, int row_count, struct Studenti* student);

struct Studenti
{
	char ime[20];
	char prezime[20];
	int bodovi;

};

int main() {
	int n = 0;
	int i = 0;
	char* filename = "imenik.txt";
	n = broj_redova(filename);
	if (n <= 0) {
		printf("No rows found or error in counting rows.\n");
		return n;
	}
	struct Studenti* student = malloc(n * sizeof(struct Studenti));
	if (student == NULL) {
		printf("greska u alokaciji");
		return ERROR_ALLOCATTING_MEMORY;

	}
	spremanje(filename, n, student);


	for (i = 0; i < n; i++) {
		printf("%s\t%s\t%d\n", student[i].ime, student[i].prezime, student[i].bodovi);
	}
	return 0;

}
int broj_redova(char* filename) {
	FILE* fp = NULL;
	char buffer[BUFFER_SIZE];
	int row_counter = 0;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error opening file\n");
		return ERROR_OPENING_FILE;
	}
	while (!feof(fp)) {
		fgets(buffer, BUFFER_SIZE, fp);
		//sscanf() doma napravi mozda
		++row_counter;
	}

	fclose(fp);
	return row_counter;
}
void spremanje(char* filename, int row_count, struct Studenti* student) {
	int i = 0;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("error opening file\n");
		return;
	}
	for (int i = 0; i < row_count; i++) {
		fscanf(fp, "%s", student[i].ime);
		fscanf(fp, "%s", student[i].prezime);
		fscanf(fp, "%d", &student[i].bodovi);
	}
	fclose(fp);
}