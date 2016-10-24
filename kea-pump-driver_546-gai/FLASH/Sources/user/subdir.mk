################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/user/commprotocol.c" \
"../Sources/user/currentbuffer.c" \
"../Sources/user/debug.c" \
"../Sources/user/error.c" \
"../Sources/user/globalvars.c" \
"../Sources/user/midfunction.c" \
"../Sources/user/motor.c" \
"../Sources/user/statemachine.c" \

C_SRCS += \
../Sources/user/commprotocol.c \
../Sources/user/currentbuffer.c \
../Sources/user/debug.c \
../Sources/user/error.c \
../Sources/user/globalvars.c \
../Sources/user/midfunction.c \
../Sources/user/motor.c \
../Sources/user/statemachine.c \

OBJS += \
./Sources/user/commprotocol.o \
./Sources/user/currentbuffer.o \
./Sources/user/debug.o \
./Sources/user/error.o \
./Sources/user/globalvars.o \
./Sources/user/midfunction.o \
./Sources/user/motor.o \
./Sources/user/statemachine.o \

OBJS_QUOTED += \
"./Sources/user/commprotocol.o" \
"./Sources/user/currentbuffer.o" \
"./Sources/user/debug.o" \
"./Sources/user/error.o" \
"./Sources/user/globalvars.o" \
"./Sources/user/midfunction.o" \
"./Sources/user/motor.o" \
"./Sources/user/statemachine.o" \

C_DEPS += \
./Sources/user/commprotocol.d \
./Sources/user/currentbuffer.d \
./Sources/user/debug.d \
./Sources/user/error.d \
./Sources/user/globalvars.d \
./Sources/user/midfunction.d \
./Sources/user/motor.d \
./Sources/user/statemachine.d \

OBJS_OS_FORMAT += \
./Sources/user/commprotocol.o \
./Sources/user/currentbuffer.o \
./Sources/user/debug.o \
./Sources/user/error.o \
./Sources/user/globalvars.o \
./Sources/user/midfunction.o \
./Sources/user/motor.o \
./Sources/user/statemachine.o \

C_DEPS_QUOTED += \
"./Sources/user/commprotocol.d" \
"./Sources/user/currentbuffer.d" \
"./Sources/user/debug.d" \
"./Sources/user/error.d" \
"./Sources/user/globalvars.d" \
"./Sources/user/midfunction.d" \
"./Sources/user/motor.d" \
"./Sources/user/statemachine.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/user/commprotocol.o: ../Sources/user/commprotocol.c
	@echo 'Building file: $<'
	@echo 'Executing target #39 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/user/commprotocol.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/user/commprotocol.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/user/currentbuffer.o: ../Sources/user/currentbuffer.c
	@echo 'Building file: $<'
	@echo 'Executing target #40 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/user/currentbuffer.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/user/currentbuffer.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/user/debug.o: ../Sources/user/debug.c
	@echo 'Building file: $<'
	@echo 'Executing target #41 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/user/debug.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/user/debug.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/user/error.o: ../Sources/user/error.c
	@echo 'Building file: $<'
	@echo 'Executing target #42 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/user/error.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/user/error.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/user/globalvars.o: ../Sources/user/globalvars.c
	@echo 'Building file: $<'
	@echo 'Executing target #43 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/user/globalvars.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/user/globalvars.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/user/midfunction.o: ../Sources/user/midfunction.c
	@echo 'Building file: $<'
	@echo 'Executing target #44 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/user/midfunction.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/user/midfunction.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/user/motor.o: ../Sources/user/motor.c
	@echo 'Building file: $<'
	@echo 'Executing target #45 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/user/motor.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/user/motor.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/user/statemachine.o: ../Sources/user/statemachine.c
	@echo 'Building file: $<'
	@echo 'Executing target #46 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/user/statemachine.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/user/statemachine.o"
	@echo 'Finished building: $<'
	@echo ' '


