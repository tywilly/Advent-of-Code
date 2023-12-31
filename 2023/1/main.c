#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct link {
  int number;
  struct link *next;
};

typedef struct ll {
  struct link *root;
} LinkList;

void freeList(LinkList *list) {
  struct link *curr = list->root;
  struct link *next = NULL;

  if (list == NULL)
    return;

  while (curr != NULL && curr->next != NULL) {
    next = curr->next;

    free(curr);

    curr = next;
  }

  free(list);
}

LinkList *newList() {
  LinkList *list = malloc(sizeof(LinkList));

  return list;
}

void addLink(LinkList *list, int number) {

  struct link *curr = list->root;

  if (list->root != NULL) {
    while (curr != NULL && curr->next != NULL) {
      curr = curr->next;
    }
    struct link *newLink = malloc(sizeof(struct link));

    newLink->number = number;
    curr->next = newLink;
    return;
  }

  struct link *newLink = malloc(sizeof(struct link));

  list->root = newLink;
  newLink->number = number;
}

int main() {

  FILE *inputFile = fopen("input.txt", "r");

  char *inputLine = NULL;
  size_t lineLen = 0;
  size_t lineSize = 0;

  LinkList *numList = newList();

  do { // Loop through input until we see "done"

    lineSize = getline(&inputLine, &lineLen, inputFile);

    int firstNumIndex = -1;
    int lastNumIndex = -1;

    for (int i = 0; i < lineSize; i++) { // Loop through the current line
      char *c = inputLine + i;

      int num = atoi(c);

      if (num != 0) { // If the string to int conversion succeeds
        if (firstNumIndex == -1) {
          firstNumIndex = i;
        }

        if (lastNumIndex < i) {
          lastNumIndex = i;
        }
      }
    }

    char newNumStr[2];
    newNumStr[0] = inputLine[firstNumIndex];
    newNumStr[1] = inputLine[lastNumIndex];
    int newNum = atoi(newNumStr);

    addLink(numList, newNum);
  } while (strcmp(inputLine, "done\n") != 0);

  int sumOfNumbers = 0;
  struct link *currLink = numList->root;

  while (currLink != NULL && currLink->next != NULL) {
    sumOfNumbers += currLink->number;
    currLink = currLink->next;
  }

  printf("%i\n", sumOfNumbers);

  freeList(numList);

  fclose(inputFile);

  return 0;
}
