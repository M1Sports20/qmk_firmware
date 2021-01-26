# MCU name
MCU = STM32F072

CONSOLE_ENABLE = no	 # Console for debug
BOOTMAGIC_ENABLE = full  # Virtual DIP switch configuration
NKRO_ENABLE = yes        # USB Nkey rollover

CUSTOM_MATRIX = lite
SRC += matrix.c
