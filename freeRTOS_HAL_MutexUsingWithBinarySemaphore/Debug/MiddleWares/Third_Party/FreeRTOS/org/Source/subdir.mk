################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MiddleWares/Third_Party/FreeRTOS/org/Source/croutine.c \
../MiddleWares/Third_Party/FreeRTOS/org/Source/event_groups.c \
../MiddleWares/Third_Party/FreeRTOS/org/Source/list.c \
../MiddleWares/Third_Party/FreeRTOS/org/Source/queue.c \
../MiddleWares/Third_Party/FreeRTOS/org/Source/stream_buffer.c \
../MiddleWares/Third_Party/FreeRTOS/org/Source/tasks.c \
../MiddleWares/Third_Party/FreeRTOS/org/Source/timers.c 

OBJS += \
./MiddleWares/Third_Party/FreeRTOS/org/Source/croutine.o \
./MiddleWares/Third_Party/FreeRTOS/org/Source/event_groups.o \
./MiddleWares/Third_Party/FreeRTOS/org/Source/list.o \
./MiddleWares/Third_Party/FreeRTOS/org/Source/queue.o \
./MiddleWares/Third_Party/FreeRTOS/org/Source/stream_buffer.o \
./MiddleWares/Third_Party/FreeRTOS/org/Source/tasks.o \
./MiddleWares/Third_Party/FreeRTOS/org/Source/timers.o 

C_DEPS += \
./MiddleWares/Third_Party/FreeRTOS/org/Source/croutine.d \
./MiddleWares/Third_Party/FreeRTOS/org/Source/event_groups.d \
./MiddleWares/Third_Party/FreeRTOS/org/Source/list.d \
./MiddleWares/Third_Party/FreeRTOS/org/Source/queue.d \
./MiddleWares/Third_Party/FreeRTOS/org/Source/stream_buffer.d \
./MiddleWares/Third_Party/FreeRTOS/org/Source/tasks.d \
./MiddleWares/Third_Party/FreeRTOS/org/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
MiddleWares/Third_Party/FreeRTOS/org/Source/%.o MiddleWares/Third_Party/FreeRTOS/org/Source/%.su: ../MiddleWares/Third_Party/FreeRTOS/org/Source/%.c MiddleWares/Third_Party/FreeRTOS/org/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/stmEgitim/rtos/workspace_1.9.0_freeRTOS/freeRTOS_HAL_MutexUsingWithBinarySemaphore/freeRTOS_Config" -I"D:/stmEgitim/rtos/workspace_1.9.0_freeRTOS/freeRTOS_HAL_MutexUsingWithBinarySemaphore/MiddleWares/Third_Party/FreeRTOS/org/Source/include" -I"D:/stmEgitim/rtos/workspace_1.9.0_freeRTOS/freeRTOS_HAL_MutexUsingWithBinarySemaphore/MiddleWares/Third_Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MiddleWares-2f-Third_Party-2f-FreeRTOS-2f-org-2f-Source

clean-MiddleWares-2f-Third_Party-2f-FreeRTOS-2f-org-2f-Source:
	-$(RM) ./MiddleWares/Third_Party/FreeRTOS/org/Source/croutine.d ./MiddleWares/Third_Party/FreeRTOS/org/Source/croutine.o ./MiddleWares/Third_Party/FreeRTOS/org/Source/croutine.su ./MiddleWares/Third_Party/FreeRTOS/org/Source/event_groups.d ./MiddleWares/Third_Party/FreeRTOS/org/Source/event_groups.o ./MiddleWares/Third_Party/FreeRTOS/org/Source/event_groups.su ./MiddleWares/Third_Party/FreeRTOS/org/Source/list.d ./MiddleWares/Third_Party/FreeRTOS/org/Source/list.o ./MiddleWares/Third_Party/FreeRTOS/org/Source/list.su ./MiddleWares/Third_Party/FreeRTOS/org/Source/queue.d ./MiddleWares/Third_Party/FreeRTOS/org/Source/queue.o ./MiddleWares/Third_Party/FreeRTOS/org/Source/queue.su ./MiddleWares/Third_Party/FreeRTOS/org/Source/stream_buffer.d ./MiddleWares/Third_Party/FreeRTOS/org/Source/stream_buffer.o ./MiddleWares/Third_Party/FreeRTOS/org/Source/stream_buffer.su ./MiddleWares/Third_Party/FreeRTOS/org/Source/tasks.d ./MiddleWares/Third_Party/FreeRTOS/org/Source/tasks.o ./MiddleWares/Third_Party/FreeRTOS/org/Source/tasks.su ./MiddleWares/Third_Party/FreeRTOS/org/Source/timers.d ./MiddleWares/Third_Party/FreeRTOS/org/Source/timers.o ./MiddleWares/Third_Party/FreeRTOS/org/Source/timers.su

.PHONY: clean-MiddleWares-2f-Third_Party-2f-FreeRTOS-2f-org-2f-Source

