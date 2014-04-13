/******************************************************************************
Filename: linkedlist.h

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include "neko.h"

typedef struct listNode_t {
  void *data;
  struct listNode_t *next;
  struct listNode_t *prev;
} LIST_NODE;

typedef struct linkedList_t {
  struct listNode_t *first;
  struct listNode_t *last;
  int count;
} LIST;

NEKO_API LIST *list_create(void);
LIST_NODE *list_create_node(void *);
NEKO_API LIST_NODE *list_insert_beginning(LIST *, void *);
NEKO_API LIST_NODE *list_insert_before(LIST *list, LIST_NODE *node, void *data);
NEKO_API LIST_NODE *list_insert_after(LIST *, LIST_NODE *, void *);
NEKO_API LIST_NODE *list_insert_end(LIST *, void *);
NEKO_API void *list_remove(LIST *, LIST_NODE *);
NEKO_API void list_remove_free(LIST *, LIST_NODE *);
NEKO_API void list_empty(LIST *);
NEKO_API void list_destroy(LIST *);
NEKO_API int list_foreach(LIST *list, int(* func)(void *));
NEKO_API LIST_NODE *list_find(LIST *list, int(* func)(void *, void *), void *data);
NEKO_API void *list_get(LIST *list, int offset);
NEKO_API LIST_NODE *list_getNodeFromOffset(LIST *list, int offset);
NEKO_API void *list_removeAt(LIST *list, int offset);
NEKO_API LIST_NODE *list_getNode(LIST *list, void *data);
NEKO_API void list_copy(LIST *destination, LIST *source);

#endif
