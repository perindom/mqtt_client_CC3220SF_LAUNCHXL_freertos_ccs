################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me --include_path="C:/Users/Domin/workspace_v10/mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs" --include_path="C:/Users/Domin/workspace_v10/mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_4_20_00_07/source" --include_path="C:/ti/simplelink_cc32xx_sdk_4_20_00_07/source/ti/posix/ccs" --include_path="C:/FreeRTOSv202107.00/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv202107.00/FreeRTOS/Source/portable/CCS/ARM_CM3" --include_path="C:/Users/Domin/workspace_v10/freertos_builds_CC3220SF_LAUNCHXL_release_ccs" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --include_path="C:/Users/Domin/CLionProjects/inter_component_communication/rover_MQTT" --include_path="C:/Users/Domin/CLionProjects/inter_component_communication/rover_MQTT" -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/Domin/workspace_v10/mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1355208881: C:/Users/Domin/CLionProjects/inter_component_communication/rover_MQTT/common.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1040/ccs/utils/sysconfig_1.9.0/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_4_20_00_07/.metadata/product.json" --script "C:/Users/Domin/CLionProjects/inter_component_communication/rover_MQTT/common.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-1355208881 C:/Users/Domin/CLionProjects/inter_component_communication/rover_MQTT/common.syscfg
syscfg/ti_drivers_config.h: build-1355208881
syscfg/ti_net_config.c: build-1355208881
syscfg/ti_utils_build_linker.cmd.exp: build-1355208881
syscfg/syscfg_c.rov.xs: build-1355208881
syscfg/ti_drivers_net_wifi_config.c: build-1355208881
syscfg/: build-1355208881

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me --include_path="C:/Users/Domin/workspace_v10/mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs" --include_path="C:/Users/Domin/workspace_v10/mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_4_20_00_07/source" --include_path="C:/ti/simplelink_cc32xx_sdk_4_20_00_07/source/ti/posix/ccs" --include_path="C:/FreeRTOSv202107.00/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv202107.00/FreeRTOS/Source/portable/CCS/ARM_CM3" --include_path="C:/Users/Domin/workspace_v10/freertos_builds_CC3220SF_LAUNCHXL_release_ccs" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --include_path="C:/Users/Domin/CLionProjects/inter_component_communication/rover_MQTT" --include_path="C:/Users/Domin/CLionProjects/inter_component_communication/rover_MQTT" -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/Domin/workspace_v10/mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


