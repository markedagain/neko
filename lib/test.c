#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "actionlist.h"


void plrShoot_update(struct action_t *action, float dt) {
  printf("Action updating\n");
  action->IsFinished = 1;
}

void plrShoot_onStart(struct action_t *action) {
  printf("Action beginning\n");
}

void plrShoot_onEnd(struct action_t *action) {
  printf("Action ending\n");
}

Action *makeAction_plrShoot(void) {
  Action *a = malloc(sizeof *a);
  a->Update = plrShoot_update;
  a->OnStart = plrShoot_onStart;
  a->OnEnd = plrShoot_onEnd;
  a->IsFinished = 0;
  a->IsBlocking = 1;
  a->Lanes = 0;
  a->Elapsed = 0.0;
  a->Duration = 1.0;
  a->HasStarted = 0;
  return a;
}

int main(void) {
  ActionList al;
  al_init(&al);
  al_append(&al, makeAction_plrShoot());
  al_append(&al, makeAction_plrShoot());
  al_append(&al, makeAction_plrShoot());
  al_append(&al, makeAction_plrShoot());
  /*al_append(&al, makeAction_plrShoot());
  */
  printf("Action list contains %i items.\n", (int)list_size(&(al.Actions)));
  al_update(&al, 0.1f);
  printf("Action list contains %i items.\n", (int)list_size(&(al.Actions)));
  al_update(&al, 0.1f);
  printf("Action list contains %i items.\n", (int)list_size(&(al.Actions)));
  /*ActionList al;
  al_init(&al);
  al_append(&al, makeAction_plrShoot());
  al_append(&al, makeAction_plrShoot());
  al_append(&al, makeAction_plrShoot());
  al_update(&al, 0.0f);
  al_free(&al);*/
#if 0
  List v;
  int i;

  /* initialize the vector */
  list_init_size(&v, 2);

  /* print info about the vector */
  printf("List contains %i entries, and has a capacity of %i\n", (int)list_size(&v), (int)list_capacity(&v));

  /* add a bunch of strings */
  list_append(&v, "0 hey");
  list_append(&v, "1 hi");
  list_append(&v, "2 hello");
  list_append(&v, "3 what");
  list_append(&v, "4 is");
  list_append(&v, "5 up");
  list_append(&v, "6 my");
  list_append(&v, "7 mans");
  list_append(&v, "8 !");

  /* print all of the elements as strings */
  for (i = 0; i < list_size(&v); ++i) {
    printf("%s\n", (const char *)list_get(&v, i));
  }

  /* print more info about the vector */
  printf("List now contains %i entries, and has a capacity of %i\n", (int)list_size(&v), (int)list_capacity(&v));

  /* free up memory */
  list_free(&v);
#endif
  return 0;
}
