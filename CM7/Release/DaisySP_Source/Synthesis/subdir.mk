################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DaisySP_Source/Synthesis/blosc.cpp \
../DaisySP_Source/Synthesis/fm2.cpp \
../DaisySP_Source/Synthesis/formantosc.cpp \
../DaisySP_Source/Synthesis/oscillator.cpp \
../DaisySP_Source/Synthesis/oscillatorbank.cpp \
../DaisySP_Source/Synthesis/variablesawosc.cpp \
../DaisySP_Source/Synthesis/variableshapeosc.cpp \
../DaisySP_Source/Synthesis/vosim.cpp \
../DaisySP_Source/Synthesis/zoscillator.cpp 

OBJS += \
./DaisySP_Source/Synthesis/blosc.o \
./DaisySP_Source/Synthesis/fm2.o \
./DaisySP_Source/Synthesis/formantosc.o \
./DaisySP_Source/Synthesis/oscillator.o \
./DaisySP_Source/Synthesis/oscillatorbank.o \
./DaisySP_Source/Synthesis/variablesawosc.o \
./DaisySP_Source/Synthesis/variableshapeosc.o \
./DaisySP_Source/Synthesis/vosim.o \
./DaisySP_Source/Synthesis/zoscillator.o 

CPP_DEPS += \
./DaisySP_Source/Synthesis/blosc.d \
./DaisySP_Source/Synthesis/fm2.d \
./DaisySP_Source/Synthesis/formantosc.d \
./DaisySP_Source/Synthesis/oscillator.d \
./DaisySP_Source/Synthesis/oscillatorbank.d \
./DaisySP_Source/Synthesis/variablesawosc.d \
./DaisySP_Source/Synthesis/variableshapeosc.d \
./DaisySP_Source/Synthesis/vosim.d \
./DaisySP_Source/Synthesis/zoscillator.d 


# Each subdirectory must supply rules for building sources it contributes
DaisySP_Source/Synthesis/%.o DaisySP_Source/Synthesis/%.su DaisySP_Source/Synthesis/%.cyclo: ../DaisySP_Source/Synthesis/%.cpp DaisySP_Source/Synthesis/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -DMETAL_MAX_DEVICE_REGIONS=2 -DVIRTIO_MASTER_ONLY -DRPMSG_BUFFER_SIZE=128 -DSTM32H747xx -DCORE_CM7 -DNO_ATOMIC_64_SUPPORT -DMETAL_INTERNAL -DUSE_HAL_DRIVER -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/Synth/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/OPENAMP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/open-amp/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/libmetal/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM4/USB_HOST/App" -I"D:/STM32CubeMX/Disco747_xav_CPP/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Binn" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source/Utility" -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DaisySP_Source-2f-Synthesis

clean-DaisySP_Source-2f-Synthesis:
	-$(RM) ./DaisySP_Source/Synthesis/blosc.cyclo ./DaisySP_Source/Synthesis/blosc.d ./DaisySP_Source/Synthesis/blosc.o ./DaisySP_Source/Synthesis/blosc.su ./DaisySP_Source/Synthesis/fm2.cyclo ./DaisySP_Source/Synthesis/fm2.d ./DaisySP_Source/Synthesis/fm2.o ./DaisySP_Source/Synthesis/fm2.su ./DaisySP_Source/Synthesis/formantosc.cyclo ./DaisySP_Source/Synthesis/formantosc.d ./DaisySP_Source/Synthesis/formantosc.o ./DaisySP_Source/Synthesis/formantosc.su ./DaisySP_Source/Synthesis/oscillator.cyclo ./DaisySP_Source/Synthesis/oscillator.d ./DaisySP_Source/Synthesis/oscillator.o ./DaisySP_Source/Synthesis/oscillator.su ./DaisySP_Source/Synthesis/oscillatorbank.cyclo ./DaisySP_Source/Synthesis/oscillatorbank.d ./DaisySP_Source/Synthesis/oscillatorbank.o ./DaisySP_Source/Synthesis/oscillatorbank.su ./DaisySP_Source/Synthesis/variablesawosc.cyclo ./DaisySP_Source/Synthesis/variablesawosc.d ./DaisySP_Source/Synthesis/variablesawosc.o ./DaisySP_Source/Synthesis/variablesawosc.su ./DaisySP_Source/Synthesis/variableshapeosc.cyclo ./DaisySP_Source/Synthesis/variableshapeosc.d ./DaisySP_Source/Synthesis/variableshapeosc.o ./DaisySP_Source/Synthesis/variableshapeosc.su ./DaisySP_Source/Synthesis/vosim.cyclo ./DaisySP_Source/Synthesis/vosim.d ./DaisySP_Source/Synthesis/vosim.o ./DaisySP_Source/Synthesis/vosim.su ./DaisySP_Source/Synthesis/zoscillator.cyclo ./DaisySP_Source/Synthesis/zoscillator.d ./DaisySP_Source/Synthesis/zoscillator.o ./DaisySP_Source/Synthesis/zoscillator.su

.PHONY: clean-DaisySP_Source-2f-Synthesis

