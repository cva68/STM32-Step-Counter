################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc.c \
../Core/Src/app.c \
../Core/Src/buttons.c \
../Core/Src/dma.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/joystick.c \
../Core/Src/main.c \
../Core/Src/pwm.c \
../Core/Src/rgb.c \
../Core/Src/ssd1306.c \
../Core/Src/ssd1306_fonts.c \
../Core/Src/state_task_count.c \
../Core/Src/state_task_distance.c \
../Core/Src/state_task_goal.c \
../Core/Src/stm32c0xx_hal_msp.c \
../Core/Src/stm32c0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32c0xx.c \
../Core/Src/task_buttons.c \
../Core/Src/task_display.c \
../Core/Src/task_fsm.c \
../Core/Src/task_joystick.c \
../Core/Src/task_uart.c \
../Core/Src/tim.c \
../Core/Src/uart_debugger.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/adc.o \
./Core/Src/app.o \
./Core/Src/buttons.o \
./Core/Src/dma.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/joystick.o \
./Core/Src/main.o \
./Core/Src/pwm.o \
./Core/Src/rgb.o \
./Core/Src/ssd1306.o \
./Core/Src/ssd1306_fonts.o \
./Core/Src/state_task_count.o \
./Core/Src/state_task_distance.o \
./Core/Src/state_task_goal.o \
./Core/Src/stm32c0xx_hal_msp.o \
./Core/Src/stm32c0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32c0xx.o \
./Core/Src/task_buttons.o \
./Core/Src/task_display.o \
./Core/Src/task_fsm.o \
./Core/Src/task_joystick.o \
./Core/Src/task_uart.o \
./Core/Src/tim.o \
./Core/Src/uart_debugger.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/adc.d \
./Core/Src/app.d \
./Core/Src/buttons.d \
./Core/Src/dma.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/joystick.d \
./Core/Src/main.d \
./Core/Src/pwm.d \
./Core/Src/rgb.d \
./Core/Src/ssd1306.d \
./Core/Src/ssd1306_fonts.d \
./Core/Src/state_task_count.d \
./Core/Src/state_task_distance.d \
./Core/Src/state_task_goal.d \
./Core/Src/stm32c0xx_hal_msp.d \
./Core/Src/stm32c0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32c0xx.d \
./Core/Src/task_buttons.d \
./Core/Src/task_display.d \
./Core/Src/task_fsm.d \
./Core/Src/task_joystick.d \
./Core/Src/task_uart.d \
./Core/Src/tim.d \
./Core/Src/uart_debugger.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32C071xx -c -I../Core/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32C0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/app.cyclo ./Core/Src/app.d ./Core/Src/app.o ./Core/Src/app.su ./Core/Src/buttons.cyclo ./Core/Src/buttons.d ./Core/Src/buttons.o ./Core/Src/buttons.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/joystick.cyclo ./Core/Src/joystick.d ./Core/Src/joystick.o ./Core/Src/joystick.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/pwm.cyclo ./Core/Src/pwm.d ./Core/Src/pwm.o ./Core/Src/pwm.su ./Core/Src/rgb.cyclo ./Core/Src/rgb.d ./Core/Src/rgb.o ./Core/Src/rgb.su ./Core/Src/ssd1306.cyclo ./Core/Src/ssd1306.d ./Core/Src/ssd1306.o ./Core/Src/ssd1306.su ./Core/Src/ssd1306_fonts.cyclo ./Core/Src/ssd1306_fonts.d ./Core/Src/ssd1306_fonts.o ./Core/Src/ssd1306_fonts.su ./Core/Src/state_task_count.cyclo ./Core/Src/state_task_count.d ./Core/Src/state_task_count.o ./Core/Src/state_task_count.su ./Core/Src/state_task_distance.cyclo ./Core/Src/state_task_distance.d ./Core/Src/state_task_distance.o ./Core/Src/state_task_distance.su ./Core/Src/state_task_goal.cyclo ./Core/Src/state_task_goal.d ./Core/Src/state_task_goal.o ./Core/Src/state_task_goal.su ./Core/Src/stm32c0xx_hal_msp.cyclo ./Core/Src/stm32c0xx_hal_msp.d ./Core/Src/stm32c0xx_hal_msp.o ./Core/Src/stm32c0xx_hal_msp.su ./Core/Src/stm32c0xx_it.cyclo ./Core/Src/stm32c0xx_it.d ./Core/Src/stm32c0xx_it.o ./Core/Src/stm32c0xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32c0xx.cyclo ./Core/Src/system_stm32c0xx.d ./Core/Src/system_stm32c0xx.o ./Core/Src/system_stm32c0xx.su ./Core/Src/task_buttons.cyclo ./Core/Src/task_buttons.d ./Core/Src/task_buttons.o ./Core/Src/task_buttons.su ./Core/Src/task_display.cyclo ./Core/Src/task_display.d ./Core/Src/task_display.o ./Core/Src/task_display.su ./Core/Src/task_fsm.cyclo ./Core/Src/task_fsm.d ./Core/Src/task_fsm.o ./Core/Src/task_fsm.su ./Core/Src/task_joystick.cyclo ./Core/Src/task_joystick.d ./Core/Src/task_joystick.o ./Core/Src/task_joystick.su ./Core/Src/task_uart.cyclo ./Core/Src/task_uart.d ./Core/Src/task_uart.o ./Core/Src/task_uart.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/uart_debugger.cyclo ./Core/Src/uart_debugger.d ./Core/Src/uart_debugger.o ./Core/Src/uart_debugger.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

