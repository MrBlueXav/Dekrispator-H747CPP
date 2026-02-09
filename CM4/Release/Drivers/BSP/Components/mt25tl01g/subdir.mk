################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components/mt25tl01g/mt25tl01g.c 

C_DEPS += \
./Drivers/BSP/Components/mt25tl01g/mt25tl01g.d 

OBJS += \
./Drivers/BSP/Components/mt25tl01g/mt25tl01g.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/mt25tl01g/mt25tl01g.o: D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components/mt25tl01g/mt25tl01g.c Drivers/BSP/Components/mt25tl01g/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DMETAL_MAX_DEVICE_REGIONS=2 -DRPMSG_BUFFER_SIZE=128 -DSTM32H747xx -DCORE_CM4 -DVIRTIO_SLAVE_ONLY -DNO_ATOMIC_64_SUPPORT -DMETAL_INTERNAL -DUSE_HAL_DRIVER -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../USB_HOST/App -I../USB_HOST/Target -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I"D:/STM32CubeMX/Disco747_xav_CPP/CM4/OPENAMP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/Fonts" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/lcd" -I"D:/STM32CubeMX/Disco747_xav_CPP/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/Synth/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/Binn" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/open-amp/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/libmetal/lib/include" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-mt25tl01g

clean-Drivers-2f-BSP-2f-Components-2f-mt25tl01g:
	-$(RM) ./Drivers/BSP/Components/mt25tl01g/mt25tl01g.cyclo ./Drivers/BSP/Components/mt25tl01g/mt25tl01g.d ./Drivers/BSP/Components/mt25tl01g/mt25tl01g.o ./Drivers/BSP/Components/mt25tl01g/mt25tl01g.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-mt25tl01g

