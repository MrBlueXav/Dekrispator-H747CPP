################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DaisySP_Source/PhysicalModeling/KarplusString.cpp \
../DaisySP_Source/PhysicalModeling/drip.cpp \
../DaisySP_Source/PhysicalModeling/modalvoice.cpp \
../DaisySP_Source/PhysicalModeling/pluck.cpp \
../DaisySP_Source/PhysicalModeling/resonator.cpp \
../DaisySP_Source/PhysicalModeling/stringvoice.cpp 

OBJS += \
./DaisySP_Source/PhysicalModeling/KarplusString.o \
./DaisySP_Source/PhysicalModeling/drip.o \
./DaisySP_Source/PhysicalModeling/modalvoice.o \
./DaisySP_Source/PhysicalModeling/pluck.o \
./DaisySP_Source/PhysicalModeling/resonator.o \
./DaisySP_Source/PhysicalModeling/stringvoice.o 

CPP_DEPS += \
./DaisySP_Source/PhysicalModeling/KarplusString.d \
./DaisySP_Source/PhysicalModeling/drip.d \
./DaisySP_Source/PhysicalModeling/modalvoice.d \
./DaisySP_Source/PhysicalModeling/pluck.d \
./DaisySP_Source/PhysicalModeling/resonator.d \
./DaisySP_Source/PhysicalModeling/stringvoice.d 


# Each subdirectory must supply rules for building sources it contributes
DaisySP_Source/PhysicalModeling/%.o DaisySP_Source/PhysicalModeling/%.su DaisySP_Source/PhysicalModeling/%.cyclo: ../DaisySP_Source/PhysicalModeling/%.cpp DaisySP_Source/PhysicalModeling/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -DMETAL_MAX_DEVICE_REGIONS=2 -DVIRTIO_MASTER_ONLY -DRPMSG_BUFFER_SIZE=128 -DSTM32H747xx -DCORE_CM7 -DNO_ATOMIC_64_SUPPORT -DMETAL_INTERNAL -DUSE_HAL_DRIVER -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/Synth/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/OPENAMP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/open-amp/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/libmetal/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM4/USB_HOST/App" -I"D:/STM32CubeMX/Disco747_xav_CPP/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Binn" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source/Utility" -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DaisySP_Source-2f-PhysicalModeling

clean-DaisySP_Source-2f-PhysicalModeling:
	-$(RM) ./DaisySP_Source/PhysicalModeling/KarplusString.cyclo ./DaisySP_Source/PhysicalModeling/KarplusString.d ./DaisySP_Source/PhysicalModeling/KarplusString.o ./DaisySP_Source/PhysicalModeling/KarplusString.su ./DaisySP_Source/PhysicalModeling/drip.cyclo ./DaisySP_Source/PhysicalModeling/drip.d ./DaisySP_Source/PhysicalModeling/drip.o ./DaisySP_Source/PhysicalModeling/drip.su ./DaisySP_Source/PhysicalModeling/modalvoice.cyclo ./DaisySP_Source/PhysicalModeling/modalvoice.d ./DaisySP_Source/PhysicalModeling/modalvoice.o ./DaisySP_Source/PhysicalModeling/modalvoice.su ./DaisySP_Source/PhysicalModeling/pluck.cyclo ./DaisySP_Source/PhysicalModeling/pluck.d ./DaisySP_Source/PhysicalModeling/pluck.o ./DaisySP_Source/PhysicalModeling/pluck.su ./DaisySP_Source/PhysicalModeling/resonator.cyclo ./DaisySP_Source/PhysicalModeling/resonator.d ./DaisySP_Source/PhysicalModeling/resonator.o ./DaisySP_Source/PhysicalModeling/resonator.su ./DaisySP_Source/PhysicalModeling/stringvoice.cyclo ./DaisySP_Source/PhysicalModeling/stringvoice.d ./DaisySP_Source/PhysicalModeling/stringvoice.o ./DaisySP_Source/PhysicalModeling/stringvoice.su

.PHONY: clean-DaisySP_Source-2f-PhysicalModeling

