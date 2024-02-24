# [COMP345] Assignment 1

### Authors

- Charles Partous
- Tristan Lafleur
- Andrea Lewis
- Michelle Pilonsky

### Description

A program that simulates a DnD character creation tool using the 5e ruleset submitted as an
assignment to Concorida University's COMP345 (Advanced Program Design with C++) course.

### Installation Instructions

This program was created using Visual Studio 2022. In the zip file the solution is included
along with the necessary source code to create a build and run it. 

In order to make a successful build of the project, follow these steps

1. Open the solution in Visual Studio and wait for everything to load
2. Locate the directory for the CppUnit library and source code.
3. Go to Go to 'Project > Properties > C/C++ > General'. Put "{your directory}\cppunit-1.12.1\include" in
	the 'Additional Include Directories' text box.
4. Go to 'Project > Properties > Linker > Input'. Put "{your directory}\cppunit-1.12.1\lib\cppunit.lib" in
	the 'Additional Dependences' text box.
5. Go to 'Project > Properties > Build Events > Post-Build Event'. Put '"$(TargetPath)"' in
	the 'Command Line' textbox.Put 'Unit Tests...' in the 'Description' textbox.
6. Run the project
