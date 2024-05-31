################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ModBusRTU.c \
../Core/Src/call_data.c \
../Core/Src/call_mode.c \
../Core/Src/globalVar.c \
../Core/Src/gripper.c \
../Core/Src/main.c \
../Core/Src/motor_control.c \
../Core/Src/stm32g4xx_hal_msp.c \
../Core/Src/stm32g4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g4xx.c 

OBJS += \
./Core/Src/ModBusRTU.o \
./Core/Src/call_data.o \
./Core/Src/call_mode.o \
./Core/Src/globalVar.o \
./Core/Src/gripper.o \
./Core/Src/main.o \
./Core/Src/motor_control.o \
./Core/Src/stm32g4xx_hal_msp.o \
./Core/Src/stm32g4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g4xx.o 

C_DEPS += \
./Core/Src/ModBusRTU.d \
./Core/Src/call_data.d \
./Core/Src/call_mode.d \
./Core/Src/globalVar.d \
./Core/Src/gripper.d \
./Core/Src/main.d \
./Core/Src/motor_control.d \
./Core/Src/stm32g4xx_hal_msp.d \
./Core/Src/stm32g4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/Include -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/BasicMathFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/BayesFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/CommonTables" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/ComplexMathFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/ControllerFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/DistanceFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/FastMathFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/FilteringFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/InterpolationFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/MatrixFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/QuaternionMathFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/StatisticsFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/SupportFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/SVMFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/TransformFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/WindowFunctions" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ModBusRTU.cyclo ./Core/Src/ModBusRTU.d ./Core/Src/ModBusRTU.o ./Core/Src/ModBusRTU.su ./Core/Src/call_data.cyclo ./Core/Src/call_data.d ./Core/Src/call_data.o ./Core/Src/call_data.su ./Core/Src/call_mode.cyclo ./Core/Src/call_mode.d ./Core/Src/call_mode.o ./Core/Src/call_mode.su ./Core/Src/globalVar.cyclo ./Core/Src/globalVar.d ./Core/Src/globalVar.o ./Core/Src/globalVar.su ./Core/Src/gripper.cyclo ./Core/Src/gripper.d ./Core/Src/gripper.o ./Core/Src/gripper.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/motor_control.cyclo ./Core/Src/motor_control.d ./Core/Src/motor_control.o ./Core/Src/motor_control.su ./Core/Src/stm32g4xx_hal_msp.cyclo ./Core/Src/stm32g4xx_hal_msp.d ./Core/Src/stm32g4xx_hal_msp.o ./Core/Src/stm32g4xx_hal_msp.su ./Core/Src/stm32g4xx_it.cyclo ./Core/Src/stm32g4xx_it.d ./Core/Src/stm32g4xx_it.o ./Core/Src/stm32g4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32g4xx.cyclo ./Core/Src/system_stm32g4xx.d ./Core/Src/system_stm32g4xx.o ./Core/Src/system_stm32g4xx.su

.PHONY: clean-Core-2f-Src

