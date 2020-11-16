################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../EEPROM.c \
../I2C.c \
../MC2.c \
../TIMER.c \
../UART.c \
../motor.c 

OBJS += \
./EEPROM.o \
./I2C.o \
./MC2.o \
./TIMER.o \
./UART.o \
./motor.o 

C_DEPS += \
./EEPROM.d \
./I2C.d \
./MC2.d \
./TIMER.d \
./UART.d \
./motor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


