/*
 * ControlDevice.h
 *
 * Created: 4/18/2023 12:31:33 AM
 *  Author: ehsan
 */ 


#ifndef CONTROLDEVICE_H_
#define CONTROLDEVICE_H_

#define NONE_ERROR 0
#define OVER_TEMP_ERROR 1
#define PWM_BROKEN_ERROR 2
#define SENSOR_FAILURE 3

#define SENSOR_1_ERROR 4
#define SENSOR_2_ERROR 5
#define SENSOR_3_ERROR 6

#define OVER_TEMP 80
#define DELAY_TIME_ERROR_CHECK 30000

typedef enum {
	DEVICE_NORMAL_MODE = 0,
	DEVICE_ERROR_MODE
} Device_ModeTypeDef;

typedef struct
{
	Device_ModeTypeDef mode;
	uint8_t status;
	uint8_t sensor_num;
	uint8_t Over_Temp;
	uint8_t Temp_1;
	uint8_t Temp_2;
	uint8_t Temp_3;
	uint8_t FanSpeed;
	uint8_t DutyCycle;
}Device_TypeDef;

extern Device_TypeDef Device;
void Device_Init();
void Device_Loop();
void Error_Clear();
#endif /* CONTROLDEVICE_H_ */