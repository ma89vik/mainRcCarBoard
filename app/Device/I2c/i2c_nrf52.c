#include "i2c_nrf52.h"
#include "board.h"
#include "device.h"
#include "i2c_device.h"
#include "log.h"

#include "nrfx_twim.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static const nrfx_twim_t m_twim_master = NRFX_TWIM_INSTANCE(0);

I2cApi_t nrf52_i2c_api = {.i2c_read = nrf52_i2c_read,
                          .i2c_write = nrf52_i2c_write};

static void nrf52_i2c_evt_handler(nrfx_twim_evt_t const *p_event,
                                  void *p_context)
{
    return;
}

I2cResult_t nrf52_i2c_init(Device_t *dev)
{
    if (!dev)
    {
        return I2C_ERR_INSTANCE;
    }
    uint32_t err_code;

    I2cDriverData_t *i2cData = (I2cDriverData_t *)(dev->driverData);
    I2cConfig_t *i2cConfig = (I2cConfig_t *)(dev->driverConfig);

    dev->driverApi = &nrf52_i2c_api;

    // Init the i2c hardware
    const nrfx_twim_config_t config = {
        .scl = TWI_SCL_M,
        .sda = TWI_SDA_M,
        .frequency = (nrf_twim_frequency_t)NRFX_TWIM_DEFAULT_CONFIG_FREQUENCY,
        .interrupt_priority = NRFX_TWIM_DEFAULT_CONFIG_IRQ_PRIORITY,
        .hold_bus_uninit = NRFX_TWIM_DEFAULT_CONFIG_HOLD_BUS_UNINIT,
    };

    // TX and RX will block, no event handler
    err_code = nrfx_twim_init(&m_twim_master, &config, NULL, NULL);

    if (err_code == NRFX_SUCCESS)
    {
        nrfx_twim_enable(&m_twim_master);
        return I2C_OK;
    }
    else
    {
        LOG_ERROR("i2c init err: %d\n", err_code);
        return I2C_ERR_CONFIG;
    }
}

I2cResult_t nrf52_i2c_write(uint8_t address, uint8_t *p_data, size_t length)
{
    uint32_t err_code =
        nrfx_twim_tx(&m_twim_master, address, p_data, length, false);

    if (err_code == NRFX_SUCCESS)
    {
        return I2C_OK;
    }
    else if (err_code == NRFX_ERROR_BUSY)
    {

        LOG_WARN("I2C tx busy\n");
        return I2C_BUSY;
    }
    else
    {
        LOG_ERROR("I2C tx err: %d\n", err_code);
        return I2C_ERR_TX;
    }
}

I2cResult_t nrf52_i2c_read(uint8_t address, uint8_t *p_data, size_t length)
{
    uint32_t err_code = nrfx_twim_rx(&m_twim_master, address, p_data, length);

    if (err_code == NRFX_SUCCESS)
    {
        return I2C_OK;
    }
    else if (err_code == NRFX_ERROR_BUSY)
    {

        LOG_WARN("I2C rx busy\n");
        return I2C_BUSY;
    }
    else
    {
        LOG_ERROR("I2C rx err: %d\n", err_code);
        return I2C_ERR_RX;
    }
}
