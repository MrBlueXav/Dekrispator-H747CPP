################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DaisySP_Source/Control/adenv.cpp \
../DaisySP_Source/Control/adsr.cpp \
../DaisySP_Source/Control/line.cpp \
../DaisySP_Source/Control/phasor.cpp 

OBJS += \
./DaisySP_Source/Control/adenv.o \
./DaisySP_Source/Control/adsr.o \
./DaisySP_Source/Control/line.o \
./DaisySP_Source/Control/phasor.o 

CPP_DEPS += \
./DaisySP_Source/Control/adenv.d \
./DaisySP_Source/Control/adsr.d \
./DaisySP_Source/Control/line.d \
./DaisySP_Source/Control/phasor.d 


# Each subdirectory must supply rules for building sources it contributes
DaisySP_Source/Control/%.o DaisySP_Source/Control/%.su DaisySP_Source/Control/%.cyclo: ../DaisySP_Source/Control/%.cpp DaisySP_Source/Control/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -DMETAL_MAX_DEVICE_REGIONS=2 -DVIRTIO_MASTER_ONLY -DRPMSG_BUFFER_SIZE=128 -DSTM32H747xx -DCORE_CM7 -DNO_ATOMIC_64_SUPPORT -DMETAL_INTERNAL -DUSE_HAL_DRIVER -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/Synth/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/OPENAMP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/open-amp/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/libmetal/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM4/USB_HOST/App" -I"D:/STM32CubeMX/Disco747_xav_CPP/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Binn" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source/Utility" -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DaisySP_Source-2f-Control

clean-DaisySP_Source-2f-Control:
	-$(RM) ./DaisySP_Source/Control/adenv.cyclo ./DaisySP_Source/Control/adenv.d ./DaisySP_Source/Control/adenv.o ./DaisySP_Source/Control/adenv.su ./DaisySP_Source/Control/adsr.cyclo ./DaisySP_Source/Control/adsr.d ./DaisySP_Source/Control/adsr.o ./DaisySP_Source/Control/adsr.su ./DaisySP_Source/Control/line.cyclo ./DaisySP_Source/Control/line.d ./DaisySP_Source/Control/line.o ./DaisySP_Source/Control/line.su ./DaisySP_Source/Control/phasor.cyclo ./DaisySP_Source/Control/phasor.d ./DaisySP_Source/Control/phasor.o ./DaisySP_Source/Control/phasor.su

.PHONY: clean-DaisySP_Source-2f-Control

