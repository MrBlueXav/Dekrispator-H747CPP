################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DaisySP_Source/Dynamics/balance.cpp \
../DaisySP_Source/Dynamics/compressor.cpp \
../DaisySP_Source/Dynamics/crossfade.cpp \
../DaisySP_Source/Dynamics/limiter.cpp 

OBJS += \
./DaisySP_Source/Dynamics/balance.o \
./DaisySP_Source/Dynamics/compressor.o \
./DaisySP_Source/Dynamics/crossfade.o \
./DaisySP_Source/Dynamics/limiter.o 

CPP_DEPS += \
./DaisySP_Source/Dynamics/balance.d \
./DaisySP_Source/Dynamics/compressor.d \
./DaisySP_Source/Dynamics/crossfade.d \
./DaisySP_Source/Dynamics/limiter.d 


# Each subdirectory must supply rules for building sources it contributes
DaisySP_Source/Dynamics/%.o DaisySP_Source/Dynamics/%.su DaisySP_Source/Dynamics/%.cyclo: ../DaisySP_Source/Dynamics/%.cpp DaisySP_Source/Dynamics/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -DMETAL_MAX_DEVICE_REGIONS=2 -DVIRTIO_MASTER_ONLY -DRPMSG_BUFFER_SIZE=128 -DSTM32H747xx -DCORE_CM7 -DNO_ATOMIC_64_SUPPORT -DMETAL_INTERNAL -DUSE_HAL_DRIVER -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/Synth/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/OPENAMP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/open-amp/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/libmetal/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM4/USB_HOST/App" -I"D:/STM32CubeMX/Disco747_xav_CPP/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Binn" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source/Utility" -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DaisySP_Source-2f-Dynamics

clean-DaisySP_Source-2f-Dynamics:
	-$(RM) ./DaisySP_Source/Dynamics/balance.cyclo ./DaisySP_Source/Dynamics/balance.d ./DaisySP_Source/Dynamics/balance.o ./DaisySP_Source/Dynamics/balance.su ./DaisySP_Source/Dynamics/compressor.cyclo ./DaisySP_Source/Dynamics/compressor.d ./DaisySP_Source/Dynamics/compressor.o ./DaisySP_Source/Dynamics/compressor.su ./DaisySP_Source/Dynamics/crossfade.cyclo ./DaisySP_Source/Dynamics/crossfade.d ./DaisySP_Source/Dynamics/crossfade.o ./DaisySP_Source/Dynamics/crossfade.su ./DaisySP_Source/Dynamics/limiter.cyclo ./DaisySP_Source/Dynamics/limiter.d ./DaisySP_Source/Dynamics/limiter.o ./DaisySP_Source/Dynamics/limiter.su

.PHONY: clean-DaisySP_Source-2f-Dynamics

