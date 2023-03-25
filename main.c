//
//  main.c
//  estimatecron


//  CITS2002 Project 1 2022
//  Student1:   23338559   Smith   Joel

//  Created by Joel Smith on 22/8/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Structure to store values of each command for reference
struct commands {
    char name[100];
    char execTime[10];
    char minute[60];
    char hour[24];
    char day[31];
    char month[12];
    char dayWeek[7];
    int numTimesCalled;
    
};


int dayofweek(int d, int m, int y)
{
    //magic number array
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    //maths
    return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d)
           % 7;
}

int getTime(int hour, int minute, int changeInMin){
    int totalMinutes = hour*60 + minute + changeInMin;
    
    return totalMinutes;
}

int main(int argc, const char *argv[]) {
    
    FILE *cronF;
    FILE *estiF;
    
    const char *month = argv[1];
    const char *cronFile = argv[2];
    const char *estiFile = argv[3];
    
    char input[256];
    char c;
    char *hashtag = "#";
    
    
    struct commands commandList[20];
    int numCommands = 0;
    
    
    cronF = fopen(cronFile, "r");
    estiF = fopen(estiFile, "r");
    
    for (int i = 0; i < argc; i++) {
            printf("argv[%d] = %s\n", i, argv[i]);
        }
    
    //error catches
    if (cronF == NULL){
        printf("Error: Could not find file %s", cronFile);
        return -1;
    }
    else if (estiF == NULL){
        printf("Error: Could not find file %s", estiFile);
        return -1;
    }
    else {
        printf("\n");
        printf("Month = %s\n\n", month);
        
        
        
        while (fgets(input, sizeof(input), estiF) != NULL){
            c = input[0];
            
            // ignore commented lines
            if (strncmp(&c, hashtag, 1)!=0){
                //splits into tokens and copies into struct
                char *token = strtok(input, " ");
                strcpy(commandList[numCommands].name, token);
                token = strtok(NULL, " ");
                strcpy(commandList[numCommands].execTime, token);
                commandList[numCommands].numTimesCalled = 0;
                numCommands += 1;
                }
            }


        while (fgets(input, sizeof(input), cronF) != NULL){
            c = input[0];
            if (strncmp(&c, hashtag, 1)!=0){
                
                //splits text into tokens and sets variables to copy into struct
                char *token = strtok(input, " ");
                char *minutes = (char *)token;
                token = strtok(NULL, " ");
                char *hours = (char *)token;
                token = strtok(NULL, " ");
                char *day = (char *)token;
                token = strtok(NULL, " ");
                char *month = (char *) token;
                token = strtok(NULL, " ");
                char *dayOWeek = (char *) token;
                token = strtok(NULL, " ");
                char *names = (char *) token;
               
                
                for (int i = 0; i < numCommands; i++){
                    // copies data from strtok tokens into command struct
                    if (strncmp(commandList[i].name, names, strlen(commandList[i].name))==0){
                        strcpy(commandList[i].minute, minutes);
                        strcpy(commandList[i].hour, hours);
                        strcpy(commandList[i].day, day);
                        strcpy(commandList[i].dayWeek, dayOWeek);
                        strcpy(commandList[i].month, month);
                        
                        // changes days of week to num for later
                        if (strcmp(dayOWeek, "sun")==0){
                            strcpy(commandList[i].dayWeek, "0");
                        }
                        if (strcmp(dayOWeek, "mon")==0){
                            strcpy(commandList[i].dayWeek, "1");
                        }
                        if (strcmp(dayOWeek, "tue")==0){
                            strcpy(commandList[i].dayWeek, "2");
                        }
                        if (strcmp(dayOWeek, "wed")==0){
                            strcpy(commandList[i].dayWeek, "3");
                        }
                        if (strcmp(dayOWeek, "thu")==0){
                            strcpy(commandList[i].dayWeek, "4");
                        }
                        if (strcmp(dayOWeek, "fri")==0){
                            strcpy(commandList[i].dayWeek, "5");
                        }
                        if (strcmp(dayOWeek, "sat")==0){
                            strcpy(commandList[i].dayWeek, "6");
                        }
                                                
                        
                    }
                }
                
                
                
            }
        }
        // visual conformation that all data went into the structure
        printf("\n\n");
    
        for (int i = 0; i < numCommands; i++){
            printf("%s, %s, %s, %s, %s, %s, %s\n\n", commandList[i].name, commandList[i].execTime, commandList[i].minute, commandList[i].hour, commandList[i].day, commandList[i].month, commandList[i].dayWeek);
        }
    
        printf("\n\n");
        
        
        
        
        
    }
    
    int numCommandRunning = 0;
    int maxNumCommandRunning = numCommandRunning;
    int totalNumCommCalled = 0;
    int terminatingList[20];
    int terminated = 0;
    
    char *star = "*";
    
    int actualMonth = -1;
    int dMonth = 0;
    
    //sets number of days in the month + sets a solid reference number for month
    if (strcmp(month, "jan")==0 || atoi(month) == 0){
        dMonth = 31;
        actualMonth = 0;
    }
    if (strcmp(month, "feb")==0 || atoi(month) == 1){
        dMonth = 28;
        actualMonth = 1;
    }
    if (strcmp(month, "mar")==0 || atoi(month) == 2){
        dMonth = 31;
        actualMonth = 2;
    }
    if (strcmp(month, "apr")==0 || atoi(month) == 3){
        dMonth = 30;
        actualMonth = 3;
    }
    if (strcmp(month, "may")==0 || atoi(month) == 4){
        dMonth = 31;
        actualMonth = 4;
    }
    if (strcmp(month, "jun")==0 || atoi(month) == 5){
        dMonth = 30;
        actualMonth = 5;
    }
    if (strcmp(month, "jul")==0 || atoi(month) == 6){
        dMonth = 31;
        actualMonth = 6;
    }
    if (strcmp(month, "aug")==0 || atoi(month) == 7){
        dMonth = 31;
        actualMonth = 7;
    }
    if (strcmp(month, "sep")==0 || atoi(month) == 8){
        dMonth = 30;
        actualMonth = 8;
    }
    if (strcmp(month, "oct")==0 || atoi(month) == 9){
        dMonth = 31;
        actualMonth = 9;
    }
    if (strcmp(month, "nov")==0 || atoi(month) == 10){
        dMonth = 30;
        actualMonth = 10;
    }
    if (strcmp(month, "dec")==0 || atoi(month) == 11){
        dMonth = 31;
        actualMonth = 11;
    }
    
    
    // error catch
    if (dMonth == 0){
        printf("Month %s is not valid", month);
        return -1;
    }
    
    
    
    
    //for each day in the month
    for (int day = 1; day <= dMonth; day++){
        //for each hour in the day
        for (int hour = 0; hour <= 24; hour++){
            //for each minute in each hour
            for (int minutes = 0; minutes <= 60; minutes++){
                
                
                if (maxNumCommandRunning < numCommandRunning){
                    maxNumCommandRunning = numCommandRunning;
                }
                
                //terminates commands
                if (terminatingList[terminated] == getTime(hour, minutes-1, 0)){
                    numCommandRunning -= 1;
                    terminated += 1;
                    
                }
                
                //for each command in command list checks if the time matches
                for (int i = 0; i < numCommands; i++){
                    if (atoi(commandList[i].month) == actualMonth || strcmp(commandList[i].month, star)==0){
                        if (atoi(commandList[i].day) == day || strcmp(commandList[i].day, star)==0){
                            if (atoi(commandList[i].dayWeek) == dayofweek(day, actualMonth+1, 2022) || strcmp(commandList[i].dayWeek, star)==0){
                                if (atoi(commandList[i].hour) == hour || strcmp(commandList[i].hour, star)==0){
                                    if (atoi(commandList[i].minute) == minutes || strcmp(commandList[i].minute, star)==0){
                                        
                                        commandList[i].numTimesCalled += 1;
                                        totalNumCommCalled += 1;
                                        numCommandRunning += 1;
                                        terminatingList[terminated] = getTime(hour, minutes, atoi(commandList[i].execTime));
                                        
                                        
                                        printf("called: Month = %d, Day = %i, Hour = %i, Minute = %i\n", actualMonth, day, hour, minutes);
                                        printf("dayWeek: %d\n", dayofweek(day, actualMonth, 2022));
                                        printf("%s, %s, %s, %s, %s, %s, %s\n\n", commandList[i].name, commandList[i].execTime, commandList[i].minute, commandList[i].hour, commandList[i].day, commandList[i].month, commandList[i].dayWeek);
                                        
                                        
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int mostCalled = 0;
    char *name = NULL;
    
    //determines most called command
    for (int i = 0; i < numCommands; i++){
        if (mostCalled < commandList[i].numTimesCalled){
            name = commandList[i].name;
            mostCalled = commandList[i].numTimesCalled;
        }
    }
    
    //final statement
    printf("\n\n%s    %d      %i\n", name, totalNumCommCalled, maxNumCommandRunning);
    
    
    fclose(cronF);
    fclose(estiF);
    
    return 0;
}
