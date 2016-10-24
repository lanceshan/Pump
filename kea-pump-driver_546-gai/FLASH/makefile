################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 83
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Static_Code/System/subdir.mk
-include Static_Code/Peripherals/subdir.mk
-include Sources/user/subdir.mk
-include Sources/subdir.mk
-include Sources/hardware/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Generated_Code/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
kea-pump.elf \

EXECUTABLES_QUOTED += \
"kea-pump.elf" \

EXECUTABLES_OS_FORMAT += \
kea-pump.elf \

SECONDARY_FLASH += \
kea-pump.hex \

SECONDARY_FLASH_QUOTED += \
"kea-pump.hex" \

SECONDARY_FLASH_OS_FORMAT += \
kea-pump.hex \

SECONDARY_LIST += \
kea-pump.lst \

SECONDARY_LIST_QUOTED += \
"kea-pump.lst" \

SECONDARY_LIST_OS_FORMAT += \
kea-pump.lst \

SECONDARY_SIZE += \
kea-pump.siz \

SECONDARY_SIZE_QUOTED += \
"kea-pump.siz" \

SECONDARY_SIZE_OS_FORMAT += \
kea-pump.siz \


# All Target
all: warning-messages explicit-dependencies kea-pump.elf secondary-outputs

# Tool invocations
kea-pump.elf: $(OBJS) $(USER_OBJS) ../Project_Settings/Linker_Files/ProcessorExpert.ld
	@echo 'Building target: $@'
	@echo 'Executing target #84 $@'
	@echo 'Invoking: ARM Ltd Windows GCC C Linker'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED) @"kea-pump.args" -o"kea-pump.elf"
	@echo 'Finished building target: $@'
	@echo ' '

kea-pump.hex: kea-pump.elf
	@echo 'Executing target #85 $@'
	@echo 'Invoking: ARM Ltd Windows GNU Create Flash Image'
	"$(ARMSourceryDirEnv)/arm-none-eabi-objcopy"  -O ihex kea-pump.elf "kea-pump.hex"
	@echo 'Finished building: $@'
	@echo ' '

kea-pump.lst: kea-pump.elf
	@echo 'Executing target #86 $@'
	@echo 'Invoking: ARM Ltd Windows GNU Create Listing'
	"$(ARMSourceryDirEnv)/arm-none-eabi-objdump"  -h -S kea-pump.elf >"kea-pump.lst"
	@echo 'Finished building: $@'
	@echo ' '

kea-pump.siz: kea-pump.elf
	@echo 'Executing target #87 $@'
	@echo 'Invoking: ARM Ltd Windows GNU Print Size'
	"$(ARMSourceryDirEnv)/arm-none-eabi-size"  --format=berkeley kea-pump.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) $(SECONDARY_LIST_QUOTED) $(SECONDARY_FLASH_QUOTED) "./*/*.o" "./*/*/*.o"  $(S_UPPER_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(SECONDARY_SIZE_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(SX_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*.d" "./*/*/*.d"  $(ProjDirPath)/FLASH/kea-pump.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: ../Project_Settings/Linker_Files/ProcessorExpert.ld kea-pump.elf kea-pump.elf kea-pump.elf 

warning-messages: 

