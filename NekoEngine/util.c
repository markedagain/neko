/******************************************************************************
Filename: util.c

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


unsigned long GraphicsColor(unsigned char a, unsigned char r, unsigned char g, unsigned char b) {
  return (a << 24) + (r << 16) + (g << 8) + b;
}