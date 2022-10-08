#define KINOVA_TAKKTILE_GRIPPER_API __attribute__ ((visibility ("default")))

extern "C"
{
    /*
    Kinova_Takktile_Gripper_Close_Serial_Port
    作用：关闭串口
    */
    KINOVA_TAKKTILE_GRIPPER_API void Close_Kinova_Takktile_Gripper_Serial_Port(void);//关闭串口

    /*
    Kinova_Takktile_Gripper_Init_Serial_Port
    作用：打开串口并初始化
    参数：port，串口名称
    返回值：
                   1：打开串口并初始化成功
                   -1：打开串口失败
    */
    KINOVA_TAKKTILE_GRIPPER_API int Init_Kinova_Takktile_Gripper_Serial_Port(char *port);

    /*
     read_finger_data
     作用：读取手指传感器读书
     参数：gripper_type：手抓类型（3：三指抓；2：二指抓）
                   gripper_id：手抓的ID号（1 ～ 254；出场默认为1）
                   finger_number：要读取的传感器位于第几根手指上（1 ～ 3；二指产品没有3）
                   finger_part：读取的传感器是在指尖部分还是在指杜部分（0：指尖，1：指杜）
     返回指：返回读取到传感器读数，共6个short类型数据；超时返回0数组
    */
    KINOVA_TAKKTILE_GRIPPER_API short* read_finger_data(unsigned char gripper_type,unsigned char gripper_id,unsigned char finger_number,unsigned char finger_part);

    /*
    read_finger_product_info
    作用：读取手指生产日期编号
    参数：gripper_type：手抓类型（3：三指抓；2：二指抓）
                   gripper_id：手抓的ID号（1 ～ 254；出场默认为1）
                   finger_number：要读取的传感器位于第几根手指上（1 ～ 3；二指产品没有3）
                   finger_part：读取的传感器是在指尖部分还是在指杜部分（0：指尖，1：指杜）
    返回指：返回读取到的生产日期编号，共5个字节，依次是生产年高字节、生产年低字节，生产月字节，生产日字节，生产序号字节；超时返回0；   
    */
    KINOVA_TAKKTILE_GRIPPER_API char* read_finger_product_info(unsigned char gripper_type,unsigned char gripper_id,unsigned char finger_number,unsigned char finger_part);

    /*
    read_palm_data
    作用：读取掌部传感器读数
    参数：gripper_type：手抓类型（3：三指抓；2：二指抓）
                   gripper_id：手抓的ID号（1 ～ 254；出场默认为1）
    返回指：返回读取到传感器读数，共15个short类型数据；超时返回0数组
    */
    KINOVA_TAKKTILE_GRIPPER_API short* read_palm_data(unsigned char gripper_type,unsigned char gripper_id);


    /*
     read_palm_product_info
    作用：读取手掌部传感器生产日期编号
    参数：gripper_type：手抓类型（3：三指抓；2：二指抓）
                   gripper_id：手抓的ID号（1 ～ 254；出场默认为1）
     返回指：返回读取到的生产日期编号，共5个字节，依次是生产年高字节、生产年低字节，生产月字节，生产日字节，生产序号字节；超时返回0；   

    */
    KINOVA_TAKKTILE_GRIPPER_API char* read_palm_product_info(unsigned char gripper_type,unsigned char gripper_id);


    /*
    calibrate_gripper_sensor
    作用：清空校正传感器读数
    参数：gripper_type：手抓类型（3：三指抓；2：二指抓）
                   gripper_id：手抓的ID号（1 ～ 254；出场默认为1）
    返回值：0：校准成功
                      负数：有传感器没有校正成功
    */
    KINOVA_TAKKTILE_GRIPPER_API int calibrate_gripper_sensor(unsigned char gripper_type,unsigned char gripper_id);


}
