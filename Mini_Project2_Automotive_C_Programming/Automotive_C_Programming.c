#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Structure
typedef struct engines
{
    char Engine_State [5];      // 0 , 1 .... on , off
    char Engine_Temp_Controler_State[5];
    signed int Engine_Temp;
}engine;

// Structure of structures
typedef struct Vehicles
{
    char AC_State[5];        //  air conditioning 0,1 ... on, off
    unsigned int Vehicle_Speed;
    signed int Room_Temp;
    engine Engine;
}vehicles;


// Constants
#define OFF                 "OFF"
#define SPEED               0
#define Init_Room_Temp      35
#define Init_Engine_Temp    20


// Global Variables
vehicles Vehicle;


void Vehicle_Initialization()
{
    // Struct initialization
    strcpy(Vehicle.AC_State , OFF);
    Vehicle.Vehicle_Speed = SPEED;
    Vehicle.Room_Temp = Init_Room_Temp;

    strcpy(Vehicle.Engine.Engine_State , OFF);
    strcpy(Vehicle.Engine.Engine_Temp_Controler_State , OFF);
    Vehicle.Engine.Engine_Temp = Init_Engine_Temp;
}


void Menu()
{
    printf("\n Welcome to Automotive System! \n");
    printf("1. Turn on the vehicle engine \n");
    printf("2. Turn off the vehicle engine \n");
    printf("3. Clear the cmd \n");
    printf("4. Quit the system \n");

    unsigned char choice = "\0";
    printf("\n Enter Choice: \t");
    scanf(" %[^\n]s", &choice);   // error    scanf("%d \n", &choice);

    switch(choice)
    {
        case '1'  :   Turn_On_Engine();             break;
        case '2'  :   Turn_Off_Engine();            break;
        case '3'  :    Clear_CMD();     Menu();     break;
        case '4'  :   Exit();                       break;
        default   :   Menu();                       break;
    }
}


void Sensor_Set_Menu()
{
    printf("\n What do you want to do ?! \n");
    printf("1. Turn off the vehicle engine \n");
    printf("2. Set the traffic light color \n");
    printf("3. Set the room temperature (Temperature Sensor) \n");
    printf("4. Set the engine temperature (Engine Temperature Sensor) \n");
    printf("5. Return to the Sensor Set Menu \n");
    printf("6. Clear the cmd \n");


    unsigned char choice = "\0";
    printf("\n Enter Choice: \t");
    scanf(" %[^\n]s", &choice);   // error    scanf("%d \n", &choice);

    switch(choice)
    {
        case '1'  :    Turn_Off_Engine();                           break;
        case '2'  :    Set_Traffic_Light_Color();                   break;
        case '3'  :    Set_Room_Temp();                             break;
        case '4'  :    Set_Engine_Temp();                           break;
        case '5'  :    Sensor_Set_Menu();                           break;
        case '6'  :    Clear_CMD();     Sensor_Set_Menu();          break;
        default   :                                                 break;
    }
}



void Turn_On_Engine()
{
    if(strcmp(Vehicle.Engine.Engine_State , "OFF") == 0)
    {
        // Turn ON the engine
        printf("The Engine is starting !\n");
        strcpy(Vehicle.Engine.Engine_State , "ON");
        printf("Now, the Engine State is: %s\n", Vehicle.Engine.Engine_State);  // print the system state
    }
    else if(strcmp(Vehicle.Engine.Engine_State , "ON") == 0)
    {
        printf("The Engine is already: %s\n", Vehicle.Engine.Engine_State);   // print the system state
    }

    while(strcmp(Vehicle.Engine.Engine_State , "ON") == 0)
    {
        Sensor_Set_Menu();   // display the sensors set menu that simulates the vehicle sensors readings

        if(Vehicle.Vehicle_Speed == 30) //check the vehicle speed if = 30 km/hr
        {
            //Turn ON AC if it was OFF and set room temperature to: current temperature * (5/4) + 1
            if(strcmp(Vehicle.AC_State , "ON") == 0)
            {
                printf("The Air Conditioning is already ON \n");
            }
            else if(strcmp(Vehicle.AC_State , "OFF") == 0)
            {
                strcpy(Vehicle.AC_State , "ON");    //Turn AC ON
            }
            Vehicle.Room_Temp = Vehicle.Room_Temp*(5/4) + 1; //set room temperature to current temperature * (5/4) + 1


            //Turn ON “Engine Temperature Controller” if it was OFF and set engine temperature to: current temperature * (5/4) + 1
            if(strcmp(Vehicle.Engine.Engine_Temp_Controler_State , "ON") == 0)
            {
                printf("The Engine Temperature Controller is already ON \n");
            }
            else if(strcmp(Vehicle.Engine.Engine_Temp_Controler_State , "OFF") == 0)
            {
                strcpy(Vehicle.Engine.Engine_Temp_Controler_State , "ON");    //Turn the Engine Temperature Controller ON
            }
            Vehicle.Engine.Engine_Temp = Vehicle.Engine.Engine_Temp*(5/4) + 1; //set engine temperature to current temperature * (5/4) + 1
        }

        Display_Vehicle_State();
    }
}


