/**
  ******************************************************************************
  * @file    dp83822.c
  * @author  Knut A. Korneliussen
  * @brief   Driver for TI DP83822 Gigabit Ethernet PHY.
  ******************************************************************************
  * @attention
  *
  * This software is provided AS-IS, adapted for DP83822 based on ST's LAN8742 BSP.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <dp83822.h>

/* Private define ------------------------------------------------------------*/
#define DP83822_MAX_DEV_ADDR   ((uint32_t)31U)

/* Private function prototypes -----------------------------------------------*/
static int32_t DP83822_ReadReg(uint32_t PhyAddr, uint32_t RegAddr, uint32_t *RegVal);
static int32_t DP83822_WriteReg(uint32_t PhyAddr, uint32_t RegAddr, uint32_t RegVal);

/**
  * @brief  Register IO functions to component object
  * @param  pObj: device object of dp83822_Object_t.
  * @param  ioctx: holds device IO functions.
  * @retval DP83822_STATUS_OK if OK
  *         DP83822_STATUS_ERROR if missing mandatory function
  */
int32_t DP83822_RegisterBusIO(dp83822_Object_t *pObj, dp83822_IOCtx_t *ioctx)
{
  if(!pObj || !ioctx->ReadReg || !ioctx->WriteReg || !ioctx->GetTick)
  {
    return DP83822_STATUS_ERROR;
  }

  pObj->IO.Init     = ioctx->Init;
  pObj->IO.DeInit   = ioctx->DeInit;
  pObj->IO.ReadReg  = ioctx->ReadReg;
  pObj->IO.WriteReg = ioctx->WriteReg;
  pObj->IO.GetTick  = ioctx->GetTick;

  return DP83822_STATUS_OK;
}

/**
  * @brief  Initialize the DP83822 and configure hardware resources
  * @param  pObj: device object dp83822_Object_t.
  * @retval DP83822_STATUS_OK if OK
  *         DP83822_STATUS_ADDRESS_ERROR if cannot find device address
  *         DP83822_STATUS_READ_ERROR if cannot read register
  */
int32_t DP83822_Init(dp83822_Object_t *pObj)
{
  uint32_t reg = 0, addr = 0;
  int32_t status = DP83822_STATUS_OK;

  if(pObj->Is_Initialized == 0)
  {
    if(pObj->IO.Init)
    {
      /* GPIO/clock init */
      pObj->IO.Init();
    }

    pObj->DevAddr = DP83822_MAX_DEV_ADDR + 1;

    /* Detect PHY address via SMR */
    for(addr = 0; addr <= DP83822_MAX_DEV_ADDR; addr++)
    {
        uint32_t reg1 = 0, reg2 = 0;
        if(pObj->IO.ReadReg(addr, DP83822_PHYI1R, &reg1) < 0)
            continue;
        if(pObj->IO.ReadReg(addr, DP83822_PHYI2R, &reg2) < 0)
            continue;
        if(reg1 != 0xFFFF && reg2 != 0xFFFF)
		{
            pObj->DevAddr = addr;
            status = DP83822_STATUS_OK;
            break;
		}
        else
        {
        	continue;
        }
    }

    if (pObj->DevAddr > DP83822_MAX_DEV_ADDR)
    {
        return DP83822_STATUS_ADDRESS_ERROR;
    }

    if(status == DP83822_STATUS_OK)
    {
      /* Verify PHY ID */
    	uint32_t reg1 = 0, reg2 = 0;
    	pObj->IO.ReadReg(pObj->DevAddr, DP83822_PHYI1R, &reg1);
    	pObj->IO.ReadReg(pObj->DevAddr, DP83822_PHYI2R, &reg2);

    	/* Verify OUI bits */
    	if (reg1 != DP83822_PHYI1R_OUI_3_18)
    	    return DP83822_STATUS_ADDRESS_ERROR;

      /* Soft reset */
      pObj->IO.WriteReg(pObj->DevAddr, DP83822_BMCR, DP83822_BMCR_SOFT_RESET);
      do
      {
        pObj->IO.ReadReg(pObj->DevAddr, DP83822_BMCR, &reg);
      } while(reg & DP83822_BMCR_SOFT_RESET);

      /* Enable and restart autonegotiation */
      pObj->IO.WriteReg(pObj->DevAddr, DP83822_BMCR, DP83822_BMCR_AUTONEGO_EN | DP83822_BMCR_RESTART_AUTONEGO);
      do
      {
        pObj->IO.ReadReg(pObj->DevAddr, DP83822_BMCR, &reg);
      } while(!(reg & DP83822_BMCR_AUTONEGO_EN));

      /* Wait link up */
      do
      {
        pObj->IO.ReadReg(pObj->DevAddr, DP83822_BMSR, &reg);
      } while(!(reg & DP83822_BMSR_LINK_STATUS));
      pObj->IO.ReadReg(pObj->DevAddr, DP83822_BMSR, &reg);

      pObj->Is_Initialized = 1;
    }
  }
  return status;
}

