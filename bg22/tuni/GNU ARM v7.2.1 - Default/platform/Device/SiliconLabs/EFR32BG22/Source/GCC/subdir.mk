################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/Device/SiliconLabs/EFR32BG22/Source/GCC/startup_efr32bg22.c 

OBJS += \
./platform/Device/SiliconLabs/EFR32BG22/Source/GCC/startup_efr32bg22.o 

C_DEPS += \
./platform/Device/SiliconLabs/EFR32BG22/Source/GCC/startup_efr32bg22.d 


# Each subdirectory must supply rules for building sources it contributes
platform/Device/SiliconLabs/EFR32BG22/Source/GCC/startup_efr32bg22.o: ../platform/Device/SiliconLabs/EFR32BG22/Source/GCC/startup_efr32bg22.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DNVM3_DEFAULT_NVM_SIZE=24576' '-D__StackLimit=0x20000000' '-D__HEAP_SIZE=0xD00' '-DHAL_CONFIG=1' '-D__STACK_SIZE=0x800' '-DEFR32BG22C224F512IM40=1' -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/Device/SiliconLabs/EFR32BG22/Include" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/emlib/inc" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/app/bluetooth/common/util" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/CMSIS/Include" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/emdrv/dmadrv/inc" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/emlib/src" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/hardware/kit/common/halconfig" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/emdrv/nvm3/src" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/protocol/bluetooth/ble_stack/inc/common" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/radio/rail_lib/common" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/Device/SiliconLabs/EFR32BG22/Source" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/emdrv/nvm3/inc" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/halconfig/inc/hal-config" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/service/sleeptimer/inc" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/emdrv/gpiointerrupt/inc" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/hardware/kit/common/bsp" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/hardware/kit/common/drivers" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/emdrv/sleep/inc" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/bootloader/api" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/Device/SiliconLabs/EFR32BG22/Source/GCC" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/emdrv/common/inc" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/common/inc" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/emdrv/uartdrv/inc" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/hardware/kit/EFR32BG22_BRD4184A/config" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/service/sleeptimer/config" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/service/sleeptimer/src" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/emdrv/dmadrv/src" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/emdrv/sleep/src" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/emdrv/gpiointerrupt/src" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/radio/rail_lib/protocol/ble" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/protocol/bluetooth/ble_stack/inc/soc" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/radio/rail_lib/protocol/ieee802154" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni" -I"/Users/mvalkama/SimplicityStudio/v4_workspace/tuni/platform/bootloader" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/Device/SiliconLabs/EFR32BG22/Source/GCC/startup_efr32bg22.d" -MT"platform/Device/SiliconLabs/EFR32BG22/Source/GCC/startup_efr32bg22.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


