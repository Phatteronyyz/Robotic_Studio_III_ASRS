################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/StatisticsFunctions.c \
../Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/StatisticsFunctionsF16.c 

OBJS += \
./Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/StatisticsFunctions.o \
./Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/StatisticsFunctionsF16.o 

C_DEPS += \
./Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/StatisticsFunctions.d \
./Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/StatisticsFunctionsF16.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/%.o Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/%.su Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/%.cyclo: ../Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/%.c Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/Include -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/BasicMathFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/BayesFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/CommonTables" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/ComplexMathFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/ControllerFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/DistanceFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/FastMathFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/FilteringFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/InterpolationFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/MatrixFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/QuaternionMathFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/StatisticsFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/SupportFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/SVMFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/TransformFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/WindowFunctions" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-ARM_CMSIS-2f-Source-2f-StatisticsFunctions

clean-Middlewares-2f-Third_Party-2f-ARM_CMSIS-2f-Source-2f-StatisticsFunctions:
	-$(RM) ./Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/StatisticsFunctions.cyclo ./Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/StatisticsFunctions.d ./Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/StatisticsFunctions.o ./Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/StatisticsFunctions.su ./Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/StatisticsFunctionsF16.cyclo ./Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/StatisticsFunctionsF16.d ./Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/StatisticsFunctionsF16.o ./Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions/StatisticsFunctionsF16.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-ARM_CMSIS-2f-Source-2f-StatisticsFunctions

