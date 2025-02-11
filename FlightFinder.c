#include <stdio.h>
#include <stdlib.h>

#define INDENTATION "    "

/* City names */
const char *city_names[] = {
    "Athens", "London", "Rome", "Paris", "New York", "Berlin", "Barcelona", "Milan", "Tokyo", "Sydney"
};

/* Flight durations */
float flight_durations[10][10] = {
    {0.0, 4.0, 2.0, -1.0, 9.5, -1.0, -1.0, -1.0, -1.0, -1.0},
    {4.0, 0.0, -1.0, 1.0, 7.0, -1.0, -1.0, -1.0, -1.0, -1.0},
    {2.0, -1.0, 0.0, -1.0, -1.0, 1.5, -1.0, 1.5, -1.0, -1.0},
    {-1.0, 1.0, -1.0, 0.0, -1.0, -1.0, 1.5, -1.0, -1.0, -1.0},
    {9.5, 7.0, -1.0, -1.0, 0.0, -1.0, 8.0, -1.0, 13.0, -1.0},
    {-1.0, -1.0, 1.5, -1.0, -1.0, 0.0, -1.0, 1.5, -1.0, -1.0},
    {-1.0, -1.0, -1.0, 1.5, 8.0, -1.0, 0.0, -1.0, -1.0, -1.0},
    {-1.0, -1.0, 1.5, -1.0, -1.0, 1.5, -1.0, 0.0, -1.0, -1.0},
    {-1.0, -1.0, -1.0, -1.0, 13.0, -1.0, -1.0, -1.0, 0.0, 9.5},
    {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 9.5, 0.0}
};

/* Function declarations */
void print_city_options();                 /* Function for question 2      */
int get_city_index(int);
void add_duration(float, int, int);        /*                               */
void find_routes(int, int, int, int);      /* Function for questions 3-4  */
void request_departure_time(int*, int*);   /* Function for question 1      */

int main()
{
    int departure_city, arrival_city;
    int hours, minutes;

    /* Question 1. Enter time and defensive programming */
    /* Continuous input from the user until a valid time is given */
    request_departure_time(&hours, &minutes);

    /* Question 2. Print city options. */
    print_city_options();
    /* Question 2. Defensive programming for selecting departure city */
    do 
    {
        printf("Enter the number of the departure city: ");
        scanf("%d", &departure_city);

        if (get_city_index(departure_city) == -1)
        {
            printf("Invalid departure city selection.\n");
            continue;
        }
        do {
            printf("Enter the number of the arrival city: ");
            scanf("%d", &arrival_city);

            if (get_city_index(arrival_city) == -1)
            {
                printf("Invalid arrival city selection.\n");
            }
            else if (departure_city == arrival_city)
            {
                printf("Departure and arrival cities must be different.\n");
            }
        } while (get_city_index(arrival_city) == -1 || departure_city == arrival_city);

    } while (get_city_index(departure_city) == -1);

    // Find flight options (direct or with layover)
    /* Questions 3-4 */
    find_routes(departure_city, arrival_city, hours, minutes);

    return 0;
}

/* Question 1 */
/* Function to enter departure time */
void request_departure_time(int *hours, int *minutes){
    int time;
    do
    {
        printf("Enter the time in the form of a four-digit positive number (e.g. 1445): ");
        scanf("%d", &time);

        *hours = time / 100;
        *minutes = time % 100;

        if(time < 0 || time > 2359 || *minutes < 0 || *minutes >= 60)
        {
            printf("The time is not correct. Try again.\n");
        }
        else
        {
            printf("Departure time: %02d:%02d\n", *hours, *minutes);
        }
    } while (time < 0 || time > 2359 || *minutes < 0 || *minutes >= 60);
}

/* Question 2. Print city options */
/* Function to print available cities */
void print_city_options()
{
    printf("City options: \n");
    for(int i = 0; i < 10; i++)
    {
        printf("%d: %s\n", i, city_names[i]);
    }
}

/* Function that returns the city index or -1 */
/* Checks if the city selection is valid */
int get_city_index(int choice)
{
    if (choice >= 0 && choice < 10)
    {
        return  choice;
    } else
    {
        return -1;
    }
}

/* Question 3 */
/* Here the flight duration for each option will be printed. */
/* When you implement question 4 you can integrate the add_duration function here which will print the arrival time */
void find_routes(int departure, int arrival, int departure_hour, int departure_minutes)
{
    printf("\n\n************* Search Results *************\n");
    int found_direct = 0;
    /* Check direct flight */
    
    if(flight_durations[departure][arrival] != -1)
    {
        printf("Option 1: Direct flight from %s to %s. Duration: %.1f hours.\n", city_names[departure], city_names[arrival], flight_durations[departure][arrival]);
        add_duration(flight_durations[departure][arrival], departure_hour, departure_minutes);
        found_direct = 1; // Set the variable to 1 if a direct flight is found
    }
    
    int found_alternative = 0;
    int option_number = 1;
    /* Find flights with one layover */
    for (int i = 0; i < 10; i++) {
        if (i != departure && i != arrival && flight_durations[departure][i] != -1 && flight_durations[i][arrival] != -1) {
            float first_leg_duration = flight_durations[departure][i];
            float second_leg_duration = flight_durations[i][arrival];
            float total_duration = first_leg_duration + second_leg_duration;
            printf("\nOption %d: With layover at %s:\n", option_number++, city_names[i]);
            printf("Flight from %s to %s. Duration: %.1f hours.\n", city_names[departure], city_names[i], first_leg_duration);
            printf("Flight from %s to %s. Duration: %.1f hours.\n", city_names[i], city_names[arrival], second_leg_duration);
            printf("Total duration: %.1f hours.\n", total_duration);
            add_duration(total_duration, departure_hour, departure_minutes);
            found_alternative = 1; // Set the variable to 1 if a flight with one layover is found
        }
    }
    
    /* Message in case no available flights are found */
    if (!found_direct && !found_alternative)
    {
        printf("No available flights from %s to %s.\n", city_names[departure], city_names[arrival]);
    }
}

/* Question 4 */
/* The function will have parameters for hours, minutes, and duration.  */
/* The duration will be added to the hours and minutes and the new time will be printed */
/* If the new time is the next day, this information should also be printed */
void add_duration(float duration, int hours, int minutes)
{
    int total_minutes = hours * 60 + minutes + (int)(duration * 60);
    int arrival_hours = (total_minutes / 60) % 24;
    int arrival_minutes = total_minutes % 60;

    printf("The arrival time is: %02d:%02d\n", arrival_hours, arrival_minutes);
    if (total_minutes >= 1440)
    {
        printf("Note: The arrival is the next day.\n");
    }
}
