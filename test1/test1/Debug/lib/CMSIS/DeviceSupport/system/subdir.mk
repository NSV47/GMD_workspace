################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/CMSIS/DeviceSupport/system/system_gw1ns4c.c 

OBJS += \
./lib/CMSIS/DeviceSupport/system/system_gw1ns4c.o 

C_DEPS += \
./lib/CMSIS/DeviceSupport/system/system_gw1ns4c.d 


# Each subdirectory must supply rules for building sources it contributes
lib/CMSIS/DeviceSupport/system/%.o: ../lib/CMSIS/DeviceSupport/system/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\GMD\workspace\test1\test1\lib\CMSIS\CoreSupport\gmd" -I"C:\GMD\workspace\test1\test1\lib\CMSIS\DeviceSupport\system" -I"C:\GMD\workspace\test1\test1\lib\StdPeriph_Driver\Includes" -I"C:\GMD\workspace\test1\test1\template" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