/**
  * @brief  De-Initialize the DP83822 and its resources
  * @param  pObj: device object dp83822_Object_t.
  * @retval DP83822_STATUS_OK
  */
int32_t DP83822_DeInit(dp83822_Object_t *pObj)
{
  if(pObj->Is_Initialized)
  {
    if(pObj->IO.DeInit)
    {
      pObj->IO.DeInit();
    }
    pObj->Is_Initialized = 0;
  }
  return DP83822_STATUS_OK;
}

/**
  * @brief  Disable power down mode
  */
int32_t DP83822_DisablePowerDownMode(dp83822_Object_t *pObj)
{
  uint32_t val = 0;
  if(pObj->IO.ReadReg(pObj->DevAddr, DP83822_BMCR, &val) < 0)
    return DP83822_STATUS_READ_ERROR;
  val &= ~DP83822_BMCR_POWER_DOWN;
  if(pObj->IO.WriteReg(pObj->DevAddr, DP83822_BMCR, val) < 0)
    return DP83822_STATUS_WRITE_ERROR;
  return DP83822_STATUS_OK;
}

/**
  * @brief  Enable power down mode
  */
int32_t DP83822_EnablePowerDownMode(dp83822_Object_t *pObj)
{
  uint32_t val = 0;
  if(pObj->IO.ReadReg(pObj->DevAddr, DP83822_BMCR, &val) < 0)
    return DP83822_STATUS_READ_ERROR;
  val |= DP83822_BMCR_POWER_DOWN;
  if(pObj->IO.WriteReg(pObj->DevAddr, DP83822_BMCR, val) < 0)
    return DP83822_STATUS_WRITE_ERROR;
  return DP83822_STATUS_OK;
}

/**
  * @brief  Start auto-negotiation
  */
int32_t DP83822_StartAutoNego(dp83822_Object_t *pObj)
{
  uint32_t val = 0;
  if(pObj->IO.ReadReg(pObj->DevAddr, DP83822_BMCR, &val) < 0)
    return DP83822_STATUS_READ_ERROR;
  val |= DP83822_BMCR_AUTONEGO_EN;
  if(pObj->IO.WriteReg(pObj->DevAddr, DP83822_BMCR, val) < 0)
    return DP83822_STATUS_WRITE_ERROR;
  return DP83822_STATUS_OK;
}

/**
  * @brief  Get link state
  */
int32_t DP83822_GetLinkState(dp83822_Object_t *pObj)
{
  uint32_t bsr = 0, bcr = 0;
  if(pObj->IO.ReadReg(pObj->DevAddr, DP83822_BMSR, &bsr) < 0)
    return DP83822_STATUS_READ_ERROR;
  if(!(bsr & DP83822_BMSR_LINK_STATUS))
    return DP83822_STATUS_LINK_DOWN;

  if(pObj->IO.ReadReg(pObj->DevAddr, DP83822_BMCR, &bcr) < 0)
    return DP83822_STATUS_READ_ERROR;

  if((bcr & DP83822_BMCR_AUTONEGO_EN) == 0)
  {
    /* Forced mode */
    if((bcr & DP83822_BMCR_SPEED_SELECT) && (bcr & DP83822_BMCR_DUPLEX_MODE))
      return DP83822_STATUS_100MBITS_FULLDUPLEX;
    else if(bcr & DP83822_BMCR_SPEED_SELECT)
      return DP83822_STATUS_100MBITS_HALFDUPLEX;
    else if(bcr & DP83822_BMCR_DUPLEX_MODE)
      return DP83822_STATUS_10MBITS_FULLDUPLEX;
    else
      return DP83822_STATUS_10MBITS_HALFDUPLEX;
  }
  else
  {
	    /* Auto-negotiated, read PHYSTS */
	    if(pObj->IO.ReadReg(pObj->DevAddr, DP83822_PHYSTS, &bsr) < 0)
	      return DP83822_STATUS_READ_ERROR;
	    if(!(bsr & DP83822_PHYSTS_AUTONEGO_DONE))
	      return DP83822_STATUS_AUTONEGO_NOTDONE;

	    /* decode speed/duplex from bits [2:1] of PHYSTS */
	    switch (bsr & (DP83822_PHYSTS_SPEED_MASK | DP83822_PHYSTS_DUPLEX_MASK))
	    {

	      case 0U:
	        return DP83822_STATUS_100MBITS_HALFDUPLEX;
	      case DP83822_PHYSTS_DUPLEX_MASK:
	        return DP83822_STATUS_100MBITS_FULLDUPLEX;
	      case DP83822_PHYSTS_SPEED_MASK:
	        return DP83822_STATUS_10MBITS_HALFDUPLEX;
	      case (DP83822_PHYSTS_SPEED_MASK | DP83822_PHYSTS_DUPLEX_MASK):
	        return DP83822_STATUS_10MBITS_FULLDUPLEX;
	      default:
	        return DP83822_STATUS_ERROR;
	    }
  }
}

