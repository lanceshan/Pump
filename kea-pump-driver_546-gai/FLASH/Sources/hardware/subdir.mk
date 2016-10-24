################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/hardware/HWinit.c" \
"../Sources/hardware/adc.c" \
"../Sources/hardware/eeprom.c" \
"../Sources/hardware/flash.c" \
"../Sources/hardware/gpio.c" \
"../Sources/hardware/i2c.c" \
"../Sources/hardware/led.c" \
"../Sources/hardware/timer.c" \
"../Sources/hardware/uart.c" \
"../Sources/hardware/uart0_master.c" \

C_SRCS += \
../Sources/hardware/HWinit.c \
../Sources/hardware/adc.c \
../Sources/hardware/eeprom.c \
../Sources/hardware/flash.c \
../Sources/hardware/gpio.c \
../Sources/hardware/i2c.c \
../Sources/hardware/led.c \
../Sources/hardware/timer.c \
../Sources/hardware/uart.c \
../Sources/hardware/uart0_master.c \

OBJS += \
./Sources/hardware/HWinit.o \
./Sources/hardware/adc.o \
./Sources/hardware/eeprom.o \
./Sources/hardware/flash.o \
./Sources/hardware/gpio.o \
./Sources/hardware/i2c.o \
./Sources/hardware/led.o \
./Sources/hardware/timer.o \
./Sources/hardware/uart.o \
./Sources/hardware/uart0_master.o \

OBJS_QUOTED += \
"./Sources/hardware/HWinit.o" \
"./Sources/hardware/adc.o" \
"./Sources/hardware/eeprom.o" \
"./Sources/hardware/flash.o" \
"./Sources/hardware/gpio.o" \
"./Sources/hardware/i2c.o" \
"./Sources/hardware/led.o" \
"./Sources/hardware/timer.o" \
"./Sources/hardware/uart.o" \
"./Sources/hardware/uart0_master.o" \

C_DEPS += \
./Sources/hardware/HWinit.d \
./Sources/hardware/adc.d \
./Sources/hardware/eeprom.d \
./Sources/hardware/flash.d \
./Sources/hardware/gpio.d \
./Sources/hardware/i2c.d \
./Sources/hardware/led.d \
./Sources/hardware/timer.d \
./Sources/hardware/uart.d \
./Sources/hardware/uart0_master.d \

OBJS_OS_FORMAT += \
./Sources/hardware/HWinit.o \
./Sources/hardware/adc.o \
./Sources/hardware/eeprom.o \
./Sources/hardware/flash.o \
./Sources/hardware/gpio.o \
./Sources/hardware/i2c.o \
./Sources/hardware/led.o \
./Sources/hardware/timer.o \
./Sources/hardware/uart.o \
./Sources/hardware/uart0_master.o \

C_DEPS_QUOTED += \
"./Sources/hardware/HWinit.d" \
"./Sources/hardware/adc.d" \
"./Sources/hardware/eeprom.d" \
"./Sources/hardware/flash.d" \
"./Sources/hardware/gpio.d" \
"./Sources/hardware/i2c.d" \
"./Sources/hardware/led.d" \
"./Sources/hardware/timer.d" \
"./Sources/hardware/uart.d" \
"./Sources/hardware/uart0_master.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/hardware/HWinit.o: ../Sources/hardware/HWinit.c
	@echo 'Building file: $<'
	@echo 'Executing target #49 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/hardware/HWinit.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/hardware/HWinit.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hardware/adc.o: ../Sources/hardware/adc.c
	@echo 'Building file: $<'
	@echo 'Executing target #50 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/hardware/adc.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/hardware/adc.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hardware/eeprom.o: ../Sources/hardware/eeprom.c
	@echo 'Building file: $<'
	@echo 'Executing target #51 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/hardware/eeprom.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/hardware/eeprom.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hardware/flash.o: ../Sources/hardware/flash.c
	@echo 'Building file: $<'
	@echo 'Executing target #52 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/hardware/flash.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/hardware/flash.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hardware/gpio.o: ../Sources/hardware/gpio.c
	@echo 'Building file: $<'
	@echo 'Executing target #53 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/hardware/gpio.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/hardware/gpio.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hardware/i2c.o: ../Sources/hardware/i2c.c
	@echo 'Building file: $<'
	@echo 'Executing target #54 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/hardware/i2c.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/hardware/i2c.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hardware/led.o: ../Sources/hardware/led.c
	@echo 'Building file: $<'
	@echo 'Executing target #55 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/hardware/led.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/hardware/led.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hardware/timer.o: ../Sources/hardware/timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #56 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/hardware/timer.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/hardware/timer.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hardware/uart.o: ../Sources/hardware/uart.c
	@echo 'Building file: $<'
	@echo 'Executing target #57 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/hardware/uart.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/hardware/uart.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hardware/uart0_master.o: ../Sources/hardware/uart0_master.c
	@echo 'Building file: $<'
	@echo 'Executing target #58 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/hardware/uart0_master.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/hardware/uart0_master.o"
	@echo 'Finished building: $<'
	@echo ' '


