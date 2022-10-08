#include "kinova_takktile_gripper.h"

kinova_takktile_gripper_driver::kinova_takktile_gripper_driver(char *port):serial_port_ready(-1)
{
    if(InitializeKinovaTakktileGripperDriverFunctions())//加载动态链接库成功
    {
        std::cout<<"Load Kinova Takktile Gripper DLL Libarary success...................."<<std::endl;

       serial_port_ready = Init_Kinova_Takktile_Gripper_Serial_Port(port);//初始化串口
       if(serial_port_ready > 0)//串口已经准备好
       {
           std::cout<<"Kinova Takktile Gripper Serial Port is ready............."<<  std::endl;            
       }
    }
}

kinova_takktile_gripper_driver::~kinova_takktile_gripper_driver()
{
    Close_Kinova_Takktile_Gripper_Serial_Port();
}



int kinova_takktile_gripper_driver::loadLibraries(const char *command_lib)
{
    API_command_lib_  = dlopen(command_lib,  RTLD_NOW | RTLD_GLOBAL);
    if (API_command_lib_ == NULL)
    {
        return 0;
    }
    return 1;
}  

void* kinova_takktile_gripper_driver::initCommandLayerFunction(const char* name)
{
    char functionName[100];
    strcpy(functionName,name);  
    void * function_pointer = dlsym(API_command_lib_, functionName);
    assert(function_pointer != NULL);
    return function_pointer;
}


int kinova_takktile_gripper_driver::InitializeKinovaTakktileGripperDriverFunctions(void)
{
    int load_ok = loadLibraries(KINOVA_TAKKTILE_GRIPPER_DRIVER_LIBRARY);//加载动态链接库
    if(load_ok == 0)return -1;

    Close_Kinova_Takktile_Gripper_Serial_Port = (void (*)())initCommandLayerFunction("Close_Kinova_Takktile_Gripper_Serial_Port");
    Init_Kinova_Takktile_Gripper_Serial_Port = (int (*)(char*))initCommandLayerFunction("Init_Kinova_Takktile_Gripper_Serial_Port");

    read_finger_data = (short* (*)(unsigned char,unsigned char,unsigned char,unsigned char))initCommandLayerFunction("read_finger_data");
    read_finger_product_info = (char* (*)(unsigned char,unsigned char,unsigned char,unsigned char))initCommandLayerFunction("read_finger_product_info");

    read_palm_data = (short* (*)(unsigned char,unsigned char))initCommandLayerFunction("read_palm_data");
    read_palm_product_info = (char* (*)(unsigned char,unsigned char))initCommandLayerFunction("read_palm_product_info");

    calibrate_gripper_sensor = (int (*)(unsigned char,unsigned char))initCommandLayerFunction("calibrate_gripper_sensor");


    return 1;   
}
