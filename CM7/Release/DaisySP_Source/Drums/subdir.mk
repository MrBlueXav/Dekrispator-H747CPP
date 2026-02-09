################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DaisySP_Source/Drums/analogbassdrum.cpp \
../DaisySP_Source/Drums/analogsnaredrum.cpp \
../DaisySP_Source/Drums/hihat.cpp \
../DaisySP_Source/Drums/synthbassdrum.cpp \
../DaisySP_Source/Drums/synthsnaredrum.cpp 

OBJS += \
./DaisySP_Source/Drums/analogbassdrum.o \
./DaisySP_Source/Drums/analogsnaredrum.o \
./DaisySP_Source/Drums/hihat.o \
./DaisySP_Source/Drums/synthbassdrum.o \
./DaisySP_Source/Drums/synthsnaredrum.o 

CPP_DEPS += \
./DaisySP_Source/Drums/analogbassdrum.d \
./DaisySP_Source/Drums/analogsnaredrum.d \
./DaisySP_Source/Drums/hihat.d \
./DaisySP_Source/Drums/synthbassdrum.d \
./DaisySP_Source/Drums/synthsnaredrum.d 


# Each subdirectory must supply rules for building sources it contributes
DaisySP_Source/Drums/%.o DaisySP_Source/Drums/%.su DaisySP_Source/Drums/%.cyclo: ../DaisySP_Source/Drums/%.cpp DaisySP_Source/Drums/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -DMETAL_MAX_DEVICE_REGIONS=2 -DVIRTIO_MASTER_ONLY -DRPMSG_BUFFER_SIZE=128 -DSTM32H747xx -DCORE_CM7 -DNO_ATOMIC_64_SUPPORT -DMETAL_INTERNAL -DUSE_HAL_DRIVER -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/Synth/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/OPENAMP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/open-amp/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/libmetal/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM4/USB_HOST/App" -I"D:/STM32CubeMX/Disco747_xav_CPP/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Binn" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source/Utility" -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DaisySP_Source-2f-Drums

clean-DaisySP_Source-2f-Drums:
	-$(RM) ./DaisySP_Source/Drums/analogbassdrum.cyclo ./DaisySP_Source/Drums/analogbassdrum.d ./DaisySP_Source/Drums/analogbassdrum.o ./DaisySP_Source/Drums/analogbassdrum.su ./DaisySP_Source/Drums/analogsnaredrum.cyclo ./DaisySP_Source/Drums/analogsnaredrum.d ./DaisySP_Source/Drums/analogsnaredrum.o ./DaisySP_Source/Drums/analogsnaredrum.su ./DaisySP_Source/Drums/hihat.cyclo ./DaisySP_Source/Drums/hihat.d ./DaisySP_Source/Drums/hihat.o ./DaisySP_Source/Drums/hihat.su ./DaisySP_Source/Drums/synthbassdrum.cyclo ./DaisySP_Source/Drums/synthbassdrum.d ./DaisySP_Source/Drums/synthbassdrum.o ./DaisySP_Source/Drums/synthbassdrum.su ./DaisySP_Source/Drums/synthsnaredrum.cyclo ./DaisySP_Source/Drums/synthsnaredrum.d ./DaisySP_Source/Drums/synthsnaredrum.o ./DaisySP_Source/Drums/synthsnaredrum.su

.PHONY: clean-DaisySP_Source-2f-Drums

