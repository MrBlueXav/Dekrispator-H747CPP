################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DaisySP_Source/Utility/dcblock.cpp \
../DaisySP_Source/Utility/jitter.cpp \
../DaisySP_Source/Utility/metro.cpp \
../DaisySP_Source/Utility/port.cpp 

OBJS += \
./DaisySP_Source/Utility/dcblock.o \
./DaisySP_Source/Utility/jitter.o \
./DaisySP_Source/Utility/metro.o \
./DaisySP_Source/Utility/port.o 

CPP_DEPS += \
./DaisySP_Source/Utility/dcblock.d \
./DaisySP_Source/Utility/jitter.d \
./DaisySP_Source/Utility/metro.d \
./DaisySP_Source/Utility/port.d 


# Each subdirectory must supply rules for building sources it contributes
DaisySP_Source/Utility/%.o DaisySP_Source/Utility/%.su DaisySP_Source/Utility/%.cyclo: ../DaisySP_Source/Utility/%.cpp DaisySP_Source/Utility/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -DMETAL_MAX_DEVICE_REGIONS=2 -DVIRTIO_MASTER_ONLY -DRPMSG_BUFFER_SIZE=128 -DSTM32H747xx -DCORE_CM7 -DNO_ATOMIC_64_SUPPORT -DMETAL_INTERNAL -DUSE_HAL_DRIVER -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/Synth/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/OPENAMP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/open-amp/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/libmetal/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM4/USB_HOST/App" -I"D:/STM32CubeMX/Disco747_xav_CPP/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Binn" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source/Utility" -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DaisySP_Source-2f-Utility

clean-DaisySP_Source-2f-Utility:
	-$(RM) ./DaisySP_Source/Utility/dcblock.cyclo ./DaisySP_Source/Utility/dcblock.d ./DaisySP_Source/Utility/dcblock.o ./DaisySP_Source/Utility/dcblock.su ./DaisySP_Source/Utility/jitter.cyclo ./DaisySP_Source/Utility/jitter.d ./DaisySP_Source/Utility/jitter.o ./DaisySP_Source/Utility/jitter.su ./DaisySP_Source/Utility/metro.cyclo ./DaisySP_Source/Utility/metro.d ./DaisySP_Source/Utility/metro.o ./DaisySP_Source/Utility/metro.su ./DaisySP_Source/Utility/port.cyclo ./DaisySP_Source/Utility/port.d ./DaisySP_Source/Utility/port.o ./DaisySP_Source/Utility/port.su

.PHONY: clean-DaisySP_Source-2f-Utility

