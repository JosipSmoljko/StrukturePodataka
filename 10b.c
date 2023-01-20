#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 1024
#define MAX_SIZE 128


struct _cvor;
typedef struct _cvor* position2;
typedef struct _cvor
{
	char ime[MAX_SIZE];
	int broj_stanovnika;
	position2 next;
}cvor;

struct _stablo;
typedef struct _stablo* position;
typedef struct _stablo
{
	char name[MAX_SIZE];
	position2 head;
	position left;
	position right;
}stablo;

int findCity(position2 head, int number);
position findCountry(position current, char* name, int number);
int readFile(char* name, position2 head);
int insertSorted(position2 newEl, position2 head);
int insertAfter(position2 before, position2 newEl);
int printList(position2 head);
position readFileTree(char* name, position root);
position insertToTree(position newEl, position current);
position createNewTreeElement(char* name);
int printTree(position current);
int compareCities(position2 newEl, position2 old);

int main()
{
	position root = NULL;
	char ime[MAX_SIZE] = { 0 };
	int broj;

	root = readFileTree("drzave.txt", root);

	printf("Unesite drzavu i broj stanovnika u toj drzavi: ");
	printf("\nDrzava: ");
	scanf("%s", ime);

	printf("Broj stanovnika: ");
	scanf("%d", &broj);

	findCountry(root, ime, broj);

	return 0;
}
int findCity(position2 head, int number)
{
	position2 temp = head->next;

	while (temp)
	{
		if (temp->broj_stanovnika >= number)
		{
			printf("%s  Broj stanovnika: %d\n", temp->ime, temp->broj_stanovnika);
		}
		temp = temp->next;
	}

	return 0;
}
position findCountry(position current, char* name,int number)
{
	if (current == NULL)
	{
		printf("Nema drzave u datoteci!\n");
		return NULL;
	}

	else if (strcmp(current->name, name) < 0)
		current->right = findCountry(current->right, name,number);

	else if (strcmp(current->name, name) > 0)
		current->left = findCountry(current->left, name,number);

	else
	{
		printf("Gradovi s vecom populacijom su:\n");
		findCity(current->head,number);
	}

	return current;
}

position readFileTree(char* name, position root)
{
	char buffer[MAX_LINE] = { 0 };
	FILE* pfile = NULL;
	pfile = fopen(name, "r");
	if (!pfile)
	{
		printf("Failed opening of the file!\n");
		return NULL;
	}

	while (!feof(pfile))
	{
		char country[MAX_SIZE] = { 0 };
		char ime[MAX_SIZE] = { 0 };
		position newEl = NULL;

		fgets(buffer, MAX_SIZE, pfile);
		if (sscanf(buffer, " %s %s", country, ime) == 2)
		{
			newEl = createNewTreeElement(country);
			readFile(ime, newEl->head);
			root = insertToTree(newEl, root);
		}
	}
	fclose(pfile);
	return root;
}
int readFile(char* name, position2 head)
{
	char buffer[MAX_LINE] = { 0 };
	FILE* pfile = NULL;

	pfile = fopen(name, "r");
	if (!pfile)
	{
		printf("Failed opening of the file!\n");
		return -1;
	}

	while (!feof(pfile))
	{
		position2 newEl = NULL;
		newEl = (position2)malloc(sizeof(cvor));
		if (!newEl)
		{
			perror("Failed allocation");
			return -1;
		}

		fgets(buffer, MAX_SIZE, pfile);
		if (sscanf(buffer, " %s %d", newEl->ime, &newEl->broj_stanovnika) == 2)
		{
			insertSorted(newEl, head);
		}
	}
	fclose(pfile);
	return 0;
}
int insertSorted(position2 newEl, position2 head)
{
	position2 temp = head;
	while (temp->next != NULL && compareCities(newEl,temp->next)<0)
	{
		temp = temp->next;
	}
	insertAfter(temp, newEl);

	return 0;
}
int compareCities(position2 newEl, position2 old)
{
	int result=newEl->broj_stanovnika-old->broj_stanovnika;

	if (newEl->broj_stanovnika == old->broj_stanovnika)
	{
		result = (strcmp(old->ime, newEl->ime) < 0);
	}
		return  result;
}
int insertAfter(position2 before, position2 newEl)
{
	newEl->next = before->next;
	before->next = newEl;

	return 0;
}
int printList(position2 head)
{
    position2 temp = head->next;
	while (temp != NULL)
	{
		printf("%s %d\n", temp->ime, temp->broj_stanovnika);
		temp = temp->next;
	}
	return 0;
}
position insertToTree(position newEl, position current)
{
	if (current == NULL)
	{
		return newEl;
	}
	else if (strcmp(current->name, newEl->name) > 0)
	{
		current->left = insertToTree(newEl, current->left);
	}
	else if (strcmp(current->name, newEl->name) < 0)
	{
		current->right = insertToTree(newEl, current->right);
	}
	else
		free(newEl);

	return current;
}
position createNewTreeElement(char* name)
{
	position newEl = NULL;

	newEl = (position)malloc(sizeof(stablo));
	if (!newEl)
	{
		perror("Failed allocation!\n");
		return NULL;
	}

	strcpy(newEl->name, name);
	newEl ->head = (position2)malloc(sizeof(cvor));
	if (!newEl)
	{
		perror("Failed allocation!\n");
		return NULL;
	}
	newEl->head->next = NULL;
	newEl->left = NULL;
	newEl->right = NULL;

	return newEl;
}
int printTree(position current)
{
	if (NULL == current)
		return 0;

	printTree(current->left);
	printf("\n%s\n", current->name);
	printList(current->head);
	printTree(current->right);

	return 0;
}
