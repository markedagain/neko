/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

/** @file   linkedlist.c
 *  @brief  Contains functions for manipulating linked lists and list nodes.
 */

#include <stdlib.h>
#include "linkedlist.h"

/**
 *  @brief  Creates a new linked list.
 *  @return Pointer to the newly-created list.
 */
LIST *list_create(void) {
  LIST *list;
  if (!(list = (LIST *)malloc(sizeof(LIST))))
    return NULL;
  list->first = NULL;
  list->last = NULL;
  list->count = 0;
  return list;
}

/**
 *  @brief  Create a new linked list node. Should probably not be called outside of linkedlist.c.
 *  @param  data Void pointer to the data the node should contain.
 *  @return Pointer to the newly-created list node.
 */
LIST_NODE *list_create_node(void *data) {
  LIST_NODE *node;
  if (!(node = (LIST_NODE *)malloc(sizeof(LIST_NODE))))
    return NULL;
  node->data = data;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

/**
 *  @brief  Insert a new node at the beginning of a list.
 *  @param  list Pointer to the list to insert the node into.
 *  @param  data Void pointer to the data the node should contain.
 *  @return Pointer to the newly-created list node.
 */
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

/**
 *  @brief  Insert a new node before a given node in a list.
 *  @param  list Pointer to the list to insert the node into.
 *  @param  node Pointer to the node to insert the node before.
 *  @param  data Void pointer to the data the node should contain.
 *  @return Pointer to the newly-created list node.
 */
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

/**
 *  @brief  Insert a new node after a given node in a list.
 *  @param  list Pointer to the list to insert the node into.
 *  @param  node Pointer to the node to insert the node after.
 *  @param  data Void pointer to the data the node should contain.
 *  @return Pointer to the newly-created list node.
 */
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

/**
 *  @brief  Insert a new node to the end of a given list.
 *  @param  list Pointer to the list to insert the node into.
 *  @param  data Void pointer to the data the node should contain.
 *  @return Pointer to the newly-created list node.
 */
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

/**
 *  @brief  Remove a node from a given list.
 *  @param  list Pointer to the list to remove the node from.
 *  @param  node List node to remove.
 *  @return Void pointer to the data that the removed node contained.
 */
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

/**
 *  @brief  Remove all nodes from a given list. Does not free the contents of the nodes.
 *  @param  list Pointer to the list to empty.
 */
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

/**
 *  @brief  Free the given list from memory.
 *  @param  list Pointer to the list to destroy.
 */
void list_destroy(LIST *list) {
  if (list == NULL)
    return;
  list_empty(list);
  free(list);
  list = NULL;
}

/**
 *  @brief  Execute a function on each node in a list.
 *  @param  list Pointer to the list to execute functions on.
 *  @param  func Pointer to a function to run on each element in the list. Takes a void pointer (the node data) and returns an int. If at any point during execution the function returns a non-zero value, the loop will break.
 *  @return -1 if the list was @c NULL or if a function call returned a non-zero number, otherwise 0.
 */
int list_foreach(LIST *list, int(* func)(void *)) {
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

/**
 *  @brief  Find a node in a list using a given search function.
 *  @param  list Pointer to the list to search through.
 *  @param  func Pointer to a function to run on each element in the list. Takes two void pointers, the first being the node data and the second being the @p data param passed to this function. Returns greater than zero if the data is a match, any other value otherwise.
 *  @param  data Void pointer to any additional data that should be passed to the search function.
 *  @return Pointer to the first node whose data matches the search function's criteria, or @c NULL if no such node exists.
 */
LIST_NODE *list_find(LIST *list, int(* func)(void *, void *), void *data) {
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


void *list_get(LIST *list, int offset) {
  LIST_NODE *node = list_getNodeFromOffset(list, offset);
  return (node == NULL ? NULL : node->data);
}

LIST_NODE *list_getNodeFromOffset(LIST *list, int offset) {
  LIST_NODE *node = list->first;
  int i = 0;
  if (offset >= list->count)
    return NULL;
  while (node && i < offset) {
    node = node->next;
    ++i;
  }
  return node;
}

void *list_removeAt(LIST *list, int offset) {
  LIST_NODE *node = list_getNodeFromOffset(list, offset);
  void *data;
  if (node == NULL)
    return NULL;
  data = node->data;
  list_remove(list, node);
  return data;
}

LIST_NODE *list_getNode(LIST *list, void *data) {
  LIST_NODE *node = list->first;
  while (node) {
    if (node->data == data)
      return node;
    node = node->next;
  }
  return NULL;
}