/*
 * ssd1306_spi.c
 *
 *  Created on: Jul 13, 2017
 *      Author: ghost
 */

#include "c_types.h"
#include <gpio.h>
#include <osapi.h>
#include <eagle_soc.h>
#include <ssd1306_spi.h>
#include <spi_interface.h>

void ICACHE_FLASH_ATTR ssd1306_init(void)
{
    SpiAttr hSpiAttr;
    hSpiAttr.bitOrder = SpiBitOrder_MSBFirst;
    hSpiAttr.speed = SpiSpeed_2MHz;
    hSpiAttr.mode = SpiMode_Master;
    hSpiAttr.subMode = SpiSubMode_0;

    // Init HSPI GPIO
    WRITE_PERI_REG(PERIPHS_IO_MUX, 0x105);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, 2);//configure io to spi mode
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, 2);//configure io to spi mode
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, 2);//configure io to spi mode
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, 2);//configure io to spi mode
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U,FUNC_GPIO0);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U,FUNC_GPIO2);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0RXD_U,FUNC_GPIO3);

    GPIO_OUTPUT_SET(GPIO_ID_PIN(2), 0);
    GPIO_OUTPUT_SET(GPIO_ID_PIN(3), 1);

    GPIO_OUTPUT_SET(GPIO_ID_PIN(0), 1);
    GPIO_OUTPUT_SET(GPIO_ID_PIN(0), 0);
    GPIO_OUTPUT_SET(GPIO_ID_PIN(0), 1);


    SPIInit(SpiNum_HSPI, &hSpiAttr);

    uint32_t sendData[8] = { 0 };
    SpiData spiData;

    os_memset(sendData, 0, sizeof(sendData));
    //sendData = 0x00;

    spiData.cmd = 0xAFA5;
    spiData.cmdLen = 2;
    spiData.addr = 0;
    spiData.addrLen = 1;
    spiData.data = sendData;
    spiData.dataLen = 0;
    GPIO_OUTPUT_SET(GPIO_ID_PIN(3), 0);
    SPIMasterSendData(SpiNum_HSPI, &spiData);
    GPIO_OUTPUT_SET(GPIO_ID_PIN(3), 1);

}
