################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_SIZE += \
SIUL2_CodeExample_Z4_0.siz \


# All Target
all: SIUL2_CodeExample_Z4_0.elf secondary-outputs

dependents:
	-cd D:/git_projects/MPC5748G/SIUL2_CodeExample/SIUL2_CodeExample_Z2_2/Debug && $(MAKE) all
	-cd D:/git_projects/MPC5748G/SIUL2_CodeExample/SIUL2_CodeExample_Z4_1/Debug && $(MAKE) all

# Tool invocations
SIUL2_CodeExample_Z4_0.elf: $(OBJS) D:/git_projects/MPC5748G/SIUL2_CodeExample/SIUL2_CodeExample_Z4_0/Project_Settings/Linker_Files/57xx_flash.ld $(OSPT) $(USER_OBJS) D:/git_projects/MPC5748G/SIUL2_CodeExample/SIUL2_CodeExample_Z2_2/Debug/SIUL2_CodeExample_Z2_2.elf D:/git_projects/MPC5748G/SIUL2_CodeExample/SIUL2_CodeExample_Z4_1/Debug/SIUL2_CodeExample_Z4_1.elf
	@echo 'Building target: $@'
	@echo 'Invoking: Standard S32DS C Linker'
	powerpc-eabivle-gcc -o "SIUL2_CodeExample_Z4_0.elf" "@SIUL2_CodeExample_Z4_0.args"  $(USER_OBJS) $(LIBS) $(OSPT)
	@echo 'Finished building target: $@'
	@echo ' '

SIUL2_CodeExample_Z4_0.siz: SIUL2_CodeExample_Z4_0.elf
	@echo 'Invoking: Standard S32DS Print Size'
	powerpc-eabivle-size --format=berkeley SIUL2_CodeExample_Z4_0.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents
D:/git_projects/MPC5748G/SIUL2_CodeExample/SIUL2_CodeExample_Z2_2/Debug/SIUL2_CodeExample_Z2_2.elf:
D:/git_projects/MPC5748G/SIUL2_CodeExample/SIUL2_CodeExample_Z4_1/Debug/SIUL2_CodeExample_Z4_1.elf:

-include ../makefile.targets
