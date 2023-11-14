#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 1024
#define MAX_SIZE 128

struct _tree;
typedef struct _tree* position;
typedef struct _tree
{
  	char name[MAX_SIZE];
  	int population;
  	position left;
  	position right;
}tree;


struct _lista;
typedef struct _lista* position2;
typedef struct _lista
{
  	char ime[MAX_SIZE];
  	position root;
  	position2 next;
}lista;

int countryFind(position2 head, char* country, int number);
int readFile(char* name, position2 head);
int insertSorted(position2 newEl, position2 head);
int insertAfter(position2 before, position2 newEl);
int printList(position2 first);
position readFileForTree(char* name, position root);
position insertToTree(position newEl, position current);
position createNewTreeElement(char* name, int number);
int printTree(position current);
position cityFind(position current, int number);

int main()
{
  	lista head = { .ime = { 0 },.root = NULL,.next = NULL };
	position2 p = &head;
	char ime[MAX_SIZE] = { 0 };
	int number;
	readFile("drzave.txt", p);


  	printf("Unesite drzavu i broj stanovnika u toj drzavi: ");
  	printf("\nDrzava: ");
  	scanf(" %s",ime);

  	printf("Broj stanovnika: ");
  	scanf("%d", &number);

	countryFind(p, ime, number);

  	return 0;
}

int readFile(char* name, position2 head)
{
  	char buffer[MAX_LINE] = { 0 };
	char ime[MAX_LINE] = { 0 };
	FILE* fp = NULL;

  	fp = fopen(name, "r");
  	if (!fp)
	  {
	    	printf("Nemoguce otvaranje datoteke!\n");
	    	return -1;
	  }

  	while (!feof(fp))
	  {
	    	position2 newEl = NULL;
	    	newEl = (position2)malloc(sizeof(lista));
	    	if (!newEl)
		    {
		         perror("Neuspjela alokacija");
			       return -1;
	     	}

	    	fgets(buffer, MAX_SIZE, fp);

		if (sscanf(buffer, " %s %s", newEl->ime, ime) == 2)
	    	{
		       	newEl->root = NULL;
			      newEl->root = readFileForTree(ime, newEl->root);
		      	insertSorted(newEl, head);
		 }
   	}
  	fclose(fp);
  	return 0;
}

position readFileForTree(char* name, position root)
{
	  char buffer[MAX_LINE] = { 0 };
	  FILE* pfile = NULL;
  	  pfile = fopen(name, "r");
	  if (!pfile)
	  {
		     printf("Nemoguce otvaranje datoteke!\n");
		     return NULL;
	  }

  	  while (!feof(pfile))
	  {
		    int number;
		    char country[MAX_SIZE] = { 0 };
		    position newEl = NULL;

	    	    fgets(buffer, MAX_SIZE, pfile);
		    if (sscanf(buffer, " %s %d", country, &number) == 2)
		    {
			       newEl = createNewTreeElement(country, number);
			       root = insertToTree(newEl, root);
		    }
	   }
	   fclose(pfile);
	   return root;
}

int insertSorted(position2 newEl, position2 head)
{
	    position2 temp = head;

	    while (temp->next != NULL && strcmp(temp->next->ime, newEl->ime) < 0)
		  temp = temp->next;

    	    insertAfter(temp, newEl);

	    return 0;
}

int insertAfter(position2 before, position2 newEl)
{
	    newEl->next = before->next;
	    before->next = newEl;

	    return 0;
}

int printList(position2 first)
{
	    while (first)
	    {
		      printf("\nIme:%s\nGradovi:\n", first->ime);
		      if (first->root)
		    	    printTree(first->root);

		      else
		        	printf("Nema gradova!\n");

		      first = first->next;
	    }

	    return 0;
}

position insertToTree(position newEl, position current)
{
	    if (current == NULL)
		       return newEl;

            else if (current->population < newEl->population)
		      current->right = insertToTree(newEl, current->right);

	    else if (current->population > newEl->population)
            current->left = insertToTree(newEl, current->left);

	    else
	    {
		       if (strcmp(current->name, newEl->name) < 0)
			          current->right = insertToTree(newEl, current->right);

		       else if (strcmp(current->name, newEl->name) > 0)
			          current->left = insertToTree(newEl, current->left);

            else
			          free(newEl);
	     }

	    return current;
}

position createNewTreeElement(char* name, int number)
{
	 position newEl = NULL;

	 newEl = (position)malloc(sizeof(tree));

      	if (!newEl)
    	{
		  perror("Neuspjela alokacija!\n");
		  return NULL;
	  }

    	strcpy(newEl->name, name);
    	newEl->population = number;
	newEl->left = NULL;
	newEl->right = NULL;

	return newEl;
}

int printTree(position current)
{
	 if (NULL == current)
		    return 0;

	 printTree(current->left);
	 printf("%s %d\n", current->name, current->population);
	 printTree(current->right);

	 return 0;
}
int countryFind(position2 head, char* country, int number)
{
	  position2 temp = head->next;

	  while (temp != NULL && strcmp(country, temp->ime) != 0)
	  	  temp = temp->next;

	  if (temp)
	  {
      		  printf("Gradovi koji imaju vecu populaciju: \n");
		  temp->root = cityFind(temp->root, number);
	}

	  else
		   printf("Drzava ne postoji u datoteci!\n");

	  return 0;
}
position cityFind(position current, int number)
{
	  if (current == NULL)
		    return NULL;

   	  else if (current->population >= number){
		    current->left = cityFind(current->left, number);
		    printf("Ime:%s  Broj stanovnika: %d\n", current->name, current->population);
		    current->right = cityFind(current->right, number);
	  }

	 else if (current->population < number)
		    current->right = cityFind(current->right, number);

	return current;
}
