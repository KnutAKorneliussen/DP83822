# DP83822
DP83822 PHY driver based on STM32 BSP template

## About
STM32 BSP library doesn't support DP83822 PHY, this uses the exact same interface and can be considered a stand-in for the missing BSP driver.
Tested with STM32H743, with NetXDuo/ThreadX

## Example
```
#include "dp83822.h"

/* DP83822 IO functions */
static int32_t dp83822_io_init(void);
static int32_t dp83822_io_deinit (void);

static int32_t dp83822_io_write_reg(uint32_t DevAddr, uint32_t RegAddr, uint32_t RegVal);
static int32_t dp83822_io_read_reg(uint32_t DevAddr, uint32_t RegAddr, uint32_t *pRegVal);

static int32_t dp83822_io_get_tick(void);

/* DP83822 IO context object */
static dp83822_IOCtx_t  DP83822_IOCtx = { dp83822_io_init,
                                          dp83822_io_deinit,
                                          dp83822_io_write_reg,
                                          dp83822_io_read_reg,
                                          dp83822_io_get_tick
                                        };
/* DP83822 main object */
static dp83822_Object_t DP83822;

/**
  * @brief  Initialize the PHY MDIO interface
  * @param  None
  * @retval 0 if OK, -1 if ERROR
  */

int32_t dp83822_io_init(void)
{
  /* We assume that MDIO GPIO configuration is already done
     in the ETH_MspInit() else it should be done here
  */

  /* Configure the MDIO Clock */
  HAL_ETH_SetMDIOClockRange(&eth_handle);

  return ETH_PHY_STATUS_OK;
}

/**
  * @brief  De-Initialize the MDIO interface
  * @param  None
  * @retval 0 if OK, -1 if ERROR
  */
int32_t dp83822_io_deinit (void)
{
    return ETH_PHY_STATUS_OK;
}

/**
  * @brief  Read a PHY register through the MDIO interface.
  * @param  DevAddr: PHY port address
  * @param  RegAddr: PHY register address
  * @param  pRegVal: pointer to hold the register value
  * @retval 0 if OK -1 if Error
  */
int32_t dp83822_io_read_reg(uint32_t DevAddr, uint32_t RegAddr, uint32_t *pRegVal)
{
  if(HAL_ETH_ReadPHYRegister(&eth_handle, DevAddr, RegAddr, pRegVal) != HAL_OK)
  {
    return ETH_PHY_STATUS_ERROR;
  }

  return ETH_PHY_STATUS_OK;
}

int32_t dp83822_io_write_reg(uint32_t DevAddr, uint32_t RegAddr, uint32_t RegVal)
{
  if(HAL_ETH_WritePHYRegister(&eth_handle, DevAddr, RegAddr, RegVal) != HAL_OK)
  {
    return ETH_PHY_STATUS_ERROR;
  }

  return ETH_PHY_STATUS_OK;
}

/**
  * @brief  Get the time in millisecons used for internal PHY driver process.
  * @retval Time value
  */
int32_t dp83822_io_get_tick(void)
{
  return HAL_GetTick();
}
```
