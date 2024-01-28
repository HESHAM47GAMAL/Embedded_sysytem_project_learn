################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/NTC_Temperature/NTC_program.c 

OBJS += \
./HAL/NTC_Temperature/NTC_program.o 

C_DEPS += \
./HAL/NTC_Temperature/NTC_program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/NTC_Temperature/%.o: ../HAL/NTC_Temperature/%.c HAL/NTC_Temperature/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


