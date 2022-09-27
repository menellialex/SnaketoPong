################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/QuadKnob.c \
../Core/Src/display_DOGS102.c \
../Core/Src/main.c \
../Core/Src/show_snake.c \
../Core/Src/smc_queue.c \
../Core/Src/snake_gameplay.c \
../Core/Src/snake_main.c \
../Core/Src/snake_repair.c \
../Core/Src/stm32g0xx_hal_msp.c \
../Core/Src/stm32g0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g0xx.c 

OBJS += \
./Core/Src/QuadKnob.o \
./Core/Src/display_DOGS102.o \
./Core/Src/main.o \
./Core/Src/show_snake.o \
./Core/Src/smc_queue.o \
./Core/Src/snake_gameplay.o \
./Core/Src/snake_main.o \
./Core/Src/snake_repair.o \
./Core/Src/stm32g0xx_hal_msp.o \
./Core/Src/stm32g0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g0xx.o 

C_DEPS += \
./Core/Src/QuadKnob.d \
./Core/Src/display_DOGS102.d \
./Core/Src/main.d \
./Core/Src/show_snake.d \
./Core/Src/smc_queue.d \
./Core/Src/snake_gameplay.d \
./Core/Src/snake_main.d \
./Core/Src/snake_repair.d \
./Core/Src/stm32g0xx_hal_msp.d \
./Core/Src/stm32g0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/QuadKnob.d ./Core/Src/QuadKnob.o ./Core/Src/QuadKnob.su ./Core/Src/display_DOGS102.d ./Core/Src/display_DOGS102.o ./Core/Src/display_DOGS102.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/show_snake.d ./Core/Src/show_snake.o ./Core/Src/show_snake.su ./Core/Src/smc_queue.d ./Core/Src/smc_queue.o ./Core/Src/smc_queue.su ./Core/Src/snake_gameplay.d ./Core/Src/snake_gameplay.o ./Core/Src/snake_gameplay.su ./Core/Src/snake_main.d ./Core/Src/snake_main.o ./Core/Src/snake_main.su ./Core/Src/snake_repair.d ./Core/Src/snake_repair.o ./Core/Src/snake_repair.su ./Core/Src/stm32g0xx_hal_msp.d ./Core/Src/stm32g0xx_hal_msp.o ./Core/Src/stm32g0xx_hal_msp.su ./Core/Src/stm32g0xx_it.d ./Core/Src/stm32g0xx_it.o ./Core/Src/stm32g0xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32g0xx.d ./Core/Src/system_stm32g0xx.o ./Core/Src/system_stm32g0xx.su

.PHONY: clean-Core-2f-Src

