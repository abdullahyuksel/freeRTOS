################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/appLayer/RtosFunc/functions.c 

OBJS += \
./Core/Src/appLayer/RtosFunc/functions.o 

C_DEPS += \
./Core/Src/appLayer/RtosFunc/functions.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/appLayer/RtosFunc/%.o Core/Src/appLayer/RtosFunc/%.su: ../Core/Src/appLayer/RtosFunc/%.c Core/Src/appLayer/RtosFunc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/stmEgitim/rtos/workspace_1.9.0_freeRTOS/freeRTOS_HAL_ledControl_Queues/freeRTOS_Config" -I"D:/stmEgitim/rtos/workspace_1.9.0_freeRTOS/freeRTOS_HAL_ledControl_Queues/MiddleWares/Third_Party/FreeRTOS/org/Source/include" -I"D:/stmEgitim/rtos/workspace_1.9.0_freeRTOS/freeRTOS_HAL_ledControl_Queues/MiddleWares/Third_Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"D:/stmEgitim/rtos/workspace_1.9.0_freeRTOS/freeRTOS_HAL_ledControl_Queues/Core/Src/appLayer/led" -I"D:/stmEgitim/rtos/workspace_1.9.0_freeRTOS/freeRTOS_HAL_ledControl_Queues/Core/Src/appLayer/RtosFunc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-appLayer-2f-RtosFunc

clean-Core-2f-Src-2f-appLayer-2f-RtosFunc:
	-$(RM) ./Core/Src/appLayer/RtosFunc/functions.d ./Core/Src/appLayer/RtosFunc/functions.o ./Core/Src/appLayer/RtosFunc/functions.su

.PHONY: clean-Core-2f-Src-2f-appLayer-2f-RtosFunc

