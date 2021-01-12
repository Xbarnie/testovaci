################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/MKL25Z128xxx4_Acel+tap_detection.c \
../source/filter.c \
../source/iic.c \
../source/lpsci.c \
../source/mma8451.c \
../source/mtb.c \
../source/semihost_hardfault.c 

OBJS += \
./source/MKL25Z128xxx4_Acel+tap_detection.o \
./source/filter.o \
./source/iic.o \
./source/lpsci.o \
./source/mma8451.o \
./source/mtb.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/MKL25Z128xxx4_Acel+tap_detection.d \
./source/filter.d \
./source/iic.d \
./source/lpsci.d \
./source/mma8451.d \
./source/mtb.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


