#ifndef KINOVA_TAKKTILE_GRIPPER_DRIVER_H
#define KINOVA_TAKKTILE_GRIPPER_DRIVER_H

#include "kinova_takktile_gripper_api.h"
#include <dlfcn.h>
#include <iostream>
#include <cstring>
#include <cassert>
 #include<algorithm>

 using namespace std;

#define KINOVA_TAKKTILE_GRIPPER_DRIVER_LIBRARY  "kinova_takktile_gripper_api.so"

class kinova_takktile_gripper_driver
{
    public:
                    kinova_takktile_gripper_driver(char *port);
                   ~kinova_takktile_gripper_driver();

                   void (*Close_Kinova_Takktile_Gripper_Serial_Port)(void);
                   int (*Init_Kinova_Takktile_Gripper_Serial_Port)(char*);                   
                 
                   short* (*read_finger_data)(unsigned char,unsigned char,unsigned char,unsigned char);
                   char* (*read_finger_product_info)(unsigned char,unsigned char,unsigned char,unsigned char);

                   short* (*read_palm_data)(unsigned char,unsigned char);

                   char* (*read_palm_product_info)(unsigned char,unsigned char);
                   int (*calibrate_gripper_sensor)(unsigned char,unsigned char);  

                   int loadLibraries(const char *command_lib);
                   void* initCommandLayerFunction(const char* name);


                   int InitializeKinovaTakktileGripperDriverFunctions(void);

                   int serial_port_ready;

    private:
                    void *API_command_lib_;
};
#endif 
