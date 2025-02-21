BOARDCPPSRC =  $(BOARD_DIR)/board_configuration.cpp \
    $(BOARD_DIR)/firmware/pinouts.cpp \
    $(BOARD_DIR)/default_tune.cpp \


BOARDINC += $(BOARD_DIR)/generated/controllers/generated

# defines SHORT_BOARD_NAME
include $(BOARD_DIR)/meta-info.env


# debug
DEBUG_LEVEL_OPT = -O0 -ggdb -g

# reduce memory usage monitoring
DDEFS += -DRAM_UNUSED_SIZE=100

# assign critical LED to a non-existent pin
DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::B7

# This board has 512K STM32F407
DDEFS += -DMIN_FLASH_SIZE=512
DDEFS += -DFLASH_ADDR=0x08075000
# DDEFS += -DEFI_STORAGE_INT_FLASH=FALSE

DDEFS += -DEFI_LUA=FALSE
DDEFS += -DEFI_HD44780_LCD=FALSE

# This board has no storage
DDEFS += -DEFI_FILE_LOGGING=FALSE
USE_FATFS = no