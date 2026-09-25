# HW2
This repository contains three C++ programs built around the TimeCode class:

TimeCode Tests - Tests the functionality of the TimeCode class.
NASA Launch Analysis - Reads space launch data and calculates the average launch time of day.
Paint Dry Timer - Tracks the real-time drying progress of batches of painted spheres.
Requirements

The programs require:

A C++ compiler such as g++
make to use the provided Makefile
The Space_Corrected.csv data file for the NASA Launch Analysis program
Valgrind for checking memory leaks in the Paint Dry Timer, if available
Files
TimeCode.h

Contains the declaration of the TimeCode class.

The class represents a time using a total number of seconds and provides functions for:

Creating and copying TimeCode objects
Getting hours, minutes, and seconds
Converting between time components and total seconds
Converting a time to a string
Adding and subtracting times
Multiplying and dividing times
Comparing TimeCode objects
TimeCode.cpp

Contains the implementation of the TimeCode class and its functions and operators.

TimeCodeTests.cpp

Contains tests for the TimeCode class, including constructors, getters, setters, arithmetic operators, and comparison operators.

NasaLaunchAnalysis.cpp

Reads launch information from Space_Corrected.csv.

The program:

Reads the launch data.
Extracts the time of day from each valid launch.
Ignores entries that do not contain an exact launch time.
Stores the times using TimeCode objects.
Calculates the average launch time using the TimeCode operations.
Prints the number of valid data points and the average launch time.

The expected result is:

4198 data points.
AVERAGE: 12:7:56
PaintDryTimer.cpp

Tracks the drying time of batches of painted spheres.

The drying time is based on the surface area of a sphere:

surface area = 4πr²

The program uses time(0) to measure real elapsed time. Each batch has a TimeCode object allocated on the heap to keep track of its remaining drying time.

When a batch reaches zero seconds remaining:

The batch is reported as DONE!
Its dynamically allocated TimeCode object is deleted
The batch is removed from the tracker
Space_Corrected.csv

The input data file used by NasaLaunchAnalysis.cpp.

Makefile

Provides commands for compiling all three programs.

Compiling

From the repository directory, run:

make

The Makefile builds these three executables:

tct
nasa
pdt

The equivalent compilation commands are:

g++ TimeCode.cpp TimeCodeTests.cpp -o tct
g++ TimeCode.cpp NasaLaunchAnalysis.cpp -o nasa
g++ TimeCode.cpp PaintDryTimer.cpp -o pdt
Running the Programs
1. Run the TimeCode tests
./tct

This runs the tests in TimeCodeTests.cpp.

2. Run NASA Launch Analysis

Make sure Space_Corrected.csv is in the appropriate directory, then run:

./nasa

The program should report:

4198 data points.
AVERAGE: 12:7:56
3. Run the Paint Dry Timer
./pdt

The program provides three options:

(A)dd
(V)iew Current Items
(Q)uit

Use A to add a batch by entering a sphere radius.

Use V to view the current batches and their remaining drying times.

Use Q to quit the program.

Checking for Memory Leaks

The Paint Dry Timer dynamically allocates a TimeCode object for each batch. These objects must be deleted when their drying time reaches zero.

If Valgrind is installed, the program can be checked with:

valgrind --leak-check=full ./pdt

A successful run should report that all heap blocks were freed and that there are no memory leaks.

Git Workflow

This project uses Git for version control.

After making changes:

git status
git add .
git commit -m "Describe the changes"
git push

To view the commit history:

git log --oneline

The repository history contains multiple commits showing the progress of the project.

Notes

The Paint Dry Timer generates batch IDs using rand(). Because these IDs are generated using pseudo-random numbers, two batches may theoretically receive the same ID.

The starter Paint Dry Timer file was renamed from PaintDryTimerStarter.cpp to PaintDryTimer.cpp as required by the assignment.