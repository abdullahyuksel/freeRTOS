################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MiddleWares/Third_Party/FreeRTOS/org/Source/portable/MemMang/subdir.mk
-include MiddleWares/Third_Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F/subdir.mk
-include MiddleWares/Third_Party/FreeRTOS/org/Source/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := freeRTOS_HAL_CountingSemaphore
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
freeRTOS_HAL_CountingSemaphore.elf \

MAP_FILES += \
freeRTOS_HAL_CountingSemaphore.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
freeRTOS_HAL_CountingSemaphore.list \


# All Target
all: main-build

# Main-build Target
main-build: freeRTOS_HAL_CountingSemaphore.elf secondary-outputs

# Tool invocations
freeRTOS_HAL_CountingSemaphore.elf freeRTOS_HAL_CountingSemaphore.map: $(OBJS) $(USER_OBJS) D:\stmEgitim\rtos\workspace_1.9.0_freeRTOS\freeRTOS_HAL_CountingSemaphore\STM32F407VGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "freeRTOS_HAL_CountingSemaphore.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\stmEgitim\rtos\workspace_1.9.0_freeRTOS\freeRTOS_HAL_CountingSemaphore\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="freeRTOS_HAL_CountingSemaphore.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

freeRTOS_HAL_CountingSemaphore.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "freeRTOS_HAL_CountingSemaphore.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout freeRTOS_HAL_CountingSemaphore.elf freeRTOS_HAL_CountingSemaphore.list freeRTOS_HAL_CountingSemaphore.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
