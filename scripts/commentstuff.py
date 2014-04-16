###############################################################################

# Filename: commentstuff.py

# Project Name: Game School Simulator 2015

# Author: Tai Der Hui

# Purpose: Adds the file header to all .c and .h files in a folder

# All content © 2014 DigiPen (USA) Corporation, all rights reserved.

###############################################################################

import os, sys

exts = ['.c', '.h']
adamFiles = []
edFiles = []
samFiles = []
dhFiles = []
authors = ["Adam Rezich", "Eduardo Gorinstein", "Samuel Valdez", "Tai Der Hui"]

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
                if int(author) == 0 :
                    adamFiles.append(fileName)
                if int(author) == 1 :
                    edFiles.append(fileName)
                if int(author) == 2 :
                    samFiles.append(fileName)
                if int(author) == 3 :
                    dhFiles.append(fileName)
                
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

# print to screen the total number of files each person wrote
print("Adam: " + str(len(adamFiles)) + '\n')
print("Ed: " + str(len(edFiles)) + '\n')
print("Sam: " + str(len(samFiles)) + '\n')
print("DH: " + str(len(dhFiles)) + '\n')

# write the filenames to different files
file = open("adam.txt", 'wt')
for item in adamFiles:
    file.write(item)
file.close()

file = open("ed.txt", 'wt')
for item in edFiles:
    file.write(item)
file.close()

file = open("sam.txt", 'wt')
for item in samFiles:
    file.write(item)
file.close()

file = open("dh.txt", 'wt')
for item in dhFiles:
    file.write(item)
file.close()
