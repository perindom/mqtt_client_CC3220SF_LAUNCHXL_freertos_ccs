/*
 * claw_control.c
 *
 *  Created on: Nov 27, 2021
 *      Author: Domin
 */


/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "claw_control.h"

/*
 *  ======== mainThread ========
 *  Task periodically increments the PWM duty for the on board LED.
 */



void *claw_control_task(void *arg0)
{

    /* Period and duty in microseconds */
    uint16_t   pwmPeriod = 4000;
    uint16_t   claw_duty = 0;
    uint16_t   kicker_duty = 0;
    uint16_t   dutyInc = 200;

    /* Sleep time in microseconds */
    PWM_Handle pwm1 = NULL;
    PWM_Handle pwm2 = NULL;
    PWM_Params params;

    /* Call driver init functions. */
    PWM_init();

    PWM_Params_init(&params);
    params.dutyUnits = PWM_DUTY_US;
    params.dutyValue = 0;
    params.periodUnits = PWM_PERIOD_US;
    params.periodValue = pwmPeriod;
    pwm1 = PWM_open(CONFIG_PWM_0, &params);
    if (pwm1 == NULL) {
        /* CONFIG_PWM_0 did not open */
        while (1);
    }

    pwm2 = PWM_open(CONFIG_PWM_1, &params);
    if (pwm2 == NULL) {
        /* CONFIG_PWM_1 did not open */
        while (1);
    }

    PWM_start(pwm1);
    PWM_start(pwm2);

    CONTMsg_t control_command;
    int current_order;

    claw_duty = 0;
    PWM_setDuty(pwm1,claw_duty);

    PWM_setDuty(pwm2, kicker_duty);

    int state = IDLE_STATE;

    //create kick variables
    int opened = 0;
    int kicked = 0;
    int retracted = 0;
    publish_message_t done_message;

    start50();

    int cx = snprintf(done_message.topic, MAX_STR_LEN, "Claw_Response");
    if (cx < 0)
    {
        //Error condition
        //while(1);
    }

    cx = snprintf(done_message.json_string, MAX_STR_LEN, "{ \"Done\" }");
    if (cx < 0)
    {
        //Error condition
        //while(1);
    }

    /* Loop forever incrementing the PWM duty */
    while (1) {
        retrieve_from_control_queue(&control_command);

        if (state == IDLE_STATE) {
            if (control_command.topic == timer){
                continue;
            }
            else if (control_command.topic == control){
                current_order = control_command.message;
                state = MOVING_STATE;
            }
        }
        else if (state == MOVING_STATE) {

            switch(current_order)
            {
                case CLAW_OPEN:
                    if (claw_duty < pwmPeriod)
                    {
                        claw_duty = claw_duty + dutyInc;
                        PWM_setDuty(pwm1, claw_duty);
                    }
                    else
                        current_order = DONE;
                break;

                case CLAW_CLOSE:
                    if (claw_duty > 0)
                    {
                        claw_duty = claw_duty - dutyInc;
                        PWM_setDuty(pwm1, claw_duty);
                    }
                    else
                        current_order = DONE;
                break;

                case KICK:

                    if (!opened){
                        if (claw_duty < pwmPeriod) {
                            claw_duty = claw_duty + dutyInc;
                            PWM_setDuty(pwm1, claw_duty);
                        }
                        else
                            opened = 1;
                    }
                    else if (opened && !kicked) {
                        if (kicker_duty < 0.5*pwmPeriod)
                        {
                            kicker_duty = kicker_duty + dutyInc;
                            PWM_setDuty(pwm2, kicker_duty);
                        }
                        else
                            kicked = 1;
                    }
                    else if (kicked && !retracted) {
                        if (kicker_duty > 0)
                        {
                            kicker_duty = kicker_duty - 0.5*dutyInc;
                            PWM_setDuty(pwm2, kicker_duty);
                        }
                        else
                            kicked = 1;

                    }
                    else {
                        opened = 0;
                        kicked = 0;
                        retracted = 0;
                        current_order = DONE;
                    }
                break;

                case DONE:
                    add_to_publish_queue(&done_message);
                    state = IDLE_STATE;
                break;
                }

            }
    }
}
