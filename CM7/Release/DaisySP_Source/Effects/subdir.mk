################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DaisySP_Source/Effects/autowah.cpp \
../DaisySP_Source/Effects/bitcrush.cpp \
../DaisySP_Source/Effects/chorus.cpp \
../DaisySP_Source/Effects/decimator.cpp \
../DaisySP_Source/Effects/flanger.cpp \
../DaisySP_Source/Effects/fold.cpp \
../DaisySP_Source/Effects/overdrive.cpp \
../DaisySP_Source/Effects/phaser.cpp \
../DaisySP_Source/Effects/reverbsc.cpp \
../DaisySP_Source/Effects/sampleratereducer.cpp \
../DaisySP_Source/Effects/tremolo.cpp \
../DaisySP_Source/Effects/wavefolder.cpp 

OBJS += \
./DaisySP_Source/Effects/autowah.o \
./DaisySP_Source/Effects/bitcrush.o \
./DaisySP_Source/Effects/chorus.o \
./DaisySP_Source/Effects/decimator.o \
./DaisySP_Source/Effects/flanger.o \
./DaisySP_Source/Effects/fold.o \
./DaisySP_Source/Effects/overdrive.o \
./DaisySP_Source/Effects/phaser.o \
./DaisySP_Source/Effects/reverbsc.o \
./DaisySP_Source/Effects/sampleratereducer.o \
./DaisySP_Source/Effects/tremolo.o \
./DaisySP_Source/Effects/wavefolder.o 

CPP_DEPS += \
./DaisySP_Source/Effects/autowah.d \
./DaisySP_Source/Effects/bitcrush.d \
./DaisySP_Source/Effects/chorus.d \
./DaisySP_Source/Effects/decimator.d \
./DaisySP_Source/Effects/flanger.d \
./DaisySP_Source/Effects/fold.d \
./DaisySP_Source/Effects/overdrive.d \
./DaisySP_Source/Effects/phaser.d \
./DaisySP_Source/Effects/reverbsc.d \
./DaisySP_Source/Effects/sampleratereducer.d \
./DaisySP_Source/Effects/tremolo.d \
./DaisySP_Source/Effects/wavefolder.d 


# Each subdirectory must supply rules for building sources it contributes
DaisySP_Source/Effects/%.o DaisySP_Source/Effects/%.su DaisySP_Source/Effects/%.cyclo: ../DaisySP_Source/Effects/%.cpp DaisySP_Source/Effects/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -DMETAL_MAX_DEVICE_REGIONS=2 -DVIRTIO_MASTER_ONLY -DRPMSG_BUFFER_SIZE=128 -DSTM32H747xx -DCORE_CM7 -DNO_ATOMIC_64_SUPPORT -DMETAL_INTERNAL -DUSE_HAL_DRIVER -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/Synth/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/OPENAMP" -I"D:/STM32CubeMX/Disco747_xav_CPP/Drivers/BSP/Components/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/open-amp/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/Third_Party/OpenAMP/libmetal/lib/include" -I"D:/STM32CubeMX/Disco747_xav_CPP/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM4/USB_HOST/App" -I"D:/STM32CubeMX/Disco747_xav_CPP/Common" -I"D:/STM32CubeMX/Disco747_xav_CPP/Binn" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source" -I"D:/STM32CubeMX/Disco747_xav_CPP/CM7/DaisySP_Source/Utility" -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DaisySP_Source-2f-Effects

clean-DaisySP_Source-2f-Effects:
	-$(RM) ./DaisySP_Source/Effects/autowah.cyclo ./DaisySP_Source/Effects/autowah.d ./DaisySP_Source/Effects/autowah.o ./DaisySP_Source/Effects/autowah.su ./DaisySP_Source/Effects/bitcrush.cyclo ./DaisySP_Source/Effects/bitcrush.d ./DaisySP_Source/Effects/bitcrush.o ./DaisySP_Source/Effects/bitcrush.su ./DaisySP_Source/Effects/chorus.cyclo ./DaisySP_Source/Effects/chorus.d ./DaisySP_Source/Effects/chorus.o ./DaisySP_Source/Effects/chorus.su ./DaisySP_Source/Effects/decimator.cyclo ./DaisySP_Source/Effects/decimator.d ./DaisySP_Source/Effects/decimator.o ./DaisySP_Source/Effects/decimator.su ./DaisySP_Source/Effects/flanger.cyclo ./DaisySP_Source/Effects/flanger.d ./DaisySP_Source/Effects/flanger.o ./DaisySP_Source/Effects/flanger.su ./DaisySP_Source/Effects/fold.cyclo ./DaisySP_Source/Effects/fold.d ./DaisySP_Source/Effects/fold.o ./DaisySP_Source/Effects/fold.su ./DaisySP_Source/Effects/overdrive.cyclo ./DaisySP_Source/Effects/overdrive.d ./DaisySP_Source/Effects/overdrive.o ./DaisySP_Source/Effects/overdrive.su ./DaisySP_Source/Effects/phaser.cyclo ./DaisySP_Source/Effects/phaser.d ./DaisySP_Source/Effects/phaser.o ./DaisySP_Source/Effects/phaser.su ./DaisySP_Source/Effects/reverbsc.cyclo ./DaisySP_Source/Effects/reverbsc.d ./DaisySP_Source/Effects/reverbsc.o ./DaisySP_Source/Effects/reverbsc.su ./DaisySP_Source/Effects/sampleratereducer.cyclo ./DaisySP_Source/Effects/sampleratereducer.d ./DaisySP_Source/Effects/sampleratereducer.o ./DaisySP_Source/Effects/sampleratereducer.su ./DaisySP_Source/Effects/tremolo.cyclo ./DaisySP_Source/Effects/tremolo.d ./DaisySP_Source/Effects/tremolo.o ./DaisySP_Source/Effects/tremolo.su ./DaisySP_Source/Effects/wavefolder.cyclo ./DaisySP_Source/Effects/wavefolder.d ./DaisySP_Source/Effects/wavefolder.o ./DaisySP_Source/Effects/wavefolder.su

.PHONY: clean-DaisySP_Source-2f-Effects

