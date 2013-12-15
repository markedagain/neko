Team Neko Means Cat Style Guide
===============================

Writing good code is cool and all, but it's kind of useless if nobody else on your team can make sense of it, or if you're a horrible person and use stupid bullshit brace formatting or dumb indentations. This is why I, Adam Rezich, technical lead of Team Neko Means Cat, present the official **Team Neko Means Cat Style Guide**!

Tabs and indentation
--------------------

All tabs should be converted into two spaces.

All blocks of code should be indented, which is to say, the **contents** of all blocks of code should be indented one level further than the block definition. The closing brace should be on a line by itself, at the same indentation level as the block definition.


Braces
------

Braces are not necessary for one-line blocks, and in fact should not have them if possible.

Opening braces belong on the same line as the block declaration.

Closing braces belong on their own line.


Spacing
-------

There should not be a space between a function name and the open parenthesis.

There should not be a space between an open parenthesis and its contents.

There should not be a space between the contents of parenthesis and the closing parenthesis.

There should be a space between operators when appropriate. The exceptions to this are cases such as the dereference operator (unary *), address-of operator (unary &), and a few other cases. For example, dereferencing a pointer p should be `*p` and not `* p`, but addition should be expressed as `1 + foo + 3` and not `1+foo+3`.


Misc.
-----

File contents **should** be restricted to 80 characters per line, ideally, but this is a nice ideal and not a strict requirement. However, stupidly long lines should be avoided.

The ternary operator is super rad and should be used when applicable, but if you nest more than one ternary operator in a single statement that's basically the worst thing ever and you should feel bad about yourself.


