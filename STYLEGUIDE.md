Team Neko Means Cat Style Guide
===============================

Writing good code is cool and all, but it's kind of useless if nobody else on your team can make sense of it, or if you're a horrible person and use stupid bullshit brace formatting or dumb indentations. This is why I, Adam Rezich, technical lead of Team Neko Means Cat, present the official **Team Neko Means Cat Style Guide**!

This is going to be a document that evolves over time and stuff, but it's actually pretty solid as of now, I think. Pretty much all of the basics are covered, but let me know if there's anything I missed and I'll clarify it and add it in.


Source code formatting
----------------------

This is most of the style guide, because it's like the most important thing in the world.


### Tabs and indentation ###

All tabs should be converted into two spaces.

All blocks of code should be indented, which is to say, the **contents** of all blocks of code should be indented one level further than the block definition. The closing brace should be on a line by itself, at the same indentation level as the block definition.


### Braces ###

Braces are not necessary for one-line blocks, and in fact should not have them if possible.

Opening braces belong on the same line as the block declaration.

Closing braces belong on their own line.

Never do something dumb like put a closing brace and another opening brace on the same line, like this: `} else {`


### Spacing ###

There should not be a space between a function name and the open parenthesis.

There should always be a space between a keyword and any following open parenthesis. The sole exception to this is `sizeof`, since it basically acts like a function. `if`, `for`, `while`, `switch`, etc. are all keywords, though, and not functions.

There should not be a space between an open parenthesis and its contents.

There should not be a space between the contents of parenthesis and the closing parenthesis.

There should be a space between operators when appropriate. The exceptions to this are cases such as the dereference operator (unary *), address-of operator (unary &), and a few other cases. For example, dereferencing a pointer p should be `*p` and not `* p`, but addition should be expressed as `1 + foo + 3` and not `1+foo+3`.


### Example of proper tabs, braces, indentation, and spacing ###

    int foo(int bar, float baz) {
      int quux = 1;
      int i;
      for (i = 0; i < bar; ++i) {
        baz += pow(quux * bar, 2) / i;
        quux *= i % 2;
      }
      return bar;
    }


Naming conventions
------------------

Having consistent naming conventions is actually way more important than having your braces in the right place or whatever. If you name your functions or variables in a way that doesn't fit with the rest of the project, nobody will remember how to call your functions or use your variables and everyone will hate you and call you names.


### Variables ###

Variable names should be generally written in camelCase; that is, no spaces, lowercase first letter, capital first letter of every subsequent word.

Sometimes it may be valuable to group variable names with a certain identifier. In this case, the identifier should be camelCase, followed by an underscore, followed by the remainder of the variable name. For example, if I had several `foo` variables, I would name them `foo_bar`, `foo_bazQuux`, and so forth.

I'm not Mead, and this isn't CS120 anymore, so I'm not going to be crazy and demand that you comment every variable declaration or something; that would be crazy. However...

Variables should be named in a self-documenting manner. Be concise, but clear. Don't name variables, like, an entire sentence in camelcase or anything.


### Functions ###

General-purpose functions should be named in all lowercase, with underscores between words. Such functions are generally few and far between, so this isn't a very common situation, but an example might be like `draw_butt()` to draw an ASCII butt.

Much more relevant and important are functions that apply to structs ("fake class methods") or are otherwise logically organized, similiar to how variables can be organized. Such functions follow a similar naming structure to variables: group identifier, underscore, then camelCase function name. For example, if I have a series functions that manipulate a `player` struct, I might name them `player_draw()`, `player_update()`, and `player_handleInput()`.

Function parameters should be given brief but descriptive names.


### Structs and typedefs ###

Structs without typedefs should be TODO

Structs that have an associated typedef should be named by having the typedef tag be in all caps, with underscores between words, and having the struct name be the same name, but in camelCase, with a _t at the end (for "type"). Tags should be brief and easily-typable.

Example of a struct/typedef combination:

    typedef struct meleeWeapon_t {
      /* struct declaration here */
    } MELEE_WEAPON;


Documentation
-------------

**This section is a work-in-progress, as I'm still figuring out how to use doxygen myself.**


### DigiPen copyright notice ###

All source code files should begin with the following, as per DigiPen policy:

    /* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */


### File headers ###

All source code files should contain a Doxygen header following the above DigiPen copyright notice, with one blank line in between, formatted as such:

    /** @file    filename.c
     *  @brief   A brief description of the file's purpose goes here.
     *
     *  If a file needs a description longer than the "brief" description above, it
     *  should be formatted like this, with an an additional blank line above it, as
     *  seen here. Long descriptions should be no longer than eighty characters in
     *  length, but really, long descriptions probably won't really be necessary.
     */

### Function headers ###

All functions should have Doxygen headers immediately preceding them, as such:

    /** @brief   A brief description of the file's purpose goes here.
     *  @param	 bar Description of what the bar parameter does goes here.
     *  @param   baz Description of what the baz parameter does goes here.
     *  @return  Description of what the function returns goes here (omit if void).
     */
    int foo(int bar, float baz) {

### Struct headers ###

TODO


### Bugs/TODO ###

If (when) you run into any serious bugs that you can't work out in your code, throw in a Doxygen "bug" comment like this:

    /** @bug	 A brief description of the bug goes here. */

If (when) you start working on something but don't finish some key aspect of it, throw in a Doxygen "todo" comment like this:

    /** @todo	 A brief description of what needs be done goes here. */


Misc.
-----

File contents **should** be restricted to 80 characters per line, ideally, but this is a nice ideal and not a strict requirement. However, stupidly long lines should be avoided.

The ternary operator is super rad and should be used when applicable, but if you nest more than one ternary operator in a single statement that's basically the worst thing ever and you should feel bad about yourself.

As a matter of good practice, pre-increment and pre-decrement should be used instead of post-increment and post-decrement, respectively, whenever casually incrementing or decrementing things.


All header files should contain the following code (after the DigiPen copyright notice and Doxygen header) (provided this file is named `filename.h`):

    #ifndef __FILENAME_H__
    #define __FILENAME_H__

    /* rest of header file contents go here */

    #endif


Commit messages
---------------

Commit messages should be concise and to the point, elegantly laying out the changes you made since the last commit.

Avoid Adam Rezich Commits ("ARCs"); that is, messages that contain content such as "holy shit it fucking works now" or "did some shit and stuff" or "made the thing better at the one place."