void Turn_Off_Engine()
{
    if(strcmp(Vehicle.Engine.Engine_State , "ON") == 0)
    {
        // Turn off the engine
        printf("The Engine shutdown !\n");
        //strcpy(Vehicle.Engine.Engine_State , "OFF");
        Vehicle_Initialization();
        printf("Now, The Engine is: %s\n", Vehicle.Engine.Engine_State);  // print the system state
    }
    else if(strcmp(Vehicle.Engine.Engine_State , "OFF") == 0)
    {
        printf("The Engine is already: %s\n", Vehicle.Engine.Engine_State);   // print the system state
    }

    Menu();     // Ask hin/her again
}



void Set_Traffic_Light_Color()
{
    char Light_Color = "NULL";
    printf("Enter the traffic light color: \n");    //get the traffic light data >>> take it from user assume that it is the sensor read value
    printf("'G': Green \n'O': Orange \n'R': Red \n");
    scanf(" %[^\n]s", &Light_Color);

    switch(Light_Color)
    {
        case 'G':   Vehicle.Vehicle_Speed = 100;            break;  //If the traffic light is ‘G’ set vehicle speed to 100 km/hr
        case 'O':   Vehicle.Vehicle_Speed = 30;             break;  //If the traffic light is ‘O’ set vehicle speed to 30 km/hr
        case 'R':   Vehicle.Vehicle_Speed = 0;              break;  //If the traffic light is ‘R’ set vehicle speed to 0 km/h
        default :   printf("Invalid Input, Try again \n");
                    Set_Traffic_Light_Color();              break;
    }
}


void Set_Room_Temp()
{
    signed int Room_Temperature;
    printf("Enter the room temperature: \n");    //get the room temperature data >>> take it from user assume that it is the sensor read value
    scanf("%d", &Room_Temperature);

    if(Room_Temperature < 10)//If temperature is less than 10
    {
        if(strcmp(Vehicle.AC_State , "ON") == 0)
        {
            printf("The Air Conditioning is already ON \n");
        }
        else if(strcmp(Vehicle.AC_State , "OFF") == 0)
        {
            strcpy(Vehicle.AC_State , "ON");    //Turn AC ON
        }
        Vehicle.Room_Temp = 20; //set temperature to 20
    }

    else if(Room_Temperature > 30)//If temperature is greater than 30
    {
        if(strcmp(Vehicle.AC_State , "ON") == 0)
        {
            printf("The Air Conditioning is already ON \n");
        }
        else if(strcmp(Vehicle.AC_State , "OFF") == 0)
        {
            strcpy(Vehicle.AC_State , "ON");    //Turn AC ON
        }
        Vehicle.Room_Temp = 20; //set temperature to 20
    }
    else    //If temperature is otherwise
    {
        strcpy(Vehicle.AC_State , "OFF");    //Turn AC OFF
    }
}


void Set_Engine_Temp()
{
    signed int Engine_Temperature;
    printf("Enter the engine temperature: \n");    //get the engine temperature data >>> take it from user assume that it is the sensor read value
    scanf("%d", &Engine_Temperature);

    if(Engine_Temperature < 100)//If temperature is less than 100
    {
        if(strcmp(Vehicle.Engine.Engine_Temp_Controler_State , "ON") == 0)
        {
            printf("The Engine Temperature Controller is already ON \n");
        }
        else if(strcmp(Vehicle.Engine.Engine_Temp_Controler_State , "OFF") == 0)
        {
            strcpy(Vehicle.Engine.Engine_Temp_Controler_State , "ON");    //Turn the Engine Temperature Controller ON
        }
        Vehicle.Engine.Engine_Temp = 125; //set temperature to 125
    }

    else if(Engine_Temperature > 150)//If temperature is greater than 150
    {
        if(strcmp(Vehicle.Engine.Engine_Temp_Controler_State , "ON") == 0)
        {
            printf("The Engine Temperature Controller is already ON \n");
        }
        else if(strcmp(Vehicle.Engine.Engine_Temp_Controler_State , "OFF") == 0)
        {
            strcpy(Vehicle.Engine.Engine_Temp_Controler_State , "ON");    //Turn the Engine Temperature Controller ON
        }
        Vehicle.Engine.Engine_Temp = 125; //set temperature to 125
    }
    else    //If temperature is otherwise
    {
        strcpy(Vehicle.Engine.Engine_Temp_Controler_State , "OFF");    //Turn the Engine Temperature Controller OFF
    }
}


void Display_Vehicle_State()
{
    printf("Engine State: %s \n", Vehicle.Engine.Engine_State);     //Engine state: ON/OFF
    printf("Vehicle Speed: %d \n", Vehicle.Vehicle_Speed);          //Vehicle Speed

    printf("Air Conditioning State: %s \n", Vehicle.AC_State);      // AC: ON/OFF
    printf("Room Temperature: %d \n", Vehicle.Room_Temp);           //Room Temperature

    printf("Engine Temperature Controller State: %s \n", Vehicle.Engine.Engine_Temp_Controler_State);   //Engine Temperature Controller State.
    printf("Engine Temperature: %d \n", Vehicle.Engine.Engine_Temp);    //Engine Temperature
}


void Clear_CMD()
{
    system("cls");  // clear the cmd
}


void Exit()
{
    //return 0;
    Exit(EXIT_SUCCESS); //Exit(0);
}



















