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

char digitString[9][6] = {"one", "two",   "three", "four", "five",
                          "six", "seven", "eight", "nine"};

int findNumber(const char *str) {
  for (int i = 0; i < 9; i++) {

    if (strstr(str, digitString[i]) == str) {
        return i+1;
    }
  }
  return -1;
}

int main() {

  FILE *inputFile = fopen("input.txt", "r");

  char *inputLine = NULL;
  size_t lineLen = 0;
  size_t lineSize = 0;
  int lineNum = 0;

  LinkList *numList = newList();

  do { // Loop through input until we see "done"

    lineSize = getline(&inputLine, &lineLen, inputFile);
    lineNum++;

    int firstNumIndex = -1;
    int firstNum = 0;
    int lastNumIndex = -1;
    int lastNum = 0;

    for (int i = 0; i < lineSize; i++) { // Loop through the current line
      char *c = inputLine + i;

      int num;
      num = findNumber(c);
      if(num != -1){
          if(firstNumIndex == -1){
            firstNumIndex = i;
            firstNum = num;
          }

          if(lastNumIndex < i){
            lastNumIndex = i;
            lastNum = num;
          }

      }

      char singleChar[2];
      memcpy(singleChar, c, 1);
      num = atoi(singleChar);
      if (num != 0) { // If the string to int conversion succeeds
        if (firstNumIndex == -1) {
          firstNumIndex = i;
          firstNum = num;
        }

        if (lastNumIndex < i) {
          lastNumIndex = i;
          lastNum = num;
        }
      }
    }

    int newNum = (firstNum * 10) + lastNum;

    printf("%i: %i\n", lineNum, newNum);

    addLink(numList, newNum);
  } while (strcmp(inputLine, "done\n") != 0);

  int sumOfNumbers = 0;
  struct link *currLink = numList->root;

  while (currLink != NULL && currLink->next != NULL) {
    sumOfNumbers += currLink->number;
    currLink = currLink->next;
  }

  printf("Ans: %i\n", sumOfNumbers);

  freeList(numList);

  fclose(inputFile);

  return 0;
}
