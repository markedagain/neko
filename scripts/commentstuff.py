# Written by Tai Der Hui, 2014
# Looks at every file in current directory and adds a file header

import os, sys

exts = ['.c', '.h']
authors = ["Adam Rezich",
           "Eduardo Gorinstein",
           "Samuel Valdez",
           "Tai Der Hui"]

here = os.path.abspath(os.path.dirname(sys.argv[0]))
filesToCheck = []

for base, dirs, files in os.walk(here):

    # run through every filename in the directory
    for fileName in files:
        # get the file extension
        ext = (fileName[fileName.rindex('.'):]).lower()

        try:
            # check if the extension is one of the listed extensions
            if exts.index(ext) >= 0:

                # get author
                print(fileName)
                author = input("Who is Author? 0 = Adam, 1 = Ed, 2 = Sam, 3 = DH: ")
                
                # open file and read in all lines
                fileNameAndPath = (base + '/' + fileName)
                file = open(fileNameAndPath)
                content = file.readlines()

                # check if first line is the digipen header. if yes, replace it
                if content[0] == "/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */\n":
                    content.pop(0)
                    print("Copyright Info Replaced\n")

                else:
                    print ("Copyright Info NOT Replaced\n")
                    filesToCheck.append(fileName)
                                
                # make new array with the new header
                firstLine = "/******************************************************************************\n"
                fileLine = "Filename: " + fileName + "\n\n"
                projectLine = "Project Name: Game School Simulator 2015\n\n"
                authorLine = "Author: " + authors[int(author)] + "\n\n"
                copyrightLine = "All content © 2014 DigiPen (USA) Corporation, all rights reserved.\n\n"
                lastLine = "******************************************************************************/\n\n"
                newContent = [firstLine, fileLine, projectLine, authorLine, copyrightLine, lastLine]
                newContent.extend(content)

                # close the file for reading
                file.close()

                # open the file for writing and write the new stuff
                file = open(fileNameAndPath, 'wt')
                for newLine in newContent:
                    file.write(newLine)

                # close the file for writing
                file.close()
                
        # if the extension is not valid, skip over file            
        except:
            pass

# write all the errors to a file
file = open("errors.txt", 'wt')
for name in filesToCheck:
    file.write(name)
file.close()
