/*
 * Timer0_driver.h
 *
 * Created: 24/12/2024 14:20:33
 *  Author: zezom
 */ 


#ifndef TIMER0_DRIVER_H_
#define TIMER0_DRIVER_H_
void Timer0_CTC_vInit(void);
void Timer0_waveform_non_PWM_vInit(void);
void Timer0_v_FastPWM(void);
void Timer0_v_Phase_Control_PWM(void);
void Timer0_v_FastPWM_duty_cycle(unsigned char duty_cycle);
#endif /* TIMER0_DRIVER_H_ */