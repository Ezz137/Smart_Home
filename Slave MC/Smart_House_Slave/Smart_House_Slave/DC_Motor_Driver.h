/*
 * DC_Motor_Driver.h
 *
 * Created: 05/01/2025 01:17:40
 *  Author: zezom
 */ 


#ifndef DC_MOTOR_DRIVER_H_
#define DC_MOTOR_DRIVER_H_
void DC_Motor_vInit (void);
void DC_Motor_AC_vSpeed_control (unsigned char duty_cycle);
void DC_Motor_Heater_vSpeed_control (unsigned char duty_cycle);
void DC_Motor_AC_vTurn_on_Anticlockwise (void);
void DC_Motor_Heater_vTurn_on_Anticlockwise (void);
void DC_Motor_AC_vTurn_off (void);
void DC_Motor_Heater_vTurn_off (void);
/*void DC_Motor_AC_vTurn_on_clockwise (void);
void DC_Motor_Heater_vTurn_on_clockwise (void);*/
#endif /* DC_MOTOR_DRIVER_H_ */