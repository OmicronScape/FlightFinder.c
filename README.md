Flight  Finder

Description:

This C program allows users to find flight routes between 10 major cities. It provides direct flight durations and also suggests alternative routes with layovers if no direct flights are available. The program calculates and displays the expected arrival time based on the user's input departure time.

Features

Allows users to select a departure and arrival city from a predefined list.

Accepts user input for departure time and validates it.

Checks for direct flights and displays their duration.

Suggests alternative routes with one layover if no direct flights are available.

Calculates and displays the arrival time after the flight duration.

Defensive programming to ensure valid inputs.

Cities Available

-Athens

-London

-Rome

-Paris

-New York

-Berlin

-Barcelona

-Milan

-Tokyo

-Sydney

Compilation and Execution

Compile the program using GCC:

gcc flight_finder.c -o flight_finder

Run the executable:

./flight_finder

Usage

Enter the departure time as a four-digit number (e.g., 1445 for 14:45).

Select a departure city from the list by entering its corresponding number.

Select an arrival city from the list.

The program displays:

Direct flight duration (if available).

Alternative routes with one layover (if no direct flight is available).

Expected arrival time based on the flight duration.

Example Run

Enter the time in the form of a four-digit positive number (e.g., 1445): 1230
Departure time: 12:30
City options:
0: Athens
1: London
2: Rome
3: Paris
4: New York
5: Berlin
6: Barcelona
7: Milan
8: Tokyo
9: Sydney
Enter the number of the departure city: 0
Enter the number of the arrival city: 4

************* Search Results *************
Option 1: Direct flight from Athens to New York. Duration: 9.5 hours.
The arrival time is: 22:00

Notes

Flight durations are predefined in a 2D array.

A -1.0 value in the flight duration table means no direct flight is available.

The program assumes flights operate 24/7 with no layover delays.

If a flight arrives after midnight, the program notifies the user that arrival is on the next day.

License

This project is open-source and free to use.


