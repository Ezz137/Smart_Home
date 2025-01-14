################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../ADC_Driver.c \
../DC_Motor_Driver.c \
../DIO.c \
../EEPROM.c \
../Led.c \
../Smart_House_Slave.c \
../SPI_Driver.c \
../Timer0_driver.c \
../Timer1_driver.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
ADC_Driver.o \
DC_Motor_Driver.o \
DIO.o \
EEPROM.o \
Led.o \
Smart_House_Slave.o \
SPI_Driver.o \
Timer0_driver.o \
Timer1_driver.o


OBJS_AS_ARGS +=  \
ADC_Driver.o \
DC_Motor_Driver.o \
DIO.o \
EEPROM.o \
Led.o \
Smart_House_Slave.o \
SPI_Driver.o \
Timer0_driver.o \
Timer1_driver.o


C_DEPS +=  \
ADC_Driver.d \
DC_Motor_Driver.d \
DIO.d \
EEPROM.d \
Led.d \
Smart_House_Slave.d \
SPI_Driver.d \
Timer0_driver.d \
Timer1_driver.d


C_DEPS_AS_ARGS +=  \
ADC_Driver.d \
DC_Motor_Driver.d \
DIO.d \
EEPROM.d \
Led.d \
Smart_House_Slave.d \
SPI_Driver.d \
Timer0_driver.d \
Timer1_driver.d


OUTPUT_FILE_PATH +=Smart_House_Slave.elf

OUTPUT_FILE_PATH_AS_ARGS +=Smart_House_Slave.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler



















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -O1 -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=atmega32   -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Smart_House_Slave.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group  -mmcu=atmega32  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "Smart_House_Slave.elf" "Smart_House_Slave.hex"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Smart_House_Slave.elf" "Smart_House_Slave.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objdump.exe" -h -S "Smart_House_Slave.elf" > "Smart_House_Slave.lss"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "Smart_House_Slave.elf" "Smart_House_Slave.srec"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-size.exe" "Smart_House_Slave.elf"
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "Smart_House_Slave.elf" "Smart_House_Slave.a" "Smart_House_Slave.hex" "Smart_House_Slave.lss" "Smart_House_Slave.eep" "Smart_House_Slave.map" "Smart_House_Slave.srec"
	