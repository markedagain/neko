###############################################################################

# Filename: commentstuff.py

# Project Name: Game School Simulator 2015

# Author: Tai Der Hui

# Purpose: Creates an archetype file based on input

# All content © 2014 DigiPen (USA) Corporation, all rights reserved.

###############################################################################

def writeHeader(archName, f, logic):
    capName = archName.upper()
    f.write("/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */\n")
    if (logic):
        f.write("\n#ifndef __COMP_" + capName + "__\n")
        f.write("#define __COMP_" + capName + "__\n")
    else:
        f.write("\n#ifndef __ARCH_" + capName + "__\n")
        f.write("#define __ARCH_" + capName + "__\n")
    f.write('\n#include "entity.h"\n')
    f.write('#include "hash.h"\n')
    if logic:
        f.write('\n#define COMP_' + capName + ' HASH("COMP_' + capName + '")\n')
        f.write("void comp_" + archName + "_logicUpdate(COMPONENT *self, void *event);\n")
        f.write("void comp_" + archName + "(COMPONENT *self);\n")
    else:
        f.write('\n#define ARCH_' + capName + ' HASH("ARCH_' + capName + '")\n')
        f.write('void arch_' + archName + '(ENTITY *entity);\n')
    f.write("\n#endif\n")

archName = input("Enter name (in camel case) of archetype: ")
fileName = archName.lower()
capName = archName.upper()
logicFlag = input("Generate logic file? (y/n)")
transformFlag = input("Does it have a transform (y/n)")

# open c file for writing
f = open(fileName +".c", mode = 'w')

# writing header and includes
f.write("/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */\n")
f.write('\n#include "' + fileName + '.h"\n')
if logicFlag.upper() == 'Y':
    f.write('#include "' + fileName + 'logic.h"\n')
if transformFlag.upper() == 'Y':
    f.write('#include "transform.h"\n')


# writing archetype connection function
f.write("\nvoid arch_" + archName + "(ENTITY *entity) {\n")
f.write("  entity->id = ARCH_" + capName + ";\n")
if transformFlag.upper() == 'Y':
    f.write("  entity_connect(entity, comp_transform);\n")
if logicFlag.upper() == 'Y':
    f.write("  entity_connect(entity, comp_" + archName + "Logic);\n")
f.write("}\n")

# close c file
f.close()

# open .h file for writing
f = open(fileName + ".h", mode = 'w')

writeHeader(archName, f, False)

# close.h file
f.close()

if logicFlag.upper() == 'Y':
    compName = archName + "Logic"
    compFile = compName.lower()
    compCap = compName.upper()

    # open h file for writing
    f = open(compFile + ".h", mode = 'w')
    writeHeader(compName, f, True)
    # close h file
    f.close()

    # open c file for writing
    f = open(compFile + ".c", mode = 'w')

    # includes
    f.write("/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */\n")
    f.write('\n#include "' + compFile + '.h"\n')
    
    # functions
    f.write("\nvoid comp_" + compName + "_logicUpdate(COMPONENT *self, void *event) {\n}\n")
    f.write("\nvoid comp_" + compName + "(COMPONENT *self) {\n")
    f.write("  COMPONENT_INIT_NULL(self, COMP_" + compCap + ");\n")
    f.write("  self->events.logicUpdate = comp_" + compName + "_logicUpdate;\n")
    f.write("}\n")

    # close c file
    f.close()
