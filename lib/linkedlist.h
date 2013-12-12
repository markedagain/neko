#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

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

LIST *list_create(void);
LIST_NODE *list_create_node(void *);
LIST_NODE *list_insert_beginning(LIST *, void *);
LIST_NODE *list_insert_before(LIST *list, LIST_NODE *node, void *data);
LIST_NODE *list_insert_after(LIST *, LIST_NODE *, void *);
LIST_NODE *list_insert_end(LIST *, void *);
void *list_remove(LIST *, LIST_NODE *);
void list_remove_free(LIST *, LIST_NODE *);
void list_empty(LIST *);
void list_destroy(LIST *);
int list_foreach(LIST *list, int(* func)(void *));
LIST_NODE *list_find(LIST *list, int(* func)(void *, void *), void *data);

#endif
