################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DaisySP_Source/Filters/allpass.cpp \
../DaisySP_Source/Filters/atone.cpp \
../DaisySP_Source/Filters/biquad.cpp \
../DaisySP_Source/Filters/comb.cpp \
../DaisySP_Source/Filters/mode.cpp \
../DaisySP_Source/Filters/moogladder.cpp \
../DaisySP_Source/Filters/nlfilt.cpp \
../DaisySP_Source/Filters/svf.cpp \
../DaisySP_Source/Filters/tone.cpp 

OBJS += \
./DaisySP_Source/Filters/allpass.o \
./DaisySP_Source/Filters/atone.o \
./DaisySP_Source/Filters/biquad.o \
./DaisySP_Source/Filters/comb.o \
./DaisySP_Source/Filters/mode.o \
./DaisySP_Source/Filters/moogladder.o \
./DaisySP_Source/Filters/nlfilt.o \
./DaisySP_Source/Filters/svf.o \
./DaisySP_Source/Filters/tone.o 

CPP_DEPS += \
./DaisySP_Source/Filters/allpass.d \
./DaisySP_Source/Filters/atone.d \
./DaisySP_Source/Filters/biquad.d \
./DaisySP_Source/Filters/comb.d \
./DaisySP_Source/Filters/mode.d \
./DaisySP_Source/Filters/moogladder.d \
./DaisySP_Source/Filters/nlfilt.d \
./DaisySP_Source/Filters/svf.d \
./DaisySP_Source/Filters/tone.d 


# Each subdirectory must supply rules for building sources it contributes
DaisySP_Source/Filters/%.o DaisySP_Source/Filters/%.su DaisySP_Source/Filters/%.cyclo: ../DaisySP_Source/Filters/%.cpp DaisySP_Source/Filters/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -DMETAL_MAX_DEVICE_REGIONS=2 -DVIRTIO_MASTER_ONLY -DRPMSG_BUFFER_SIZE=128 -DSTM32H747xx -DCORE_CM7 -DNO_ATOMIC_64_SUPPORT -DMETAL_INTERNAL -DUSE_HAL_DRIVER -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/Synth/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/OPENAMP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/open-amp/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/libmetal/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM4/USB_HOST/App" -I"D:/STM32CubeMX/Disco747_xav_CPP/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Binn" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source/Utility" -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DaisySP_Source-2f-Filters

clean-DaisySP_Source-2f-Filters:
	-$(RM) ./DaisySP_Source/Filters/allpass.cyclo ./DaisySP_Source/Filters/allpass.d ./DaisySP_Source/Filters/allpass.o ./DaisySP_Source/Filters/allpass.su ./DaisySP_Source/Filters/atone.cyclo ./DaisySP_Source/Filters/atone.d ./DaisySP_Source/Filters/atone.o ./DaisySP_Source/Filters/atone.su ./DaisySP_Source/Filters/biquad.cyclo ./DaisySP_Source/Filters/biquad.d ./DaisySP_Source/Filters/biquad.o ./DaisySP_Source/Filters/biquad.su ./DaisySP_Source/Filters/comb.cyclo ./DaisySP_Source/Filters/comb.d ./DaisySP_Source/Filters/comb.o ./DaisySP_Source/Filters/comb.su ./DaisySP_Source/Filters/mode.cyclo ./DaisySP_Source/Filters/mode.d ./DaisySP_Source/Filters/mode.o ./DaisySP_Source/Filters/mode.su ./DaisySP_Source/Filters/moogladder.cyclo ./DaisySP_Source/Filters/moogladder.d ./DaisySP_Source/Filters/moogladder.o ./DaisySP_Source/Filters/moogladder.su ./DaisySP_Source/Filters/nlfilt.cyclo ./DaisySP_Source/Filters/nlfilt.d ./DaisySP_Source/Filters/nlfilt.o ./DaisySP_Source/Filters/nlfilt.su ./DaisySP_Source/Filters/svf.cyclo ./DaisySP_Source/Filters/svf.d ./DaisySP_Source/Filters/svf.o ./DaisySP_Source/Filters/svf.su ./DaisySP_Source/Filters/tone.cyclo ./DaisySP_Source/Filters/tone.d ./DaisySP_Source/Filters/tone.o ./DaisySP_Source/Filters/tone.su

.PHONY: clean-DaisySP_Source-2f-Filters

