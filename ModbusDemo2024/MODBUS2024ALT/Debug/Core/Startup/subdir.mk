################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32g474retx.s 

OBJS += \
./Core/Startup/startup_stm32g474retx.o 

S_DEPS += \
./Core/Startup/startup_stm32g474retx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/BasicMathFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/BayesFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/CommonTables" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/ComplexMathFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/ControllerFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/DistanceFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/FastMathFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/FilteringFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/InterpolationFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/MatrixFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/QuaternionMathFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/StatisticsFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/SupportFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/SVMFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/TransformFunctions" -I"E:/Fibo_2_2/Stu/All_code/Robotic_Studio_III_ASRS/ModbusDemo2024/MODBUS2024ALT/Source/WindowFunctions" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32g474retx.d ./Core/Startup/startup_stm32g474retx.o

.PHONY: clean-Core-2f-Startup

