################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include board/subdir.mk
-include CMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: MKL25Z128xxx4_Acel+tap_detection.axf

# Tool invocations
MKL25Z128xxx4_Acel+tap_detection.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="MKL25Z128xxx4_Acel+tap_detection.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0plus -mthumb -T MKL25Z128xxx4_Acel+tap_detection_Debug.ld -o "MKL25Z128xxx4_Acel+tap_detection.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) MKL25Z128xxx4_Acel+tap_detection.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "MKL25Z128xxx4_Acel+tap_detection.axf"; # arm-none-eabi-objcopy -v -O binary "MKL25Z128xxx4_Acel+tap_detection.axf" "MKL25Z128xxx4_Acel+tap_detection.bin" ; # checksum -p MKL25Z128xxx4 -d "MKL25Z128xxx4_Acel+tap_detection.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
