/*
 CIS 22B Manage Activities
 File name: MA.cpp
 Purpose: Allow user to create, view, and manage events.
 
 @author Nicholas Hausch
 @version 1.0
 @since   7/29/2015
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <iomanip>
#include "Date.h"
#include "Event.h"
#include "Activity.h"

using namespace std;

// Menu string
const string MAIN_MENU = "\n 1. Display all events\n 2. Create an event\n 3. Update an event\n 4. Cancel an event\n 5. Exit\n: ";

// Function Protoypes
int commandLineArgs(int argc, char * argv[], char fileName[20]);
int copyFile(vector<Activity> &vectorOfActivities, char fileName[20]);
int testPrint(vector<Activity> &vectorOfActivities, int aVectorSize);
void checkStatus(int userStatus);
int printVectors(vector<Activity> &vectorOfActivities, int aVectorSize);
int createNew(vector<Activity> &vectorOfActivities, int aVectorSize);
int updateEvent(vector<Activity> &vectorOfActivities, int aVectorSize);
int cancelEvent(vector<Activity> &vectorOfActivities, int aVectorSize);
int saveVector(vector<Activity> &vectorOfActivities, int aVectorSize, char fileName[20]);

// Main Function
int main(int argc, char * argv[])
{
    char fileName[20];
    commandLineArgs(argc,argv,fileName);
    vector<Activity> vectorOfActivities;
    copyFile(vectorOfActivities,fileName);
    
    int aVectorSize = 0;
    
    cout << "Welcome to my event manager." << endl;
    
    int status = 0;
    
    while (status != 5) {
        
        aVectorSize = vectorOfActivities.size();
        
        cout << MAIN_MENU;
        cin >> status;
        
        if (cin.fail()) {
            cout << "Error. Program ended." << endl;
            exit(EXIT_FAILURE);
        }
        
        checkStatus(status);
        
        // If statements for each choice
        if (status == 1) {
            printVectors(vectorOfActivities,aVectorSize);
            continue;
        }
        else if (status == 2) {
            createNew(vectorOfActivities,aVectorSize);
            continue;
        }
        else if (status == 3) {
            updateEvent(vectorOfActivities,aVectorSize);
        }
        else if (status == 4) {
            cancelEvent(vectorOfActivities,aVectorSize);
        }
        else if (status == 5) {
            saveVector(vectorOfActivities,aVectorSize,fileName);
            cout << "Thank you for using my event manager." << endl << endl;
            exit(0);
        }
        else {
            cout << "Error. Program ended." << endl;
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}

// Process command line args
int commandLineArgs(int argc, char * argv[], char fileName[20])
{
    if (argc != 2) {
        cout << "Improper command line arguements." << endl;
        exit(EXIT_FAILURE);
    }
    else {
        strcpy(fileName,argv[1]);
        return 0;
    }
}

// Copy Event File
int copyFile(vector<Activity> &vectorOfActivities, char fileName[20])
{
    ifstream EventFile;
    EventFile.open(fileName, ios::in);
    
    int column = 0;
    int index = 0;
    char myCharacter;
    char myString[50];
    int myStrLen = 0;
    
    int currentID = 0;
    int currentDay, currentMonth, currentYear = 0;
    string currentDesc;
    string currentLoc;
    
    while (!EventFile.eof()) {
        
        EventFile.get(myCharacter);
        
        if (myCharacter == ' ') {
            
            if (column == 0) {
                currentID = atoi(myString);
                column++;
                index = 0;
                memset(myString,0,50);
            }
            else if (column == 1) {
                currentDay = atoi(myString);
                column++;
                index = 0;
                memset(myString,0,50);
            }
            else if (column == 2) {
                currentMonth = atoi(myString);
                column++;
                index = 0;
                memset(myString,0,50);
            }
            else if (column == 3) {
                currentYear = atoi(myString);
                column++;
                index = 0;
                memset(myString,0,50);
            }
            else if (column == 4) {
                myString[index] = myCharacter;
                index++;
            }
            else if (column == 5) {
                myString[index] = myCharacter;
                index++;
            }
            else {
                EventFile.close();
                cout << column << endl;
                cout << "Error1. Program ended." << endl;
                exit(EXIT_FAILURE);
            }
            
        }
        else if (myCharacter == '|') {
            currentDesc.assign(myString);
            index = 0;
            memset(myString,0,50);
            column++;
        }
        else if (myCharacter == '\n') {
            
            if (column == 4) {
                currentDesc.assign(myString);
                index = 0;
                memset(myString,0,50);
                column = 0;
                Activity oneActivity(currentDay,currentMonth,currentYear,currentID,currentDesc," ");
                vectorOfActivities.push_back(oneActivity);
                currentDesc.clear();
            }
            else if (column == 5) {
                
                if (myString[0] == ' ') {
                    memmove(myString, myString+1, strlen(myString));
                }
                
                currentLoc.assign(myString);
                index = 0;
                memset(myString,0,50);
                column = 0;
                if (currentDesc.back() == ' ') {
                    currentDesc.back() = '\0';
                }
                Activity oneActivity(currentDay,currentMonth,currentYear,currentID,currentDesc,currentLoc);
                vectorOfActivities.push_back(oneActivity);
                currentDesc.clear();
                currentLoc.clear();
            }
            else {
                EventFile.close();
                cout << "Error2. Program ended." << endl;
                exit(EXIT_FAILURE);
            }
        }
        else {
            myString[index] = myCharacter;
            index++;
        }
    }
    EventFile.close();
    myStrLen = strlen(myString);
    myString[myStrLen - 1] = '\0';
    if (column == 4) {
        currentDesc.assign(myString);
        Activity oneActivity(currentDay,currentMonth,currentYear,currentID,currentDesc," ");
        vectorOfActivities.push_back(oneActivity);
    }
    if (column == 5) {
        
        if (myString[0] == ' ') {
            memmove(myString, myString+1, strlen(myString));
        }
        if (currentDesc.back() == ' ') {
            currentDesc.back() = '\0';
        }
        currentLoc.assign(myString);
        Activity oneActivity(currentDay,currentMonth,currentYear,currentID,currentDesc,currentLoc);
        vectorOfActivities.push_back(oneActivity);
    }
    return 0;
}

// To test if reading was successful
int testPrint(vector<Activity> &vectorOfActivities, int aVectorSize)
{
    for (int i = 0; i < aVectorSize; i++) {
        cout << vectorOfActivities[i].getID() << " " << vectorOfActivities[i].getMonth() << " " << vectorOfActivities[i].getDay() << " " << vectorOfActivities[i].getYear() << " " << vectorOfActivities[i].getDesc();
        if ((vectorOfActivities[i].getLoc()).compare(" ") == 0) {
            cout << endl;
        }
        else {
            cout << " | " << vectorOfActivities[i].getLoc() << endl;
        }
    }
    return 0;
}

// Check to make sure the user entered 1-5
void checkStatus(int userStatus)
{
    if (userStatus < 1 || userStatus > 5) {
        cout << "Invalid selection. Program ended." << endl;
        exit(EXIT_FAILURE);
    }
}

// Print vectors with parentheses format
int printVectors(vector<Activity> &vectorOfActivities, int aVectorSize)
{
    for (int i = 0; i < aVectorSize; i++) {
        cout << setw(10) << left << vectorOfActivities[i].to_string() << setw(5) << right << vectorOfActivities[i].getID() << ": " << vectorOfActivities[i].getDesc();
        if ((vectorOfActivities[i].getLoc()).compare(" ") == 0) {
            cout << endl;
        }
        else {
            cout << " (" << vectorOfActivities[i].getLoc() << ")" << endl;
        }
    }
    
    return 0;
}

// Create a new event and add it to the vector of activities
int createNew(vector<Activity> &vectorOfActivities, int aVectorSize)
{
    int d, m, y = 0;
    int id = vectorOfActivities[aVectorSize -1].getID();
    string desc;
    string loc;
    
    if (id < 10000) {
        id = 10000;
    }
    else {
        id++;
    }
    
    cout << "Enter event date (m/d/yyyy): ";
    cin >> m; cin.ignore(); cin >> d; cin.ignore(); cin >> y;
    
    // Check for illogical dates
    if (m < 1 || m > 12 || d < 0 || d > 31) {
        cout << "Invalid date." << endl;
        return 0;
    }
    else {
        if (m == 2) {
            if (d > 28) {
                cout << "Invalid date." << endl;
                return 0;
            }
        }
        if (m == 4 || m == 6 || m == 9 || m == 11) {
            if (d > 30) {
                cout << "Invalid date." << endl;
                return 0;
            }
        }
    }
    
    cout << "Enter event description: ";
    cin.ignore();
    getline(cin,desc);
    
    cout << "Enter event location (optional - press <return> to skip): " << endl;
    getline(cin,loc);
    
    if (loc.empty()) {
        cout << "No location." << endl;
        Activity AnActivity(d,m,y,id,desc," ");
        vectorOfActivities.push_back(AnActivity);
    }
    else {
        Activity AnActivity(d,m,y,id,desc,loc);
        vectorOfActivities.push_back(AnActivity);
    }
    cout << "Event saved." << endl;
    
    return 0;
}

// Update the description or location of an event
int updateEvent(vector<Activity> &vectorOfActivities, int aVectorSize)
{
    int enteredId = 0;
    int found = 0;
    int i = 0;
    string newDesc;
    string newLoc;
    
    cout << "Enter the ID of the event: ";
    cin >> enteredId;
    for (i = 0; i < aVectorSize; i++) {
        if (vectorOfActivities[i].getID() == enteredId) {
            found = 1;
            break;
        }
        else {
            continue;
        }
    }
    
    if (found == 0) {
        cout << "Event not found." << endl;
        return 0;
    }
    
    cout << "Enter new event description: ";
    cin.ignore();
    getline(cin,newDesc);
    
    cout << "Enter new event location (optional - press <return> to skip - press <space> to delete a location): " << endl;
    getline(cin,newLoc);
    
    if (newLoc.empty()) {
        vectorOfActivities[i].updateDesc(newDesc);
        cout << "Description has been updated." << endl;
    }
    else {
        vectorOfActivities[i].updateDesc(newDesc);
        vectorOfActivities[i].updateLoc(newLoc);
        cout << "Description and location have been updated." << endl;
    }
    
    return 0;
}

// Cancel an event by deleting it from the vector of activities
int cancelEvent(vector<Activity> &vectorOfActivities, int aVectorSize)
{
    int enteredId = 0;
    int found = 0;
    int i = 0;
    
    cout << "Enter the ID of the event: ";
    cin >> enteredId;
    for (i = 0; i < aVectorSize; i++) {
        if (vectorOfActivities[i].getID() == enteredId) {
            found = 1;
            break;
        }
        else {
            continue;
        }
    }
    
    if (found == 0) {
        cout << "Event not found." << endl;
        return 0;
    }
    else {
        vectorOfActivities.erase(vectorOfActivities.begin() + i);
        cout << "Event canceled." << endl;
    }
    return 0;
}

// Save modified vector of activities to the event file
int saveVector(vector<Activity> &vectorOfActivities, int aVectorSize, char fileName[20])
{
    fstream EventFile;
    
    EventFile.open(fileName, ios::out | ios::trunc);
    
    for (int i = 0; i < aVectorSize; i++) {
        EventFile << vectorOfActivities[i].getID() << " " << vectorOfActivities[i].getMonth() << " " << vectorOfActivities[i].getDay() << " " << vectorOfActivities[i].getYear() << " " << vectorOfActivities[i].getDesc();
        if ((vectorOfActivities[i].getLoc()).compare(" ") == 0) {
            if (i != (aVectorSize - 1))
                EventFile << endl;
        }
        else {
            if (i != (aVectorSize - 1))
                EventFile << " | " << vectorOfActivities[i].getLoc() << endl;
            else
                EventFile << " | " << vectorOfActivities[i].getLoc();
        }
    }
    
    EventFile.close();
    
    return 0;
}
