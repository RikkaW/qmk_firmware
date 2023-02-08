DEBUG_ENABLE = yes
CUSTOM_MATRIX = lite

SRC += keyboard.c \
    matrix.c \
	sn74x165.c
QUANTUM_LIB_SRC += spi_master.c

# Wildcard to allow APM32 MCU
DFU_SUFFIX_ARGS = -v FFFF -p FFFF
