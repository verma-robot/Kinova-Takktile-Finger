#include <ros/ros.h>
#include <ros/time.h>
#include <iostream>
#include <std_msgs/Int32.h>
#include  "kinova_takktile_gripper_msgs/kg3_gripper.h"
#include  "kinova_takktile_gripper_msgs/kg2_gripper.h"
#include "kinova_takktile_gripper.h"
#include <std_srvs/Empty.h>

bool CALIBRATE_ALL_SENSOR_FLAG = false;

bool calibrate_all_sensors(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res) 
{
  CALIBRATE_ALL_SENSOR_FLAG =  true;
  return true;
};

int main(int argc, char** argv)
{

	ros::init(argc, argv, "Kinova_Takktile_Gripper_Node");	
    ros::NodeHandle nh("~");  

    std::string port_name; 
    char port[100];
    std::string ns; 

    int gripper_type;
    int gripper_id;

    nh.getParam("port_name", port_name);//串口名称
    nh.getParam("gripper_type", gripper_type);//串口名称
    nh.getParam("gripper_id", gripper_id);//串口名称

    strcpy(port, port_name.c_str());

    if(gripper_type != 3 && gripper_type != 2)
    {
        ROS_ERROR("Gripper Type Error");
        return 0;
    }

    if(gripper_id <1 ||   gripper_id  > 254)
    {
        ROS_ERROR("Gripper ID Error");
        return 0;
    }
    kinova_takktile_gripper_driver driver(port);

    if(driver.serial_port_ready > 0)//串口ready
    {
        char* produc_info;
        union produce_year
        {
            char data[2];
            unsigned short p_da;
        };

        union produce_year pro_;
        produc_info = (char *)malloc(5 * sizeof(char));
        produc_info = driver.read_palm_product_info((unsigned char)gripper_type,(unsigned char)gripper_id);

        if(produc_info[0] != 0)
        {
            pro_.data[1] = produc_info[0];
            pro_.data[0] = produc_info[1];
          
            std::cout<< "Palm Sensor  No.:  "<<(int)pro_.p_da << (int)produc_info[2] << (int)produc_info[3]<<(int)produc_info[4]<< std::endl;
        }

       produc_info = driver.read_finger_product_info((unsigned char)gripper_type,(unsigned char)gripper_id,1,0);

        if(produc_info[0] != 0)
        {
            pro_.data[1] = produc_info[0];
            pro_.data[0] = produc_info[1];
          
            std::cout<< "The Fingertips Sensor Seral No.  of The Fisrt Finger  :  "<<(int)pro_.p_da << (int)produc_info[2] << (int)produc_info[3]<<(int)produc_info[4]<< std::endl;
        }

        produc_info = driver.read_finger_product_info((unsigned char)gripper_type,(unsigned char)gripper_id,1,1);

        if(produc_info[0] != 0)
        {
            pro_.data[1] = produc_info[0];
            pro_.data[0] = produc_info[1];
          
            std::cout<< "The finger_proximal Sensors of the First Finger  :  "<<(int)pro_.p_da << (int)produc_info[2] << (int)produc_info[3]<<(int)produc_info[4]<< std::endl;
        }


       produc_info = driver.read_finger_product_info((unsigned char)gripper_type,(unsigned char)gripper_id,2,0);

        if(produc_info[0] != 0)
        {
            pro_.data[1] = produc_info[0];
            pro_.data[0] = produc_info[1];
          
            std::cout<< "The Fingertips Sensor of The Second Finger  :  "<<(int)pro_.p_da << (int)produc_info[2] << (int)produc_info[3]<<(int)produc_info[4]<< std::endl;
        }

        produc_info = driver.read_finger_product_info((unsigned char)gripper_type,(unsigned char)gripper_id,2,1);

        if(produc_info[0] != 0)
        {
            pro_.data[1] = produc_info[0];
            pro_.data[0] = produc_info[1];
          
            std::cout<< "The finger_proximal Sensors of the Second Finger  :  "<<(int)pro_.p_da << (int)produc_info[2] << (int)produc_info[3]<<(int)produc_info[4]<< std::endl;
        }

        if(gripper_type == 3)
        {
            produc_info = driver.read_finger_product_info((unsigned char)gripper_type,(unsigned char)gripper_id,3,0);

            if(produc_info[0] != 0)
            {
                pro_.data[1] = produc_info[0];
                pro_.data[0] = produc_info[1];
          
                std::cout<< "The Fingertips Sensor of The Third Finger  :  "<<(int)pro_.p_da << (int)produc_info[2] << (int)produc_info[3]<<(int)produc_info[4]<< std::endl;
            }

            produc_info = driver.read_finger_product_info((unsigned char)gripper_type,(unsigned char)gripper_id,3,1);

            if(produc_info[0] != 0)
            {
                pro_.data[1] = produc_info[0];
                pro_.data[0] = produc_info[1];
          
                std::cout<< "The finger_proximal Sensors of the Third Finger  :  "<<(int)pro_.p_da << (int)produc_info[2] << (int)produc_info[3]<<(int)produc_info[4]<< std::endl;
            }
        }
        free(produc_info);
    }    
    
    ros::Publisher takktile_sensor_pub;
    ros::ServiceServer calibrate_sensors;
    if(gripper_type == 3)
    {
        takktile_sensor_pub = nh.advertise<kinova_takktile_gripper_msgs::kg3_gripper>( "/kinova_takktile_sensor", 50);
        calibrate_sensors =   nh.advertiseService<std_srvs::Empty::Request, std_srvs::Empty::Response> ("/calibrate_all_sensors", calibrate_all_sensors);
    }
    else if(gripper_type == 2)
    {
        takktile_sensor_pub = nh.advertise<kinova_takktile_gripper_msgs::kg2_gripper>( "/kinova_takktile_sensor", 50);
        calibrate_sensors =   nh.advertiseService<std_srvs::Empty::Request, std_srvs::Empty::Response> ("/calibrate_all_sensors", calibrate_all_sensors);
    }

	ros::Rate loop_rate(20);

    ros::Time::init();


	while (ros::ok()) 
	{
            try
            {
                if(gripper_type == 3)
                {
                    kinova_takktile_gripper_msgs::kg3_gripper all_data;
                    short* sensor_data; 
                    sensor_data = (short *)malloc(15 * sizeof(short));

                    if(CALIBRATE_ALL_SENSOR_FLAG)//需要校准
                    {
                        driver.calibrate_gripper_sensor((unsigned char)gripper_type,(unsigned char)gripper_id);
                        CALIBRATE_ALL_SENSOR_FLAG = false;
                    }
                    sensor_data = driver.read_palm_data((unsigned char)gripper_type,(unsigned char)gripper_id);
                    for(int i = 0; i < 15;i++)all_data.palm.sensor[i] = sensor_data[i];

                    free(sensor_data);//释放
                    sensor_data = (short *)malloc(6 * sizeof(short));
                    sensor_data = driver.read_finger_data((unsigned char)gripper_type,(unsigned char)gripper_id,1,0);
                    for(int i = 0; i < 6;i++)all_data.finger_sensor[0].finger_tip_sensor.sensor[i] = sensor_data[i];

                    sensor_data = driver.read_finger_data((unsigned char)gripper_type,(unsigned char)gripper_id,1,1);
                    for(int i = 0; i < 6;i++)all_data.finger_sensor[0].finger_proximal_sensor.sensor[i] = sensor_data[i];

                    sensor_data = driver.read_finger_data((unsigned char)gripper_type,(unsigned char)gripper_id,2,0);
                    for(int i = 0; i < 6;i++)all_data.finger_sensor[1].finger_tip_sensor.sensor[i] = sensor_data[i];

                    sensor_data = driver.read_finger_data((unsigned char)gripper_type,(unsigned char)gripper_id,2,1);
                    for(int i = 0; i < 6;i++)all_data.finger_sensor[1].finger_proximal_sensor.sensor[i] = sensor_data[i];

                    sensor_data = driver.read_finger_data((unsigned char)gripper_type,(unsigned char)gripper_id,3,0);
                    for(int i = 0; i < 6;i++)all_data.finger_sensor[2].finger_tip_sensor.sensor[i] = sensor_data[i];

                    sensor_data = driver.read_finger_data((unsigned char)gripper_type,(unsigned char)gripper_id,3,1);
                    for(int i = 0; i < 6;i++)all_data.finger_sensor[2].finger_proximal_sensor.sensor[i] = sensor_data[i];
                    takktile_sensor_pub.publish(all_data);
                }
                else if(gripper_type == 2)
                {
                   kinova_takktile_gripper_msgs::kg2_gripper all_data;
                    short* sensor_data; 
                    sensor_data = (short *)malloc(15 * sizeof(short));

                    if(CALIBRATE_ALL_SENSOR_FLAG)//需要校准
                    {
                        driver.calibrate_gripper_sensor((unsigned char)gripper_type,(unsigned char)gripper_id);
                        CALIBRATE_ALL_SENSOR_FLAG = false;
                    }
                    sensor_data = driver.read_palm_data((unsigned char)gripper_type,(unsigned char)gripper_id);
                    for(int i = 0; i < 15;i++)all_data.palm.sensor[i] = sensor_data[i];

                    free(sensor_data);//释放
                    sensor_data = (short *)malloc(6 * sizeof(short));
                    sensor_data = driver.read_finger_data((unsigned char)gripper_type,(unsigned char)gripper_id,1,0);
                    for(int i = 0; i < 6;i++)all_data.finger_sensor[0].finger_tip_sensor.sensor[i] = sensor_data[i];

                    sensor_data = driver.read_finger_data((unsigned char)gripper_type,(unsigned char)gripper_id,1,1);
                    for(int i = 0; i < 6;i++)all_data.finger_sensor[0].finger_proximal_sensor.sensor[i] = sensor_data[i];

                    sensor_data = driver.read_finger_data((unsigned char)gripper_type,(unsigned char)gripper_id,2,0);
                    for(int i = 0; i < 6;i++)all_data.finger_sensor[1].finger_tip_sensor.sensor[i] = sensor_data[i];

                    sensor_data = driver.read_finger_data((unsigned char)gripper_type,(unsigned char)gripper_id,2,1);
                    for(int i = 0; i < 6;i++)all_data.finger_sensor[1].finger_proximal_sensor.sensor[i] = sensor_data[i];

                    takktile_sensor_pub.publish(all_data);

                } 
	            ros::spinOnce();
	            loop_rate.sleep();
            }
            catch(const std::exception& e)
            {
		            ROS_ERROR("//////////////ERROR/////////////.");
            }
	}
	return 0;
}


