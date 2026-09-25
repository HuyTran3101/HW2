# HW2
This repository contains three C++ programs built around the TimeCode class:

## TimeCodeTests.cpp
Contains tests for the `TimeCode` class, including constructors, getters, setters, arithmetic operators, and comparison operators.

## NasaLaunchAnalysis.cpp
Reads launch data from `Space_Corrected.csv`, extracts the UTC launch times, and calculates the average launch time using the `TimeCode` class.

**Input:** `Space_Corrected.csv`

**Expected output:**

4198 data points.
AVERAGE: 12:7:56

## PaintDryTimer.cpp

Calculates and tracks the drying time of batches of painted spheres based on their surface area.

**Input:** The user enters a radius when adding a batch and can choose to add (A), view (V), or quit (Q) the program.

**Expected output:** The program displays each batch's ID, drying time, remaining time, and a message when a batch is finished.