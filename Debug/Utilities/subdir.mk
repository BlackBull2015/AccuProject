################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/fsl_debug_console.c \
../Utilities/print_scan.c 

OBJS += \
./Utilities/fsl_debug_console.o \
./Utilities/print_scan.o 

C_DEPS += \
./Utilities/fsl_debug_console.d \
./Utilities/print_scan.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/%.o: ../Utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL26Z128VLH4" -I"../Sources" -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL26Z4/include" -I"C:\Freescale\KSDK_1.2.0\platform\devices\MKL26Z4\startup" -I"C:\Freescale\KSDK_1.2.0/platform/utilities/inc" -I"C:\Freescale\KSDK_1.2.0/platform/utilities/src" -I"C:\Freescale\KSDK_1.2.0\platform\osa\inc" -I"C:\Freescale\KSDK_1.2.0\platform\hal\inc" -I"C:\Freescale\KSDK_1.2.0\platform\drivers\inc" -I"C:\Freescale\KSDK_1.2.0\platform\system\inc" -I"C:\Freescale\KSDK_1.2.0" -I"C:\Freescale\KSDK_1.2.0/platform/system/inc" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/src/rtc" -I"C:\Freescale\KSDK_1.2.0/platform/system/src/clock" -I"C:\Freescale\KSDK_1.2.0/platform/system/src/clock/MKL26Z4" -I"D:/Project/Lab_template_v01/Board" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/inc" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/src/i2c" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


