/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2019 Google LLC.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "AppConfig.h"
#include <lib/support/CHIPPlatformMemory.h>
#include <platform/CHIPDeviceLayer.h>

#ifdef __cplusplus
extern "C" {
#endif
#include <assert.h>
#include <string.h>

#include <mbedtls/platform.h>

#if CHIP_ENABLE_OPENTHREAD
#include <openthread-core-config.h>
#include <openthread/cli.h>
#include <openthread/config.h>
#include <openthread/dataset.h>
#include <openthread/error.h>
#include <openthread/heap.h>
#include <openthread/icmp6.h>
#include <openthread/instance.h>
#include <openthread/link.h>
#include <openthread/platform/openthread-system.h>
#include <openthread/tasklet.h>
#include <openthread/thread.h>
#include <utils/uart.h>

#include "platform-efr32.h"
#include "sl_openthread.h"

#if OPENTHREAD_CONFIG_HEAP_EXTERNAL_ENABLE
#include "openthread/heap.h"
#endif // OPENTHREAD_CONFIG_HEAP_EXTERNAL_ENABLE
#endif // CHIP_ENABLE_OPENTHREAD

#include "init_efrPlatform.h"
#include "sl_component_catalog.h"
#include "sl_mbedtls.h"
#include "sl_system_init.h"

#include "uartdrv.h"
#include <stddef.h>
#include "sl_uartdrv_eusart_vcom_config.h"
#include "em_eusart.h"

#if SL_SYSTEM_VIEW
#include "SEGGER_SYSVIEW.h"
#endif

void initAntenna(void);

void tuya_log_rx_cb(uint32_t port_id){
    
}

UARTDRV_Handle_t ty_uart_data_2;

DEFINE_BUF_QUEUE(SL_UARTDRV_EUSART_VCOM_RX_BUFFER_SIZE, uartdrv_eusart_vcom_rx_buffer);
DEFINE_BUF_QUEUE(SL_UARTDRV_EUSART_VCOM_TX_BUFFER_SIZE, uartdrv_eusart_vcom_tx_buffer);

UARTDRV_InitEuart_t ty_uart_ch_1 = { 
  .port = EUSART0,
  .useLowFrequencyMode = false,
  .baudRate = 115200,
  .txPort = gpioPortD,
  .rxPort = gpioPortD,
  .txPin = 3,
  .rxPin = 2,
  .uartNum = 0,
  .stopBits = eusartStopbits1,
  .parity = eusartNoParity,
  .oversampling = eusartOVS16,
  .mvdis = eusartMajorityVoteEnable,//false,
  .fcType = uartdrvFlowControlNone,
  .ctsPort = SL_UARTDRV_EUSART_VCOM_CTS_PORT,
  .ctsPin = SL_UARTDRV_EUSART_VCOM_CTS_PIN,
  .rtsPort = SL_UARTDRV_EUSART_VCOM_RTS_PORT,
  .rtsPin = SL_UARTDRV_EUSART_VCOM_RTS_PIN,
  .rxQueue = (UARTDRV_Buffer_FifoQueue_t *)&uartdrv_eusart_vcom_rx_buffer,
  .txQueue = (UARTDRV_Buffer_FifoQueue_t *)&uartdrv_eusart_vcom_tx_buffer
};

// void EUSART0_RX_IRQHandler(void) 
// {
//   //TY_LOG_DEBUG("EUSART0_RX_IRQHandler*****!");
//   if (EUSART0->IF & EUSART_IF_RXFL) {
//     tuya_log_rx_cb(1);
//     EUSART_IntClear( EUSART0, EUSART_IF_RXFL );
//   }
// } 

extern "C" void tuya_log_uart_init(void)
{
    ty_uart_ch_1.baudRate = 921600;
    ty_uart_ch_1.parity = eusartNoParity;
    ty_uart_ch_1.stopBits = eusartStopbits1;
    ty_uart_ch_1.fcType = uartdrvFlowControlNone;

    UARTDRV_InitEuart(ty_uart_data_2, &ty_uart_ch_1);
    
    EUSART_IntClear( EUSART0, EUSART_IF_RXFL );
    NVIC_ClearPendingIRQ( EUSART0_RX_IRQn );
    /* Enable RX interrupts */
    EUSART_IntEnable( EUSART0, EUSART_IF_RXFL );
    NVIC_EnableIRQ( EUSART0_RX_IRQn );
    EUSART_Enable(EUSART0, eusartEnable);
    // tkl_uart_rx_irq_cb_reg(1, tuya_log_rx_cb);
    // // Clear previous RX interrupts
    // EUSART_IntClear(SL_UARTDRV_EUSART_VCOM_PERIPHERAL, EUSART_IF_RXFL);

    // // Enable RX interrupts
    // EUSART_IntEnable(SL_UARTDRV_EUSART_VCOM_PERIPHERAL, EUSART_IF_RXFL);

    // Enable EUSART
    // EUSART_Enable(SL_UARTDRV_EUSART_VCOM_PERIPHERAL, eusartEnable);    
}


void init_efrPlatform(void)
{
    sl_system_init();
    sl_mbedtls_init();
#if CHIP_ENABLE_OPENTHREAD
#ifdef MGM24
    sl_openthread_init();
#endif
    efr32RadioInit();
    efr32AlarmInit();
    efr32MiscInit();
#endif // CHIP_ENABLE_OPENTHREAD

#if SL_SYSTEM_VIEW
    SEGGER_SYSVIEW_Conf();
    SEGGER_SYSVIEW_Start();
#endif

#if SILABS_LOG_ENABLED
    silabsInitLog();
#endif
}

#ifdef __cplusplus
}
#endif
