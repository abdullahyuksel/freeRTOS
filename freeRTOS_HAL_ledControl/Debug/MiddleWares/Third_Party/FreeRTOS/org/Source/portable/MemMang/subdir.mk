################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MiddleWares/Third_Party/FreeRTOS/org/Source/portable/MemMang/heap_4.c 

OBJS += \
./MiddleWares/Third_Party/FreeRTOS/org/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./MiddleWares/Third_Party/FreeRTOS/org/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
MiddleWares/Third_Party/FreeRTOS/org/Source/portable/MemMang/%.o MiddleWares/Third_Party/FreeRTOS/org/Source/portable/MemMang/%.su: ../MiddleWares/Third_Party/FreeRTOS/org/Source/portable/MemMang/%.c MiddleWares/Third_Party/FreeRTOS/org/Source/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/stmEgitim/rtos/workspace_1.9.0_freeRTOS/freeRTOS_HAL_ledControl/MiddleWares/Third_Party/FreeRTOS/org/Source/include" -I"D:/stmEgitim/rtos/workspace_1.9.0_freeRTOS/freeRTOS_HAL_ledControl/MiddleWares/Third_Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"D:/stmEgitim/rtos/workspace_1.9.0_freeRTOS/freeRTOS_HAL_ledControl/freeRTOS_Config" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MiddleWares-2f-Third_Party-2f-FreeRTOS-2f-org-2f-Source-2f-portable-2f-MemMang

clean-MiddleWares-2f-Third_Party-2f-FreeRTOS-2f-org-2f-Source-2f-portable-2f-MemMang:
	-$(RM) ./MiddleWares/Third_Party/FreeRTOS/org/Source/portable/MemMang/heap_4.d ./MiddleWares/Third_Party/FreeRTOS/org/Source/portable/MemMang/heap_4.o ./MiddleWares/Third_Party/FreeRTOS/org/Source/portable/MemMang/heap_4.su

.PHONY: clean-MiddleWares-2f-Third_Party-2f-FreeRTOS-2f-org-2f-Source-2f-portable-2f-MemMang

