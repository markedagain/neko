#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
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
  printf("Action list contains %i items.\n", (int)vector_size(&(al.Actions)));
  al_update(&al, 0.1f);
  printf("Action list contains %i items.\n", (int)vector_size(&(al.Actions)));
  al_update(&al, 0.1f);
  printf("Action list contains %i items.\n", (int)vector_size(&(al.Actions)));
  return 0;
}
