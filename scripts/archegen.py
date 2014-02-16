# creates an archetype file based on input

def writeHeader(archName, f, logic):
    capName = archName.upper()
    f.write("/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */\n")
    f.write("\n#ifndef __" + capName + "__\n")
    f.write("#define __" + capName + "__\n")
    f.write('\n#include "entity.h"\n')
    f.write('#include "hash.h"\n')
    f.write('\n#define ARCH_' + capName + ' HASH("ARCH_' + capName + '")\n')
    if logic:
        f.write("void comp_" + archName + "_logicUpdate(COMPONENT *self, void *event);\n")
        f.write("void comp_" + archName + "(COMPONENT *self);\n")
    f.write("\n#endif\n")

archName = input("Enter name (in camel case) of archetype: ")
fileName = archName.lower()
capName = archName.upper()
logicFlag = input("Generate logic file? (y/n)")

# open c file for writing
f = open(fileName +".c", mode = 'w')

# writing header and includes
f.write("/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */\n")
f.write("\n#include " + fileName + ".h\n")

# writing archetype connection function
f.write("\nvoid arch_" + archName + "(ENTITY *entity) {\n}")

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
    f.write('#include "' + compFile + '.h"\n')
    
    # functions
    f.write("\nvoid comp_" + compName + "_logicUpdate(COMPONENT *self, void *event) {\n}")
    f.write("void comp_" + compName + "(COMPONENT *self) {\n")
    f.write("COMPONENT_INIT_NULL(self, COMP_" + compCap + ")\n")
    f.write("self->events.logicUpdate = comp_" + compName + "_logicUpdate")

    # close c file
    f.close()
