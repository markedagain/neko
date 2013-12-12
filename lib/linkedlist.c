#include <stdlib.h>
#include "linkedlist.h"

LIST *list_create(void) {
  LIST *list;
  if (!(list = malloc(sizeof(LIST))))
    return NULL;
  list->first = NULL;
  list->last = NULL;
  list->count = 0;
  return list;
}

LIST_NODE *list_create_node(void *data) {
  LIST_NODE *node;
  if (!(node = malloc(sizeof(LIST_NODE))))
    return NULL;
  node->data = data;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

LIST_NODE *list_insert_end(LIST *list, void *data) {
  LIST_NODE *node;
  if (list == NULL)
    return NULL;
  if (!(node = list_create_node(data)))
    return NULL;
  if (list->count == 0)
    list->first = node;
  else {
    list->last->next = node;
    node->prev = list->last;
  }
  list->last = node;
  list->count++;
  return node;
}

LIST_NODE *list_insert_after(LIST *list, LIST_NODE *node, void *data) {
  LIST_NODE *newNode;
  if (list == NULL)
    return NULL;
  newNode = list_create_node(data);
  newNode->next = node->next;
  newNode->prev = node;
  if (node->next == NULL)
    list->last = newNode;
  else
    node->next->prev = newNode;
  node->next = newNode;
  list->count++;
  return newNode;
}

LIST_NODE *list_insert_before(LIST *list, LIST_NODE *node, void *data) {
  LIST_NODE *newNode;
  if (list == NULL)
    return NULL;
  newNode = list_create_node(data);
  newNode->prev = node->prev;
  newNode->next = node;
  if (node->prev == NULL)
    list->first = newNode;
  else
    node->prev->next = newNode;
  node->prev = newNode;
  list->count++;
  return newNode;
}

LIST_NODE *list_insert_beginning(LIST *list, void *data) {
  LIST_NODE *newNode;
  if (list == NULL)
    return NULL;
  newNode = list_create_node(data);
  newNode->next = list->first;
  if (list->first != NULL)
    list->first->prev = newNode;
  list->first = newNode;
  list->count++;
  return newNode;
}

void *list_remove(LIST *list, LIST_NODE *node) {
  void *data;
  if (node == NULL)
    return NULL;
  
  if (node->prev == NULL)
    list->first = node->next;
  else
    node->prev->next = node->next;
  if (node->next == NULL)
    list->last = node->prev;
  else
    node->next->prev = node->prev;
  
  data = node->data;
  free(node);
  list->count--;
  return data;
}

void list_remove_free(LIST *list, LIST_NODE *node) {
  free(list_remove(list, node));
}

void list_empty(LIST *list) {
  LIST_NODE *node;
  if (list == NULL)
    return;
  node = list->last;
  while (node) {
    list_remove(list, node);
    node = list->last;
  }
  list->last = NULL;
  list->first = NULL;
}

void list_destroy(LIST *list) {
  if (list == NULL)
    return;
  list_empty(list);
  free(list);
  list = NULL;
}

int list_foreach(LIST *list, int(*func)(void *)) {
  LIST_NODE *node;
  if (list == NULL)
    return -1;
  node = list->first;
  while (node) {
    if (func(node->data) != 0)
      return -1;
    node = node->next;
  }
  return 0;
}

LIST_NODE *list_find(LIST *list, int(*func)(void *, void *), void *data) {
  LIST_NODE *node;
  if (list == NULL)
    return NULL;
  node = list->first;
  while (node) {
    if (func(node->data, data) > 0)
      return node;
    node = node->next;
  }
  return NULL;
}
