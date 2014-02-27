Action lists
============

This is an overview of how to use action lists, awesome data structures that
make doing stuff sequentially awesome.


In your component data struct
-----------------------------

    typedef struct {
	  ALIST actions;
	} CDATA_FOO;


When you create your component
------------------------------

	CDATA_FOO *data = (CDATA_FOO *)data;
	al_init(&data->actions);


When you update your component
------------------------------

Note: do this in frameUpdate *or* logicUpdate, **not** both.

	CDATA_FOO *data = (CDATA_FOO *)data;
	EV_UPDATE *updateEvent = (EV_UPDATE *)event;
	al_update(&data->actions, updateEvent->dt);


When you destroy your component
-------------------------------

	CDATA_FOO *data = (CDATA_FOO *)data;
	al_destroy(&data);


When you want to add an action to your component
------------------------------------------------

	ACTION *action = action_create(data, update, onStart, onEnd, blocking, duration);

- **data** - void pointer to whatever you want (probably your component's data) (or NULL)
- **update** - function pointer, (see "Action functions," below) (or NULL)
- **onStart** - function pointer, (see "Action functions," below) (or NULL)
- **onEnd** - function pointer, (see "Action functions," below) (or NULL)
- **blocking** - whether or not this action is blocking
- **duration** - length of this action, in seconds


### Action functions ###

Assuming you're doing something like:

	ACTION *action = action_create(NULL, foo_update, foo_onStart, foo_onEnd, false, 1.5f);

This is how the functions should look:

	foo_update(ACTION *action, float dt) {
	  // This will be called every update, assuming you put al_update() in your
	  //   update event function properly.
	}
	
	foo_onStart(ACTION *action) {
	  // This will be called once, when your action finally "gets to" start
	}
	
	foo_onEnd(ACTION *action) {
	  // This will be called once, when your action is about to be finished.
	  // This will also be called if you prematurely destroy your action list and
      //   this action has already "begun" (i.e. its onStart was called).
	}

### Insertion functions ###

After creating your action, you must insert it into the action list using one of
the following functions.

	al_pushFront(&data->actions, action); // Put at FRONT of action list (this will happen like immediately)
	al_pushBack(&data->actions, action); // Put at BACK of action list (this will happen after everything else)
	al_insertBefore(&data->actions, someOtherAction, action) // insert BEFORE (sooner than) someOtherAction
	al_insertAfter(&data->actions, someOtherAction, action) // insert AFTER (later than) someOtherAction

### Putting it all together ###

You don't need to separate the action creation and insertion; why not just do it all on one line?

	al_pushFront(&data->actions, action_create(NULL, foo_update, foo_onStart, foo_onEnd, false, 1.5f)); 