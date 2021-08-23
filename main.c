#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

//struct for contact
typedef struct
{
	char firstName[15];
	char lastName[15];
	char number[15];
	char group[10];
}contact;

//element of list
typedef struct
{
	struct element* previous;
	contact data;
	struct element* next;
}element;

//read contacts from csv file and form list
element* readFile(element* first, element* last)
{
	first = NULL;
	last = NULL;

	char* name = malloc(25*sizeof(char));
	char fname[30];
	char line[60];

	element* newElement;
	
	while (1)
	{
		printf("Podaj nazwę pliku z kontaktami do wczytania (bez rozszerzenia): ");
		scanf("%s", name);
		sprintf(fname, "%s.csv", name);
		FILE* file;
		if (file = fopen(fname, "r"))
		{
			fopen(fname, "r");
			while (!feof(file))
			{

				fscanf(file, "%s", line);				

				newElement = malloc(sizeof(element));
				newElement->previous = NULL;
				newElement->next = NULL;

				
				sscanf(line, "%[^;] ; %[^;] ; %[^;] ; %s", newElement->data.firstName, newElement->data.lastName, newElement->data.number, newElement->data.group);

				if (first == NULL) {
					first = newElement;
				}

				if (last == NULL) {
					last = newElement;
				} else {
					last->next = newElement;
					newElement->previous = last;
					last = last->next;
				}
			}
			fclose(file);
			break;
		}
		else
		{
			printf("\n!> Plik nie istnieje <!");
			Sleep(1000);
			system("CLS");
		}
	}
	printf("\nWczytano pomyślnie!\n");

	free(name);

	return first;
}

//check if list empty
int isEmpty(element* first)
{
	if (first == NULL)
	{
		printf("\n!> Lista kontaktów jest pusta <!\n");
		return 1;
	}
}

//print list in console
int printList(element* first, int index) 
{
	if(isEmpty(first) == 1)
	{
		return;
	}

	index = 0;
	element* current = first;

	printf("___________________________________________________________________\n");
	printf("POZ.            IMIĘ I NAZWISKO      |       NUMER TEL.|      GRUPA\n");
	printf("_____________________________________|_________________|___________\n");
	while(current != NULL) 
	{
		index = index++;
		printf("%3d. %15s %15s | %15s | %10s\n", index, current->data.firstName, current->data.lastName, current->data.number, current->data.group);
		current = current->next;
	}

	return index;
}

