#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int data;
  struct Node *next;
};

typedef struct Node node;

node *allocNode()
{
  node *newNode = (node *)malloc(sizeof(node));
  if (newNode == NULL)
  {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }
  return newNode;
}

node *createNode(int data)
{
  node *newNode = allocNode();
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

node *appendToList(node *root, node *nodeToAppend)
{
  if (root == NULL)
    return nodeToAppend;

  node *iterator = root;
  while (iterator->next != NULL)
    iterator = iterator->next;

  iterator->next = nodeToAppend;
  return root;
}

node *insertToList(node *root, node *nodeToInsert, int place)
{
  if (place < 0)
  {
    fprintf(stderr, "Invalid position\n");
    exit(1);
  }

  if (place == 0)
  {
    nodeToInsert->next = root;
    return nodeToInsert;
  }

  node *iterator = root;
  for (int index = 0; index < place - 1; ++index)
  {
    if (iterator == NULL || iterator->next == NULL)
      return appendToList(root, nodeToInsert);
    iterator = iterator->next;
  }
  nodeToInsert->next = iterator->next;
  iterator->next = nodeToInsert;
  return root;
}

void printList(node *root)
{
  node *iterator = root;
  while (iterator != NULL)
  {
    printf("%d\n", iterator->data);
    iterator = iterator->next;
  }
}

void freeList(node *root)
{
  node *iterator = root;
  while (iterator != NULL)
  {
    node *temp = iterator;
    iterator = iterator->next;
    free(temp);
  }
}

int main()
{
  node *root = createNode(1);

  root = insertToList(root, createNode(4), 4);
  root = appendToList(root, createNode(3));
  root = appendToList(root, createNode(5));
  root = insertToList(root, createNode(2), 2);

  printList(root);
  freeList(root);
  return 0;
}
