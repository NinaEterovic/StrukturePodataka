#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define FILE_OPEN_ERROR 1
#define EXIT_SUCCESS 0;

typedef struct _binTree* position;
typedef struct _binTree
{
	int el;
	position left, right;
}binTree;

position insert_element(position root, int element);
position create_root(int element);
int inorder(position root);
int inorder_in_file(position root, FILE* fp);
int replace(position root);

int main()
{
	position root = NULL;
	int i;

	FILE* fp = NULL;
	fp = fopen("ispis_in_order.txt", "w");
	if (fp == NULL) {
		return FILE_OPEN_ERROR;
	}
	srand(time(NULL));

	//int elements[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	//int n = sizeof(elements) / sizeof(elements[0]);
	//for (int i = 0; i < n; i++) root = insert_element(root, elements[i]);

	for (i = 0; i < 10; i++) {
		int r = rand() % (90 + 1 - 10) + 10;
		printf("%d ", r);
		root= insert_element(root, r);

	}
	printf("\n");
	inorder(root);
	inorder_in_file(root, fp);
	fprintf(fp, "\n");
	printf("\n");
	replace(root);
	inorder(root);
	inorder_in_file(root, fp);








	return 0;
}

position insert_element(position root, int element) {
	if (!root) return create_root(element);

	if (element >= root->el)
		root->left = insert_element(root->left, element);
	else if (element < root->el)
		root->right = insert_element(root->right, element);

	return root;

}

position create_root(int element)
{
	position new = (position)malloc(sizeof(binTree));
	if (!new)
	{
		printf("Memory allocation error in create_root!\n");
		return NULL;
	}

	new->el = element;
	new->left = new->right = NULL;

	return new;
}
int inorder(position root)
{
	if (root)
	{
		inorder(root->left);
		printf("%d ", root->el);
		inorder(root->right);
	}

	return EXIT_SUCCESS;
}

int replace(position root)
{
	if (!root) return 0; 

	int left_sum = replace(root->left);
	int right_sum = replace(root->right);
	int old_value = root->el;

	root->el = left_sum + right_sum;

	return root->el + old_value;
}

int inorder_in_file(position root, FILE* fp)
{

	if (root)
	{
		inorder_in_file(root->left,fp);
		fprintf(fp,"%d ", root->el);
		inorder_in_file(root->right,fp);
	}

	return EXIT_SUCCESS;
}
