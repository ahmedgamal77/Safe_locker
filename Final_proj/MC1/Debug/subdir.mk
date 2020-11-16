################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD_Driver.c \
../MC1.c \
../TIMER.c \
../UART.c \
../keypad.c 

OBJS += \
./LCD_Driver.o \
./MC1.o \
./TIMER.o \
./UART.o \
./keypad.o 

C_DEPS += \
./LCD_Driver.d \
./MC1.d \
./TIMER.d \
./UART.d \
./keypad.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