//clear list
void clearList(element* first) 
{
	element* current = first;
	element* next;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

//sorts list by firstName
void sortByFirstName(element* first, element* last)
{
	int swapped, i;
	element* current;
	last = NULL;
	element tmp;

	if (first == NULL) {
		return;
	}

	do
	{
		swapped = FALSE;
		current = first;

		while (current->next != last)
		{
			element* next = current->next;
			if (strcoll(current->data.firstName, next->data.firstName) == 1) // first is greater
			{
				tmp.data = current->data;
				current->data = next->data;
				next->data = tmp.data;
				swapped = TRUE;
			}
			current = next;
		}
		last = current;
	} while (swapped);
}

//sorts list by lastName
void sortByLastName(element* first, element* last)
{
	int swapped, i;
	element* current;
	last = NULL;
	element tmp;

	do
	{
		swapped = FALSE;
		current = first;

		while (current->next != last)
		{
			element* next = current->next;
			if (strcoll(current->data.lastName, next->data.lastName) == 1) // first is greater
			{
				tmp.data = current->data;
				current->data = next->data;
				next->data = tmp.data;
				swapped = TRUE;
			}
			current = next;
		}
		last = current;
	} while (swapped);
}

//sorts list by group
void sortByGroup(element* first, element* last)
{
	int swapped, i;
	element* current;
	last = NULL;
	element tmp;

	do
	{
		swapped = FALSE;
		current = first;

		while (current->next != last)
		{
			element* next = current->next;
			if (strcoll(current->data.group, next->data.group) == 1) // first is greater
			{
				tmp.data = current->data;
				current->data = next->data;
				next->data = tmp.data;
				swapped = TRUE;
			}
			current = next;
		}
		last = current;
	} while (swapped);
}

//selects a sort method
int sortList(element* first, element* last, int sorted)
{
	char input;
	int x;

	if (isEmpty(first) == 1)
	{
		return;
	}

	while (1)
	{
		system("CLS");
		printf("Wybierz odnośnik sortowania: [i] - imię, [n] - nazwisko, [g] - grupa: ");
		scanf(" %c", &input);
		if (input == 'i' || input == 'I')
		{
			sortByFirstName(first, last);
			printf("\nSortowanie przebiegło pomyślnie.\n");
			return sorted = 1;
			break;
		}
		else if (input == 'n' || input == 'N')
		{
			sortByLastName(first, last);
			printf("\nSortowanie przebiegło pomyślnie.\n");
			return sorted = 2;
			break;
		}
		else if (input == 'g' || input == 'G')
		{
			sortByGroup(first, last);
			printf("\nSortowanie przebiegło pomyślnie.\n");
			return sorted = 3;
			break;
		}
		else
		{
			printf("\nWybrano niepoprawną metodę sortowania\n\n");
			Sleep(1000);
		}
	}
}

//put new element as first
void putFirst(element* newContact, element* first)
{
	newContact->next = first;
	if (first != NULL)
	{
		first->previous = newContact;
	}
}

//put new element in alphabetical order by first name
void putByFirstName(element* newContact, element* first, element* last)
{
	element* current = first;
	element* previous = current->previous;

	while (current != NULL)
	{	
		if (strcoll(current->data.firstName, newContact->data.firstName) == 1)
		{
			newContact->next = current;
			newContact->previous = previous;
			current->previous = newContact;
			if (previous != NULL) {
				previous->next = newContact;
			}
			return;
		}
		previous = current;
		current = current->next;
	}

	//now previous points to the last element in the list or is NULL
	if (previous != NULL) {
		previous->next = newContact;
		newContact->previous = previous;
		last = newContact;
	}
}

//put new element in alphabetical order by last name
void putByLastName(element* newContact, element* first, element* last)
{
	element* current = first;
	element* previous = current->previous;

	while (current != NULL)
	{
		if (strcoll(current->data.lastName, newContact->data.lastName) == 1)
		{
			newContact->next = current;
			newContact->previous = previous;
			current->previous = newContact;
			if (previous != NULL) {
				previous->next = newContact;
			}
			return;
		}
		previous = current;
		current = current->next;
	}

	//now previous points to the last element in the list or is NULL
	if (previous != NULL) {
		previous->next = newContact;
		newContact->previous = previous;
		last = newContact;
	}
}

//put new element in alphabetical order by group
void putByGroup(element* newContact, element* first, element* last)
{
	element* current = first;
	element* previous = current->previous;

	while (current != NULL)
	{
		if (strcoll(current->data.group, newContact->data.group) == 1)
		{
			newContact->next = current;
			newContact->previous = previous;
			current->previous = newContact;
			if (previous != NULL) {
				previous->next = newContact;
			}
			return;
		}
		previous = current;
		current = current->next;
	}

	//now previous points to the last element in the list or is NULL
	if (previous != NULL) {
		previous->next = newContact;
		newContact->previous = previous;
		last = newContact;
	}
}

//puts new contact with specific order
element* putNewContact(element* newContact, element* first, element* last, int sorted)
{
	if (first == NULL) {
		last = newContact;
		return newContact;
	}

	if (sorted == 1)
	{
		if (strcoll(first->data.firstName, newContact->data.firstName) == 1) {
			putFirst(newContact, first);
			return newContact;
		}
		else {
			putByFirstName(newContact, first, last);
			return first;
		}
	}
	else if (sorted == 2)
	{
		if (strcoll(first->data.lastName, newContact->data.lastName) == 1) {
			putFirst(newContact, first);
			return newContact;
		}
		else {
			putByLastName(newContact, first, last);
			return first;
		}
	}
	else if (sorted == 3)
	{
		if (strcoll(first->data.group, newContact->data.group) == 1) {
			putFirst(newContact, first);
			return newContact;
		}
		else {
			putByGroup(newContact, first, last);
			return first;
		}
	}
	else
	{
		putFirst(newContact, first);
		return newContact;
	}
}

//create new contact and add it to list
element* addContact(element* first, element* last, int sorted)
{
	element* newElement = malloc(sizeof(element));

	printf("Wprowadź wymagane dane do utworzenia kontaktu\n\n");
	while (1)
	{
		printf("Imię: ");
		scanf("%s", newElement->data.firstName);
		if (strlen(newElement->data.firstName) > 15)
		{
			printf("\n > Imię może mieć maksymalnie 15 liter <\n\n");
		}
		else
		{
			break;
		}
	}
	while (1)
	{
		printf("Nazwisko: ");
		scanf("%s", newElement->data.lastName);
		if (strlen(newElement->data.lastName) > 15)
		{
			printf("\n > Nazwisko może mieć maksymalnie 15 liter <\n\n");
		}
		else
		{
			break;
		}
	}
	while (1)
	{
		printf("Numer: ");
		scanf("%s", newElement->data.number);
		if (strlen(newElement->data.number) > 15)
		{
			printf("\n > Numer może mieć maksymalnie 15 cyfr <\n\n");
		}
		else
		{
			break;
		}
	}
	while (1)
	{
		printf("Grupa: ");
		scanf("%s", newElement->data.group);
		if (strlen(newElement->data.group) > 10)
		{
			printf("\n > Grupa może mieć maksymalnie 10 liter <\n\n");
		}
		else
		{
			break;
		}
	}

	newElement->next = NULL;
	newElement->previous = NULL;

	printf("\nKontakt dodano pomyślnie.\n");

	return putNewContact(newElement, first, last, sorted);
}

//find string by search in string
char* stristr(const char* strToS, const char* strToF)
{
	char strToS_Up[15];
	char strToF_Up[15];

	strcpy(strToS_Up, strToS);
	strcpy(strToF_Up, strToF);

	_strupr(strToS_Up);
	_strupr(strToF_Up);

	strstr(strToS_Up, strToF_Up);
}

//find exact contact
void find(element* first) 
{
	if (isEmpty(first) == 1)
	{
		return;
	}

	element* current = first;
	char* prefix = malloc(15*sizeof(char));

	system("CLS");
	printf("Wprowadź fragment imienia lub nazwiska: ");
	scanf("%s", prefix);

	while (current != NULL)
	{
		if (stristr(current->data.firstName, prefix))
		{
			printf("imię i nazwisko: %15s %15s, nr: %15s, grupa: %s\n", current->data.firstName, current->data.lastName, current->data.number, current->data.group);
		}
		else if (stristr(current->data.lastName, prefix))
		{
			printf("imię i nazwisko: %15s %15s, nr: %15s, grupa: %s\n", current->data.firstName, current->data.lastName, current->data.number, current->data.group);
		}
		current = current->next;
	}

	free(prefix);
}

//print contacts related to exact group
void printGroup(element* first) 
{
	if (isEmpty(first) == 1)
	{
		return;
	}

	element* current = first;
	char* prefix = malloc(10*sizeof(char));

	printf("Wprowadź fragment nazwy grupy: ");
	scanf("%s", prefix);
	while (current != NULL)
	{
		if (stristr(current->data.group, prefix) != 0)
		{
			printf("imię i nazwisko: %20s %20s, nr: %20s, grupa: %s\n", current->data.firstName, current->data.lastName, current->data.number, current->data.group);
		}
		current = current->next;
	}

	free(prefix);
}

//delete first element of list
element* delFirst(element* first)
{
	element* del = first;
	first = first->next;
	if (first != NULL)
	{
		first->previous = NULL;
	}

	free(del);

	return first;
}

//delete last element of list
void delLast(element* first, element* last)
{
	last = first;

	while (last->next != NULL)
	{
		last = last->next;
	}
	
	element* del = last;
	last = last->previous;

	if (last != NULL)
	{
		last->next = NULL;
	}

	free(del);
}

//delete n element from list
element* delN(element* first, element* last, int index) 
{
	if (isEmpty(first) == 1)
	{
		return;
	}

	element* current;
	
	int pos;

	current = first;

	element* prev;  
	element* nxt; 

	while (1)
	{
		system("CLS");

		printList(first, index);

		printf("\nWprowadź pozycję do usunięcia: ");
		scanf("%d", &pos);

		if (pos == 1)
		{
			first = delFirst(first);
			break;
		}
		else if (pos == index)
		{
			delLast(first, last);
			break;
		}
		else if (pos > 1 && pos < index)
		{
			for (int i = 1; i < pos; i++)
			{
				current = current->next;
			}
			prev = current->previous;
			nxt = current->next;
			prev->next = current->next;
			nxt->previous = current->previous;

			free(current);

			break;
		}
		else
		{
			printf("\n!> Nie ma takiej pozycji <!");
			Sleep(1000);
		}
	}
	printf("\nZ powodzeniem usunięto pozycję numer: %d\n", pos);

	return first;
} 

//entry function
void main()
{
	element* first = NULL;
	element* last = NULL;
	int sorted = 0;
	int index = 0;

	setlocale(LC_ALL, "Polish");

	int end = 1;
	int x;
	
	while (1)
	{
		system("CLS");
		printf("KONTAKTY\n");
		printf("1. Wczytaj kontakty z pliku\n");
		printf("2. Wyświetl listę kontaktów\n");
		printf("3. Sortuj kontakty\n");
		printf("4. Dodaj nowy kontakt\n");
		printf("5. Wyszukaj kontakt\n");
		printf("6. Wyœwietl grupę kontaktów\n");
		printf("7. Usuń kontakt\n");
		printf("0. Wyjście\n\n");

		scanf("%d", &x);
		system("CLS");
		switch (x)
		{
			case 1:
				clearList(first);
				first = readFile(first, last);
				break;
			case 2:
				index = printList(first, index);
				break;
			case 3:
				sorted = sortList(first, last, sorted);
				break;
			case 4:
				first = addContact(first, last, sorted);
				break;
			case 5:
				find(first);
				break;
			case 6:
				printGroup(first);
				break;
			case 7:
				first = delN(first, last, index);
				break;
			case 0:
				clearList(first);
				break;
			default:
				system("CLS");
				printf("Brak takiej opcji\n");
				break;
		}
		printf("\nWciśnij [Enter], aby kontynuować\n");
		getchar();
		while (getchar() != '\n');
	}
}