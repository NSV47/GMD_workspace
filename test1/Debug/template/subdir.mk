################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../template/gw1ns4c_it.c \
../template/main.c 

OBJS += \
./template/gw1ns4c_it.o \
./template/main.o 

C_DEPS += \
./template/gw1ns4c_it.d \
./template/main.d 


# Each subdirectory must supply rules for building sources it contributes
template/%.o: ../template/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\GMD\workspace\test1\lib\CMSIS\CoreSupport\gmd" -I"C:\GMD\workspace\test1\lib\CMSIS\DeviceSupport\system" -I"C:\GMD\workspace\test1\lib\StdPeriph_Driver\Includes" -I"C:\GMD\workspace\test1\template" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


