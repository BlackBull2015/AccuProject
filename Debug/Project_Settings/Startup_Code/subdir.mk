################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project_Settings/Startup_Code/startup.c \
../Project_Settings/Startup_Code/system_MKL26Z4.c 

S_UPPER_SRCS += \
../Project_Settings/Startup_Code/startup_MKL26Z4.S 

OBJS += \
./Project_Settings/Startup_Code/startup.o \
./Project_Settings/Startup_Code/startup_MKL26Z4.o \
./Project_Settings/Startup_Code/system_MKL26Z4.o 

C_DEPS += \
./Project_Settings/Startup_Code/startup.d \
./Project_Settings/Startup_Code/system_MKL26Z4.d 

S_UPPER_DEPS += \
./Project_Settings/Startup_Code/startup_MKL26Z4.d 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL26Z128VLH4" -I"../Sources" -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL26Z4/include" -I"C:\Freescale\KSDK_1.2.0\platform\devices\MKL26Z4\startup" -I"C:\Freescale\KSDK_1.2.0/platform/utilities/inc" -I"C:\Freescale\KSDK_1.2.0/platform/utilities/src" -I"C:\Freescale\KSDK_1.2.0\platform\osa\inc" -I"C:\Freescale\KSDK_1.2.0\platform\hal\inc" -I"C:\Freescale\KSDK_1.2.0\platform\drivers\inc" -I"C:\Freescale\KSDK_1.2.0\platform\system\inc" -I"C:\Freescale\KSDK_1.2.0" -I"C:\Freescale\KSDK_1.2.0/platform/system/inc" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/src/rtc" -I"C:\Freescale\KSDK_1.2.0/platform/system/src/clock" -I"C:\Freescale\KSDK_1.2.0/platform/system/src/clock/MKL26Z4" -I"D:/Project/Lab_template_v01/Board" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/inc" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/src/i2c" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -I"../" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


