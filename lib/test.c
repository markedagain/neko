#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "actionlist.h"
#include "linkedlist.h"

void plrShoot_update(struct action_t *action, float dt) {
  printf("Action updating\n");
  action->isFinished = 1;
}

void plrShoot_onStart(struct action_t *action) {
  printf("Action beginning\n");
}

void plrShoot_onEnd(struct action_t *action) {
  printf("Action ending\n");
}

ACTION *makeAction_plrShoot(void) {
  ACTION *a = malloc(sizeof *a);
  a->update = plrShoot_update;
  a->onStart = plrShoot_onStart;
  a->onEnd = plrShoot_onEnd;
  a->isFinished = 0;
  a->isBlocking = 1;
  a->lanes = 0;
  a->elapsed = 0.0;
  a->duration = 1.0;
  a->hasStarted = 0;
  return a;
}

int node_test(void *data) {
  printf("### (%s) ###\n", (char *)data);
  return 0;
}

int node_test2(void *listData, void *searchData) {
  return strcmp((char *)listData, (char *)searchData) ? 0 : 1;
}

int main(void) {
  ALIST al;
  al_init(&al);
  al_append(&al, makeAction_plrShoot());
  printf("Action list contains %i items.\n", (int)vector_size(&(al.actions)));
  al_update(&al, 0.1f);
  printf("Action list contains %i items.\n", (int)vector_size(&(al.actions)));
  al_update(&al, 0.1f);
  printf("Action list contains %i items.\n", (int)vector_size(&(al.actions)));
  
  LIST *l;
  LIST_NODE *node;
  void *data;
  l = list_create();
  list_insert_end(l, (void *)"first");
  node = list_insert_beginning(l, (void *)"begin");
  node = list_insert_after(l, node, (void *)"after");
  list_insert_before(l, node, (void *)"before");
  list_insert_end(l, (void *)"end");
  data = list_remove(l, node);
  
  printf("This was removed from the list, but the data was saved: %s\n\n", (char *)data);
  
  printf("%s\t\t", (l->first) ? (char *)(l->first->data) : "NULL");
  printf("\t\t%s", (l->last) ? (char *)(l->last->data) : "NULL");
  printf("\t\t%i\n", l->count);
  
  node = l->first;
  while (node) {
    printf("%s\t\t", (node->prev) ? (char *)(node->prev->data) : "NULL");
    printf("%s", (char *)(node->data));
    printf("\t\t%s", (node->next) ? (char *)(node->next->data) : "NULL");
    printf("\n");
    node = node->next;
  }
  
  list_foreach(l, node_test);
  
  node = list_find(l, node_test2, (void *)"before");
  printf("SEARCH RESULT: %s\n", (char *)node->data);
  
  list_destroy(l);
  return 0;
  
}
