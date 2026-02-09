################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Third_Party/OpenAMP/open-amp/lib/virtio/subdir.mk
-include Third_Party/OpenAMP/open-amp/lib/rpmsg/subdir.mk
-include Third_Party/OpenAMP/open-amp/lib/remoteproc/subdir.mk
-include Third_Party/OpenAMP/libmetal/lib/system/generic/cortexm/subdir.mk
-include Third_Party/OpenAMP/libmetal/lib/system/generic/subdir.mk
-include Third_Party/OpenAMP/libmetal/lib/subdir.mk
-include Synth/Src/subdir.mk
-include OPENAMP/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/Legacy/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/Components/wm8994/subdir.mk
-include Drivers/BSP/Components/otm8009a/subdir.mk
-include Drivers/BSP/Components/nt35510/subdir.mk
-include Drivers/BSP/Components/mt25tl01g/subdir.mk
-include Drivers/BSP/Components/is42s32800j/subdir.mk
-include Drivers/BSP/Components/ft6x06/subdir.mk
-include Drivers/BSP/Components/adv7533/subdir.mk
-include Drivers/BSP/subdir.mk
-include DaisySP_Source/Utility/subdir.mk
-include DaisySP_Source/Synthesis/subdir.mk
-include DaisySP_Source/PhysicalModeling/subdir.mk
-include DaisySP_Source/Noise/subdir.mk
-include DaisySP_Source/Filters/subdir.mk
-include DaisySP_Source/Effects/subdir.mk
-include DaisySP_Source/Dynamics/subdir.mk
-include DaisySP_Source/Drums/subdir.mk
-include DaisySP_Source/Control/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Common/Src/subdir.mk
-include Binn/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CCM_DEPS)),)
-include $(CCM_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CXXM_DEPS)),)
-include $(CXXM_DEPS)
endif
ifneq ($(strip $(C++M_DEPS)),)
-include $(C++M_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := DK747CPP_CM7
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
DK747CPP_CM7.elf \

MAP_FILES += \
DK747CPP_CM7.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
DK747CPP_CM7.list \

OBJCOPY_HEX += \
DK747CPP_CM7.hex \

OBJCOPY_BIN += \
DK747CPP_CM7.bin \


# All Target
all: main-build

# Main-build Target
main-build: DK747CPP_CM7.elf secondary-outputs

# Tool invocations
DK747CPP_CM7.elf DK747CPP_CM7.map: $(OBJS) $(USER_OBJS) D:\STM32CubeMX\Disco747_xav_CPP\CM7\STM32H747XIHX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-g++ -o "DK747CPP_CM7.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"D:\STM32CubeMX\Disco747_xav_CPP\CM7\STM32H747XIHX_FLASH.ld" --specs=nosys.specs -Wl,-Map="DK747CPP_CM7.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

DK747CPP_CM7.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "DK747CPP_CM7.list"
	@echo 'Finished building: $@'
	@echo ' '

DK747CPP_CM7.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "DK747CPP_CM7.hex"
	@echo 'Finished building: $@'
	@echo ' '

DK747CPP_CM7.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "DK747CPP_CM7.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) DK747CPP_CM7.bin DK747CPP_CM7.elf DK747CPP_CM7.hex DK747CPP_CM7.list DK747CPP_CM7.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
