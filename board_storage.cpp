#include "pch.h"

/* This board stores settings in external SPI flash */
#if !defined(EFI_BOOTLOADER) && (EFI_STORAGE_MFS == TRUE)

#include "hal_serial_nor.h"
#include "hal_mfs.h"

/* SPI storage */
#define EFI_FLASH_SPI_CS_GPIO GPIOE
#define EFI_FLASH_SPI_CS_PIN 1

#define EFI_FLASH_SPI_AF 5U
#define EFI_FLASH_SPI_SCK Gpio::B3
#define EFI_FLASH_SPI_MISO Gpio::B4
#define EFI_FLASH_SPI_MOSI Gpio::B5
#define EFI_FLASH_SDPID SPID2

/* 8 Mbytes */
/* Not used, just FYI */
#define EFI_FLASH_SIZE (8 * 1024 * 1024)

/* Some fields in following struct are used for DMA transfers, so do not cache */
NO_CACHE SNORDriver snor1;

/*
 * Maximum speed SPI configuration (Clock = Fpclk / 2 =  21 MHz, CPHA=0, CPOL=0, MSb first).
 * SPI2 is clocked from APB1, APB1 clock is 42MHz
 * W25Qxx supports up to 133MHz in single SPI mode
 */
static const SPIConfig W25SpiCfg = {
    .circular = false,
    .end_cb = NULL,
    .ssport = EFI_FLASH_SPI_CS_GPIO,
    .sspad = EFI_FLASH_SPI_CS_PIN,
    .cr1 =
        SPI_CR1_8BIT_MODE |
        ((0 << SPI_CR1_BR_Pos) & SPI_CR1_BR) |
        0,
    .cr2 =
        SPI_CR2_8BIT_MODE |
        0,
};

/*
 * Flash driver configuration.
 */
static const SNORConfig W25FlashConfig = {
    .busp = &EFI_FLASH_SDPID,
    .buscfg = &W25SpiCfg
};

const MFSConfig mfsd_nor_config = {
    .flashp         = (BaseFlash *)&snor1,
    .erased         = 0xFFFFFFFFU,
#if 1
    .bank_size      = 512 * 1024U,
    .bank0_start    = 0U,
    .bank0_sectors  = 128U,
    .bank1_start    = 128U,
    .bank1_sectors  = 128U
#else
    .bank_size      = 64 * 1024U,
    .bank0_start    = 0U,
    .bank0_sectors  = 16U,
    .bank1_start    = 16U,
    .bank1_sectors  = 16U
#endif
};

void boardInitMfs()
{
#if SNOR_SHARED_BUS == FALSE
    spiStart(&EFI_FLASH_SDPID, &W25SpiCfg);
#endif

    palSetPad(EFI_FLASH_SPI_CS_GPIO, EFI_FLASH_SPI_CS_PIN);
    palSetPadMode(EFI_FLASH_SPI_CS_GPIO, EFI_FLASH_SPI_CS_PIN,
        PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
    palSetPadMode(getBrainPinPort(EFI_FLASH_SPI_SCK), getBrainPinIndex(EFI_FLASH_SPI_SCK),
        PAL_MODE_ALTERNATE(EFI_FLASH_SPI_AF) | PAL_STM32_OSPEED_HIGHEST);
    palSetPadMode(getBrainPinPort(EFI_FLASH_SPI_MISO), getBrainPinIndex(EFI_FLASH_SPI_MISO),
        PAL_MODE_ALTERNATE(EFI_FLASH_SPI_AF) | PAL_STM32_OSPEED_HIGHEST);
    palSetPadMode(getBrainPinPort(EFI_FLASH_SPI_MOSI), getBrainPinIndex(EFI_FLASH_SPI_MOSI),
        PAL_MODE_ALTERNATE(EFI_FLASH_SPI_AF) | PAL_STM32_OSPEED_HIGHEST);

    /* Initializing and starting flash driver. */
    snorObjectInit(&snor1);
    snorStart(&snor1, &W25FlashConfig);
}

const MFSConfig *boardGetMfsConfig()
{
    return &mfsd_nor_config;
}

#endif /* EFI_STORAGE_MFS == TRUE */
