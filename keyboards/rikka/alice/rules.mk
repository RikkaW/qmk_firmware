DEBUG_ENABLE = yes
CUSTOM_MATRIX = yes

SRC += keyboard.c \
    matrix.c \
    alice.c
QUANTUM_LIB_SRC += spi_master.c

# Wildcard to allow APM32 MCU
DFU_SUFFIX_ARGS = -v FFFF -p FFFF
