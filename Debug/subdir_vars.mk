################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../CC3220SF_LAUNCHXL_FREERTOS.cmd 

SYSCFG_SRCS += \
C:/Users/Domin/CLionProjects/inter_component_communication/rover_MQTT/common.syscfg 

C_SRCS += \
../chain_queue.c \
../chain_task.c \
../claw_control.c \
./syscfg/ti_drivers_config.c \
./syscfg/ti_net_config.c \
./syscfg/ti_drivers_net_wifi_config.c \
../control_queue.c \
../debug.c \
../main_freertos.c \
../mqtt_client_app.c \
../mqtt_connect.c \
../mqtt_if.c \
../mqtt_queue.c \
../mqtt_task.c \
../mqtt_thread_state.c \
../network_if.c \
../parsing_queue.c \
../publish_queue.c \
../publish_task.c \
../sensor_task.c \
../sensor_thread_queue.c \
../sensor_thread_state.c \
../testRoverTask.c \
../testRoverTask_state.c \
../timer50.c \
../timer500.c \
../timer70.c \
../uart_term.c 

GEN_FILES += \
./syscfg/ti_drivers_config.c \
./syscfg/ti_net_config.c \
./syscfg/ti_drivers_net_wifi_config.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./chain_queue.d \
./chain_task.d \
./claw_control.d \
./syscfg/ti_drivers_config.d \
./syscfg/ti_net_config.d \
./syscfg/ti_drivers_net_wifi_config.d \
./control_queue.d \
./debug.d \
./main_freertos.d \
./mqtt_client_app.d \
./mqtt_connect.d \
./mqtt_if.d \
./mqtt_queue.d \
./mqtt_task.d \
./mqtt_thread_state.d \
./network_if.d \
./parsing_queue.d \
./publish_queue.d \
./publish_task.d \
./sensor_task.d \
./sensor_thread_queue.d \
./sensor_thread_state.d \
./testRoverTask.d \
./testRoverTask_state.d \
./timer50.d \
./timer500.d \
./timer70.d \
./uart_term.d 

OBJS += \
./chain_queue.obj \
./chain_task.obj \
./claw_control.obj \
./syscfg/ti_drivers_config.obj \
./syscfg/ti_net_config.obj \
./syscfg/ti_drivers_net_wifi_config.obj \
./control_queue.obj \
./debug.obj \
./main_freertos.obj \
./mqtt_client_app.obj \
./mqtt_connect.obj \
./mqtt_if.obj \
./mqtt_queue.obj \
./mqtt_task.obj \
./mqtt_thread_state.obj \
./network_if.obj \
./parsing_queue.obj \
./publish_queue.obj \
./publish_task.obj \
./sensor_task.obj \
./sensor_thread_queue.obj \
./sensor_thread_state.obj \
./testRoverTask.obj \
./testRoverTask_state.obj \
./timer50.obj \
./timer500.obj \
./timer70.obj \
./uart_term.obj 

GEN_MISC_FILES += \
./syscfg/ti_drivers_config.h \
./syscfg/ti_utils_build_linker.cmd.exp \
./syscfg/syscfg_c.rov.xs 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"chain_queue.obj" \
"chain_task.obj" \
"claw_control.obj" \
"syscfg\ti_drivers_config.obj" \
"syscfg\ti_net_config.obj" \
"syscfg\ti_drivers_net_wifi_config.obj" \
"control_queue.obj" \
"debug.obj" \
"main_freertos.obj" \
"mqtt_client_app.obj" \
"mqtt_connect.obj" \
"mqtt_if.obj" \
"mqtt_queue.obj" \
"mqtt_task.obj" \
"mqtt_thread_state.obj" \
"network_if.obj" \
"parsing_queue.obj" \
"publish_queue.obj" \
"publish_task.obj" \
"sensor_task.obj" \
"sensor_thread_queue.obj" \
"sensor_thread_state.obj" \
"testRoverTask.obj" \
"testRoverTask_state.obj" \
"timer50.obj" \
"timer500.obj" \
"timer70.obj" \
"uart_term.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\ti_drivers_config.h" \
"syscfg\ti_utils_build_linker.cmd.exp" \
"syscfg\syscfg_c.rov.xs" 

C_DEPS__QUOTED += \
"chain_queue.d" \
"chain_task.d" \
"claw_control.d" \
"syscfg\ti_drivers_config.d" \
"syscfg\ti_net_config.d" \
"syscfg\ti_drivers_net_wifi_config.d" \
"control_queue.d" \
"debug.d" \
"main_freertos.d" \
"mqtt_client_app.d" \
"mqtt_connect.d" \
"mqtt_if.d" \
"mqtt_queue.d" \
"mqtt_task.d" \
"mqtt_thread_state.d" \
"network_if.d" \
"parsing_queue.d" \
"publish_queue.d" \
"publish_task.d" \
"sensor_task.d" \
"sensor_thread_queue.d" \
"sensor_thread_state.d" \
"testRoverTask.d" \
"testRoverTask_state.d" \
"timer50.d" \
"timer500.d" \
"timer70.d" \
"uart_term.d" 

GEN_FILES__QUOTED += \
"syscfg\ti_drivers_config.c" \
"syscfg\ti_net_config.c" \
"syscfg\ti_drivers_net_wifi_config.c" 

C_SRCS__QUOTED += \
"../chain_queue.c" \
"../chain_task.c" \
"../claw_control.c" \
"./syscfg/ti_drivers_config.c" \
"./syscfg/ti_net_config.c" \
"./syscfg/ti_drivers_net_wifi_config.c" \
"../control_queue.c" \
"../debug.c" \
"../main_freertos.c" \
"../mqtt_client_app.c" \
"../mqtt_connect.c" \
"../mqtt_if.c" \
"../mqtt_queue.c" \
"../mqtt_task.c" \
"../mqtt_thread_state.c" \
"../network_if.c" \
"../parsing_queue.c" \
"../publish_queue.c" \
"../publish_task.c" \
"../sensor_task.c" \
"../sensor_thread_queue.c" \
"../sensor_thread_state.c" \
"../testRoverTask.c" \
"../testRoverTask_state.c" \
"../timer50.c" \
"../timer500.c" \
"../timer70.c" \
"../uart_term.c" 

SYSCFG_SRCS__QUOTED += \
"C:/Users/Domin/CLionProjects/inter_component_communication/rover_MQTT/common.syscfg" 