/**
  * @brief  Set link state (forced)
  */
int32_t DP83822_SetLinkState(dp83822_Object_t *pObj, uint32_t LinkState)
{
  uint32_t bcr = 0;
  if(pObj->IO.ReadReg(pObj->DevAddr, DP83822_BMCR, &bcr) < 0)
    return DP83822_STATUS_READ_ERROR;
  bcr &= ~(DP83822_BMCR_AUTONEGO_EN | DP83822_BMCR_SPEED_SELECT | DP83822_BMCR_DUPLEX_MODE);

  switch(LinkState)
  {
    case DP83822_STATUS_100MBITS_FULLDUPLEX:
      bcr |= (DP83822_BMCR_SPEED_SELECT | DP83822_BMCR_DUPLEX_MODE);
      break;
    case DP83822_STATUS_100MBITS_HALFDUPLEX:
      bcr |= DP83822_BMCR_SPEED_SELECT;
      break;
    case DP83822_STATUS_10MBITS_FULLDUPLEX:
      bcr |= DP83822_BMCR_DUPLEX_MODE;
      break;
    default:
      return DP83822_STATUS_ERROR;
  }

  if(pObj->IO.WriteReg(pObj->DevAddr, DP83822_BMCR, bcr) < 0)
    return DP83822_STATUS_WRITE_ERROR;

  return DP83822_STATUS_OK;
}

/**
  * @brief  Enable loopback mode
  */
int32_t DP83822_EnableLoopbackMode(dp83822_Object_t *pObj)
{
  uint32_t bcr = 0;
  if(pObj->IO.ReadReg(pObj->DevAddr, DP83822_BMCR, &bcr) < 0)
    return DP83822_STATUS_READ_ERROR;
  bcr |= DP83822_BMCR_LOOPBACK;
  if(pObj->IO.WriteReg(pObj->DevAddr, DP83822_BMCR, bcr) < 0)
    return DP83822_STATUS_WRITE_ERROR;
  return DP83822_STATUS_OK;
}

/**
  * @brief  Disable loopback mode
  */
int32_t DP83822_DisableLoopbackMode(dp83822_Object_t *pObj)
{
  uint32_t bcr = 0;
  if(pObj->IO.ReadReg(pObj->DevAddr, DP83822_BMCR, &bcr) < 0)
    return DP83822_STATUS_READ_ERROR;
  bcr &= ~DP83822_BMCR_LOOPBACK;
  if(pObj->IO.WriteReg(pObj->DevAddr, DP83822_BMCR, bcr) < 0)
    return DP83822_STATUS_WRITE_ERROR;
  return DP83822_STATUS_OK;
}

/* Interrupt and status functions would follow similar patterns */

/**
  * @brief  Read PHY register (wrap HAL)
  */
static int32_t DP83822_ReadReg(uint32_t PhyAddr, uint32_t RegAddr, uint32_t *RegVal)
{
#ifdef USE_HAL_ETH_REGISTER_CALLBACKS
  extern ETH_HandleTypeDef heth;
  if(HAL_ETH_ReadPHYRegister(&heth, PhyAddr, RegAddr, RegVal) == HAL_OK)
    return DP83822_STATUS_OK;
  else
    return DP83822_STATUS_READ_ERROR;
#else
  return DP83822_STATUS_READ_ERROR;
#endif
}

/**
  * @brief  Write PHY register (wrap HAL)
  */
static int32_t DP83822_WriteReg(uint32_t PhyAddr, uint32_t RegAddr, uint32_t RegVal)
{
#ifdef USE_HAL_ETH_REGISTER_CALLBACKS
  extern ETH_HandleTypeDef heth;
  if(HAL_ETH_WritePHYRegister(&heth, PhyAddr, RegAddr, RegVal) == HAL_OK)
    return DP83822_STATUS_OK;
  else
    return DP83822_STATUS_WRITE_ERROR;
#else
  return DP83822_STATUS_WRITE_ERROR;
#endif
}
