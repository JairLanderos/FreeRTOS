################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Fam.\ Landeros\ Franco/Desktop/Embedded\ Systems/FreeRTOS\ course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/croutine.c \
C:/Users/Fam.\ Landeros\ Franco/Desktop/Embedded\ Systems/FreeRTOS\ course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/event_groups.c \
C:/Users/Fam.\ Landeros\ Franco/Desktop/Embedded\ Systems/FreeRTOS\ course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/list.c \
C:/Users/Fam.\ Landeros\ Franco/Desktop/Embedded\ Systems/FreeRTOS\ course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/queue.c \
C:/Users/Fam.\ Landeros\ Franco/Desktop/Embedded\ Systems/FreeRTOS\ course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/stream_buffer.c \
C:/Users/Fam.\ Landeros\ Franco/Desktop/Embedded\ Systems/FreeRTOS\ course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/tasks.c \
C:/Users/Fam.\ Landeros\ Franco/Desktop/Embedded\ Systems/FreeRTOS\ course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/timers.c 

OBJS += \
./common/ThirdParty/FreeRTOS/croutine.o \
./common/ThirdParty/FreeRTOS/event_groups.o \
./common/ThirdParty/FreeRTOS/list.o \
./common/ThirdParty/FreeRTOS/queue.o \
./common/ThirdParty/FreeRTOS/stream_buffer.o \
./common/ThirdParty/FreeRTOS/tasks.o \
./common/ThirdParty/FreeRTOS/timers.o 

C_DEPS += \
./common/ThirdParty/FreeRTOS/croutine.d \
./common/ThirdParty/FreeRTOS/event_groups.d \
./common/ThirdParty/FreeRTOS/list.d \
./common/ThirdParty/FreeRTOS/queue.d \
./common/ThirdParty/FreeRTOS/stream_buffer.d \
./common/ThirdParty/FreeRTOS/tasks.d \
./common/ThirdParty/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
common/ThirdParty/FreeRTOS/croutine.o: C:/Users/Fam.\ Landeros\ Franco/Desktop/Embedded\ Systems/FreeRTOS\ course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/croutine.c common/ThirdParty/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/include" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/Config" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/OS" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/ThirdParty/FreeRTOS/event_groups.o: C:/Users/Fam.\ Landeros\ Franco/Desktop/Embedded\ Systems/FreeRTOS\ course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/event_groups.c common/ThirdParty/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/include" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/Config" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/OS" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/ThirdParty/FreeRTOS/list.o: C:/Users/Fam.\ Landeros\ Franco/Desktop/Embedded\ Systems/FreeRTOS\ course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/list.c common/ThirdParty/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/include" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/Config" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/OS" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/ThirdParty/FreeRTOS/queue.o: C:/Users/Fam.\ Landeros\ Franco/Desktop/Embedded\ Systems/FreeRTOS\ course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/queue.c common/ThirdParty/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/include" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/Config" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/OS" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/ThirdParty/FreeRTOS/stream_buffer.o: C:/Users/Fam.\ Landeros\ Franco/Desktop/Embedded\ Systems/FreeRTOS\ course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/stream_buffer.c common/ThirdParty/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/include" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/Config" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/OS" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/ThirdParty/FreeRTOS/tasks.o: C:/Users/Fam.\ Landeros\ Franco/Desktop/Embedded\ Systems/FreeRTOS\ course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/tasks.c common/ThirdParty/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/include" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/Config" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/OS" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/ThirdParty/FreeRTOS/timers.o: C:/Users/Fam.\ Landeros\ Franco/Desktop/Embedded\ Systems/FreeRTOS\ course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/timers.c common/ThirdParty/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/include" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/Config" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/OS" -I"C:/Users/Fam. Landeros Franco/Desktop/Embedded Systems/FreeRTOS course/workspace/RTOS_workspace/common/ThirdParty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-common-2f-ThirdParty-2f-FreeRTOS

clean-common-2f-ThirdParty-2f-FreeRTOS:
	-$(RM) ./common/ThirdParty/FreeRTOS/croutine.d ./common/ThirdParty/FreeRTOS/croutine.o ./common/ThirdParty/FreeRTOS/event_groups.d ./common/ThirdParty/FreeRTOS/event_groups.o ./common/ThirdParty/FreeRTOS/list.d ./common/ThirdParty/FreeRTOS/list.o ./common/ThirdParty/FreeRTOS/queue.d ./common/ThirdParty/FreeRTOS/queue.o ./common/ThirdParty/FreeRTOS/stream_buffer.d ./common/ThirdParty/FreeRTOS/stream_buffer.o ./common/ThirdParty/FreeRTOS/tasks.d ./common/ThirdParty/FreeRTOS/tasks.o ./common/ThirdParty/FreeRTOS/timers.d ./common/ThirdParty/FreeRTOS/timers.o

.PHONY: clean-common-2f-ThirdParty-2f-FreeRTOS
