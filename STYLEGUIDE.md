Team Neko Means Cat Style Guide
===============================

Writing good code is cool and all, but it's kind of useless if nobody else on your team can make sense of it, or if you're a horrible person and use stupid bullshit brace formatting or dumb indentations. This is why I, Adam Rezich, technical lead of Team Neko Means Cat, present the official **Team Neko Means Cat Style Guide**!

This is going to be a document that evolves over time and stuff, but it's actually pretty solid as of now, I think. Pretty much all of the basics are covered, but let me know if there's anything I missed and I'll clarify it and add it in.


Source code formatting
----------------------

This is most of the style guide, because it's like the most important thing in the world.


###Tabs and indentation###

All tabs should be converted into two spaces.

All blocks of code should be indented, which is to say, the **contents** of all blocks of code should be indented one level further than the block definition. The closing brace should be on a line by itself, at the same indentation level as the block definition.


###Braces###

Braces are not necessary for one-line blocks, and in fact should not have them if possible.

Opening braces belong on the same line as the block declaration.

Closing braces belong on their own line.

Never do something dumb like put a closing brace and another opening brace on the same line, like this: `} else {`


###Spacing###

There should not be a space between a function name and the open parenthesis.

There should not be a space between an open parenthesis and its contents.

There should not be a space between the contents of parenthesis and the closing parenthesis.

There should be a space between operators when appropriate. The exceptions to this are cases such as the dereference operator (unary *), address-of operator (unary &), and a few other cases. For example, dereferencing a pointer p should be `*p` and not `* p`, but addition should be expressed as `1 + foo + 3` and not `1+foo+3`.


###Example of proper tabs, braces, indentation, and spacing###

    int foo(int bar, float baz) {
      int quux = 1;
      int i;
      for (i = 0; i < bar; ++i) {
        baz += pow(quux * bar, 2) / i;
        quux *= i % 2;
      }
      return bar;
    }


###Documentation###

**This section is a work-in-progress, as I'm still figuring out how to use doxygen myself.**

All source code files should begin with the following, as per DigiPen policy:

    /* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

All source code files should contain a Doxygen header following the above DigiPen copyright notice, with one blank line in between, formatted as such:

    /** @file    filename.c
     *  @brief   A brief description of the file's purpose goes here.
     *
     *  If a file needs a description longer than the "brief" description above, it
     *  should be formatted like this, with an an additional blank line above it, as
     *  seen here. Long descriptions should be no longer than eighty characters in
     *  length, but really, long descriptions probably won't really be necessary.
     */

All functions should have Doxygen headers immediately preceding them, as such:

    /** @brief   A brief description of the file's purpose goes here.
     *  @param	 bar Description of what the bar parameter does goes here.
     *  @param   baz Description of what the baz parameter does goes here.
     *  @return  Description of what the function returns goes here (omit if void).
     */
    int foo(int bar, float baz) {

If (when) you run into any serious bugs that you can't work out in your code, throw in a Doxygen "bug" comment like this:

    /** @bug	 A brief description of the bug goes here. */

If (when) you start working on something but don't finish some key aspect of it, throw in a Doxygen "todo" comment like this:

    /** @todo	 A brief description of what needs be done goes here. */


###Misc.###

File contents **should** be restricted to 80 characters per line, ideally, but this is a nice ideal and not a strict requirement. However, stupidly long lines should be avoided.

The ternary operator is super rad and should be used when applicable, but if you nest more than one ternary operator in a single statement that's basically the worst thing ever and you should feel bad about yourself.

As a matter of good practice, pre-increment and pre-decrement should be used instead of post-increment and post-decrement, respectively, whenever casually incrementing or decrementing things.


Commit messages
---------------

Commit messages should be concise and to the point, elegantly laying out the changes you made since the last commit.

Avoid Adam Rezich Commits ("ARCs"); that is, messages that contain content such as "holy shit it fucking works now" or "did some shit and stuff" or "made the thing better at the one place."
