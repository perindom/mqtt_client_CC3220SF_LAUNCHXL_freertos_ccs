################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
json_files/cJSON.obj: C:/Users/Domin/CLionProjects/inter_component_communication/rover_MQTT/json_files/cJSON.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me --include_path="C:/Users/Domin/workspace_v10/mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs" --include_path="C:/Users/Domin/workspace_v10/mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_4_20_00_07/source" --include_path="C:/ti/simplelink_cc32xx_sdk_4_20_00_07/source/ti/posix/ccs" --include_path="C:/FreeRTOSv202107.00/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv202107.00/FreeRTOS/Source/portable/CCS/ARM_CM3" --include_path="C:/Users/Domin/workspace_v10/freertos_builds_CC3220SF_LAUNCHXL_release_ccs" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --include_path="C:/Users/Domin/CLionProjects/inter_component_communication/rover_MQTT" --include_path="C:/Users/Domin/CLionProjects/inter_component_communication/rover_MQTT" -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="json_files/$(basename $(<F)).d_raw" --include_path="C:/Users/Domin/workspace_v10/mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs/Debug/syscfg" --obj_directory="json_files" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


