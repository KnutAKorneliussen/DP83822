/**
  ******************************************************************************
  * @file    dp83822.h
  * @author  Knut A. Korneliussen
  * @brief   PHY driver for Texas Instruments DP83822 Gigabit Ethernet PHY.
  ******************************************************************************
  * @attention
  *
  * This software is provided AS-IS, adapted for DP83822 based on ST's LAN8742 BSP.
  *
  ******************************************************************************
  */

#ifndef DP83822_H
#define DP83822_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

/* Exported constants
 * Unused registers / values can be considered untested and therefore commented out.
 * --------------------------------------------------------*/
/* DP83822 Registers MII Mapping */
#define DP83822_BMCR           ((uint16_t)0x0000U)
#define DP83822_BMSR           ((uint16_t)0x0001U)
#define DP83822_PHYI1R         ((uint16_t)0x0002U)
#define DP83822_PHYI2R         ((uint16_t)0x0003U)
//#define DP83822_ANAR          ((uint16_t)0x0004U)
//#define DP83822_ANLPAR        ((uint16_t)0x0005U)
//#define DP83822_ANER          ((uint16_t)0x0006U)
//#define DP83822_ANNPTR        ((uint16_t)0x0007U)
//#define DP83822_ANNPRR        ((uint16_t)0x0008U)
//#define DP83822_MMDACR        ((uint16_t)0x000DU)
//#define DP83822_MMDAADR       ((uint16_t)0x000EU)
//#define DP83822_ENCTR         ((uint16_t)0x0010U)
//
//
//#define DP83822_TPDCR         ((uint16_t)0x0018U)
//#define DP83822_TCSR          ((uint16_t)0x0019U)
//#define DP83822_SECR          ((uint16_t)0x001AU)
//#define DP83822_SCSIR         ((uint16_t)0x001BU)
//#define DP83822_CLR           ((uint16_t)0x001CU)
//
//
#define DP83822_PHYSTS        0x0010U
//
///* BMCR Bit Definition */
#define DP83822_BMCR_SOFT_RESET         ((uint16_t)0x8000U)
#define DP83822_BMCR_LOOPBACK           ((uint16_t)0x4000U)
#define DP83822_BMCR_SPEED_SELECT       ((uint16_t)0x2000U)
#define DP83822_BMCR_AUTONEGO_EN        ((uint16_t)0x1000U)
#define DP83822_BMCR_POWER_DOWN         ((uint16_t)0x0800U)
//#define DP83822_BMCR_ISOLATE            ((uint16_t)0x0400U)
#define DP83822_BMCR_RESTART_AUTONEGO   ((uint16_t)0x0200U)
#define DP83822_BMCR_DUPLEX_MODE        ((uint16_t)0x0100U)
//
///* BSR Bit Definition */
//#define DP83822_BMSR_100BASE_T4         ((uint16_t)0x8000U)
//#define DP83822_BMSR_100BASE_TX_FD      ((uint16_t)0x4000U)
//#define DP83822_BMSR_100BASE_TX_HD      ((uint16_t)0x2000U)
//#define DP83822_BMSR_10BASE_T_FD        ((uint16_t)0x1000U)
//#define DP83822_BMSR_10BASE_T_HD        ((uint16_t)0x0800U)
//#define DP83822_BMSR_100BASE_T2_FD      ((uint16_t)0x0400U)
//#define DP83822_BMSR_100BASE_T2_HD      ((uint16_t)0x0200U)
//#define DP83822_BMSR_EXTENDED_STATUS    ((uint16_t)0x0100U)
//#define DP83822_BMSR_AUTONEGO_CPLT      ((uint16_t)0x0020U)
//#define DP83822_BMSR_REMOTE_FAULT       ((uint16_t)0x0010U)
//#define DP83822_BMSR_AUTONEGO_ABILITY   ((uint16_t)0x0008U)
#define DP83822_BMSR_LINK_STATUS        ((uint16_t)0x0004U)
//#define DP83822_BMSR_JABBER_DETECT      ((uint16_t)0x0002U)
//#define DP83822_BMSR_EXTENDED_CAP       ((uint16_t)0x0001U)
//
///* PHYID1R Bit Definition (OUI bits [18:3]) */
#define DP83822_PHYI1R_OUI_3_18        ((uint16_t)0x2000U)
//
///* PHYID2R Bit Definition */
//#define DP83822_PHYI2R_OUI_19_24       ((uint16_t)0x08U)  /* bits [15:10] */
//#define DP83822_PHYI2R_MODEL_NBR       ((uint16_t)0x0FU)  /* bits [9:4]  */
//#define DP83822_PHYI2R_REVISION_NBR    ((uint16_t)0x000FU)  /* bits [3:0]  */
//
///* ANAR Bit Definition */
//#define DP83822_ANAR_NEXT_PAGE               ((uint16_t)0x8000U)
//#define DP83822_ANAR_REMOTE_FAULT            ((uint16_t)0x2000U)
//#define DP83822_ANAR_PAUSE_OPERATION         ((uint16_t)0x0C00U)
//#define DP83822_ANAR_PO_NOPAUSE              ((uint16_t)0x0000U)
//#define DP83822_ANAR_PO_SYMMETRIC_PAUSE      ((uint16_t)0x0400U)
//#define DP83822_ANAR_PO_ASYMMETRIC_PAUSE     ((uint16_t)0x0800U)
//#define DP83822_ANAR_PO_ADVERTISE_SUPPORT    ((uint16_t)0x0C00U)
//#define DP83822_ANAR_100BASE_TX_FD           ((uint16_t)0x0100U)
//#define DP83822_ANAR_100BASE_TX              ((uint16_t)0x0080U)
//#define DP83822_ANAR_10BASE_T_FD             ((uint16_t)0x0040U)
//#define DP83822_ANAR_10BASE_T                ((uint16_t)0x0020U)
//#define DP83822_ANAR_SELECTOR_FIELD          ((uint16_t)0x000FU)
//
///* ANLPAR Bit Definition */
//#define DP83822_ANLPAR_NEXT_PAGE            ((uint16_t)0x8000U)
//#define DP83822_ANLPAR_REMOTE_FAULT         ((uint16_t)0x2000U)
//#define DP83822_ANLPAR_PAUSE_OPERATION      ((uint16_t)0x0C00U)
//#define DP83822_ANLPAR_PO_NOPAUSE           ((uint16_t)0x0000U)
//#define DP83822_ANLPAR_PO_SYMMETRIC_PAUSE   ((uint16_t)0x0400U)
//#define DP83822_ANLPAR_PO_ASYMMETRIC_PAUSE  ((uint16_t)0x0800U)
//#define DP83822_ANLPAR_PO_ADVERTISE_SUPPORT ((uint16_t)0x0C00U)
//#define DP83822_ANLPAR_100BASE_TX_FD        ((uint16_t)0x0100U)
//#define DP83822_ANLPAR_100BASE_TX           ((uint16_t)0x0080U)
//#define DP83822_ANLPAR_10BASE_T_FD          ((uint16_t)0x0040U)
//#define DP83822_ANLPAR_10BASE_T             ((uint16_t)0x0020U)
//#define DP83822_ANLPAR_SELECTOR_FIELD       ((uint16_t)0x000FU)
//
///* ANER Bit Definition */
//#define DP83822_ANER_RX_NP_LOCATION_ABLE    ((uint16_t)0x0040U)
//#define DP83822_ANER_RX_NP_STORAGE_LOCATION ((uint16_t)0x0020U)
//#define DP83822_ANER_PARALLEL_DETECT_FAULT  ((uint16_t)0x0010U)
//#define DP83822_ANER_LP_NP_ABLE             ((uint16_t)0x0008U)
//#define DP83822_ANER_NP_ABLE                ((uint16_t)0x0004U)
//#define DP83822_ANER_PAGE_RECEIVED          ((uint16_t)0x0002U)
//#define DP83822_ANER_LP_AUTONEG_ABLE        ((uint16_t)0x0001U)
//
///* ANNPTR Bit Definition */
//#define DP83822_ANNPTR_NEXT_PAGE         ((uint16_t)0x8000U)
//#define DP83822_ANNPTR_MESSAGE_PAGE      ((uint16_t)0x2000U)
//#define DP83822_ANNPTR_ACK2              ((uint16_t)0x1000U)
//#define DP83822_ANNPTR_TOGGLE            ((uint16_t)0x0800U)
//#define DP83822_ANNPTR_MESSAGGE_CODE     ((uint16_t)0x07FFU)
//
///* ANNPRR Bit Definition */
//#define DP83822_ANNPRR_NEXT_PAGE         ((uint16_t)0x8000U)
//#define DP83822_ANNPRR_ACK               ((uint16_t)0x4000U)
//#define DP83822_ANNPRR_MESSAGE_PAGE      ((uint16_t)0x2000U)
//#define DP83822_ANNPRR_ACK2              ((uint16_t)0x1000U)
//#define DP83822_ANNPRR_TOGGLE            ((uint16_t)0x0800U)
//#define DP83822_ANNPRR_MESSAGGE_CODE     ((uint16_t)0x07FFU)
//
///* MMD Access Control Register */
//#define DP83822_MMDACR_MMD_FUNCTION       ((uint16_t)0xC000U)
//#define DP83822_MMDACR_MMD_FUNCTION_ADDR  ((uint16_t)0x0000U)
//#define DP83822_MMDACR_MMD_FUNCTION_DATA  ((uint16_t)0x4000U)
//#define DP83822_MMDACR_MMD_DEV_ADDR       ((uint16_t)0x001FU)
//
///* MCSR Bit Definition */
//
//#define DP83822_MCSR_FARLOOPBACK      ((uint16_t)0x0200U)
//#define DP83822_MCSR_ALTINT           ((uint16_t)0x0040U)
//#define DP83822_MCSR_ENERGYON         ((uint16_t)0x0002U)
//
///* ENCTR Bit Definition */
//#define DP83822_ENCTR_TX_ENABLE             ((uint16_t)0x8000U)
//#define DP83822_ENCTR_TX_TIMER              ((uint16_t)0x6000U)
//#define DP83822_ENCTR_TX_TIMER_1S           ((uint16_t)0x0000U)
//#define DP83822_ENCTR_TX_TIMER_768MS        ((uint16_t)0x2000U)
//#define DP83822_ENCTR_TX_TIMER_512MS        ((uint16_t)0x4000U)
//#define DP83822_ENCTR_TX_TIMER_265MS        ((uint16_t)0x6000U)
//#define DP83822_ENCTR_RX_ENABLE             ((uint16_t)0x1000U)
//#define DP83822_ENCTR_RX_MAX_INTERVAL       ((uint16_t)0x0C00U)
//#define DP83822_ENCTR_RX_MAX_INTERVAL_64MS  ((uint16_t)0x0000U)
//#define DP83822_ENCTR_RX_MAX_INTERVAL_256MS ((uint16_t)0x0400U)
//#define DP83822_ENCTR_RX_MAX_INTERVAL_512MS ((uint16_t)0x0800U)
//#define DP83822_ENCTR_RX_MAX_INTERVAL_1S    ((uint16_t)0x0C00U)
//#define DP83822_ENCTR_EX_CROSS_OVER         ((uint16_t)0x0002U)
//#define DP83822_ENCTR_EX_MANUAL_CROSS_OVER  ((uint16_t)0x0001U)
//
///* SMR Bit Definition */
//#define DP83822_SMR_MODE       ((uint16_t)0x00E0U)
//
//
///* TPDCR Bit Definition */
//#define DP83822_TPDCR_DELAY_IN                 ((uint16_t)0x8000U)
//#define DP83822_TPDCR_LINE_BREAK_COUNTER       ((uint16_t)0x7000U)
//#define DP83822_TPDCR_PATTERN_HIGH             ((uint16_t)0x0FC0U)
//#define DP83822_TPDCR_PATTERN_LOW              ((uint16_t)0x003FU)
//
///* TCSR Bit Definition */
//#define DP83822_TCSR_TDR_ENABLE           ((uint16_t)0x8000U)
//#define DP83822_TCSR_TDR_AD_FILTER_ENABLE ((uint16_t)0x4000U)
//#define DP83822_TCSR_TDR_CH_CABLE_TYPE    ((uint16_t)0x0600U)
//#define DP83822_TCSR_TDR_CH_CABLE_DEFAULT ((uint16_t)0x0000U)
//#define DP83822_TCSR_TDR_CH_CABLE_SHORTED ((uint16_t)0x0200U)
//#define DP83822_TCSR_TDR_CH_CABLE_OPEN    ((uint16_t)0x0400U)
//#define DP83822_TCSR_TDR_CH_CABLE_MATCH   ((uint16_t)0x0600U)
//#define DP83822_TCSR_TDR_CH_STATUS        ((uint16_t)0x0100U)
//#define DP83822_TCSR_TDR_CH_LENGTH        ((uint16_t)0x00FFU)
//
///* SCSIR Bit Definition */
//#define DP83822_SCSIR_AUTO_MDIX_ENABLE    ((uint16_t)0x8000U)
//#define DP83822_SCSIR_CHANNEL_SELECT      ((uint16_t)0x2000U)
//#define DP83822_SCSIR_SQE_DISABLE         ((uint16_t)0x0800U)
//#define DP83822_SCSIR_XPOLALITY           ((uint16_t)0x0010U)
//
///* CLR Bit Definition */
//#define DP83822_CLR_CABLE_LENGTH          ((uint16_t)0xF000U)
//
///* IMR / ISFR Bit Definition */
//#define DP83822_INT_8       ((uint16_t)0x0100U)
//#define DP83822_INT_7       ((uint16_t)0x0080U)
//#define DP83822_INT_6       ((uint16_t)0x0040U)
//#define DP83822_INT_5       ((uint16_t)0x0020U)
//#define DP83822_INT_4       ((uint16_t)0x0010U)
//#define DP83822_INT_3       ((uint16_t)0x0008U)
//#define DP83822_INT_2       ((uint16_t)0x0004U)
//#define DP83822_INT_1       ((uint16_t)0x0002U)
//
//#define DP83822_PHYSTS                0x0010U     /* PHY Status Register */
//#define DP83822_PHYSTS_PHY_ADDR_MASK  0x001FU     /* PHY Address Mask */
//
//#define DP83822_PHYSCR                0x0011U     /* PHY Special Control/Status Register */
//
//#define DP83822_MISR1                 0x0012U     /* MII Interrupt Status Register 1 */
//#define DP83822_MISR1_LINK_STAT_CHG   0x0020U     /* Link Status Change */
//
//#define DP83822_MISR2                 0x0013U     /* MII Interrupt Status Register 2 */
//
//#define DP83822_IMR                   0x0014U     /* Interrupt Mask Register */
//#define DP83822_IMR_LINK_STAT_CHG_EN  0x0020U     /* Link Status Change Interrupt Enable */
//
//#define DP83822_PHYCR                 0x0019U     /* PHY Control Register */
//
///* PHYSCSR Bit Definition */
#define DP83822_PHYSTS_AUTONEGO_DONE 0x0010U  /* bit 4 */
#define DP83822_PHYSTS_DUPLEX_MASK   0x0004U  /* bit 2 */
#define DP83822_PHYSTS_SPEED_MASK    0x0002U  /* bit 1 */
//#define DP83822_PHYSTS_LINK_STATUS   0x0001U  /* bit 0 */
//
//
//#define DP83822_PHYSCSR_10BT_HD          ((uint16_t)0x0004U)
//#define DP83822_PHYSCSR_10BT_FD          ((uint16_t)0x0014U)
//#define DP83822_PHYSCSR_100BTX_HD        ((uint16_t)0x0008U)
//#define DP83822_PHYSCSR_100BTX_FD        ((uint16_t)0x0018U)
//
///* Status codes */
#define  DP83822_STATUS_READ_ERROR            ((int32_t)-5)
#define  DP83822_STATUS_WRITE_ERROR           ((int32_t)-4)
#define  DP83822_STATUS_ADDRESS_ERROR         ((int32_t)-3)
#define  DP83822_STATUS_RESET_TIMEOUT         ((int32_t)-2)
#define  DP83822_STATUS_ERROR                 ((int32_t)-1)
#define  DP83822_STATUS_OK                    ((int32_t) 0)
#define  DP83822_STATUS_LINK_DOWN             ((int32_t) 1)
#define  DP83822_STATUS_100MBITS_FULLDUPLEX   ((int32_t) 2)
#define  DP83822_STATUS_100MBITS_HALFDUPLEX   ((int32_t) 3)
#define  DP83822_STATUS_10MBITS_FULLDUPLEX    ((int32_t) 4)
#define  DP83822_STATUS_10MBITS_HALFDUPLEX    ((int32_t) 5)
#define  DP83822_STATUS_AUTONEGO_NOTDONE      ((int32_t) 6)
//
///* Interrupt flags */
//#define  DP83822_WOL_IT                        DP83822_INT_8
//#define  DP83822_ENERGYON_IT                   DP83822_INT_7
//#define  DP83822_AUTONEGO_COMPLETE_IT          DP83822_INT_6
//#define  DP83822_REMOTE_FAULT_IT               DP83822_INT_5
//#define  DP83822_LINK_DOWN_IT                  DP83822_INT_4
//#define  DP83822_AUTONEGO_LP_ACK_IT            DP83822_INT_3
//#define  DP83822_PARALLEL_DETECTION_FAULT_IT   DP83822_INT_2
//#define  DP83822_AUTONEGO_PAGE_RECEIVED_IT     DP83822_INT_1
//
//#define DP83822_TIMEOUT_VALUE ((uint32_t)2000) /*!< Timeout for polling loops in ms */

/* Exported types ------------------------------------------------------------*/
typedef int32_t  (*dp83822_Init_Func)     (void);
typedef int32_t  (*dp83822_DeInit_Func)   (void);
typedef int32_t  (*dp83822_ReadReg_Func)  (uint32_t, uint32_t, uint32_t *);
typedef int32_t  (*dp83822_WriteReg_Func) (uint32_t, uint32_t, uint32_t);
typedef int32_t  (*dp83822_GetTick_Func)  (void);

typedef struct 
{                   
  dp83822_Init_Func      Init;
  dp83822_DeInit_Func    DeInit;
  dp83822_WriteReg_Func  WriteReg;
  dp83822_ReadReg_Func   ReadReg;
  dp83822_GetTick_Func   GetTick;
} dp83822_IOCtx_t;

typedef struct 
{
  uint32_t            DevAddr;
  uint32_t            Is_Initialized;
  dp83822_IOCtx_t     IO;
  void               *pData;
} dp83822_Object_t;

/* Exported functions --------------------------------------------------------*/
int32_t DP83822_RegisterBusIO(dp83822_Object_t *pObj, dp83822_IOCtx_t *ioctx);
int32_t DP83822_Init(dp83822_Object_t *pObj);
int32_t DP83822_DeInit(dp83822_Object_t *pObj);
int32_t DP83822_DisablePowerDownMode(dp83822_Object_t *pObj);
int32_t DP83822_EnablePowerDownMode(dp83822_Object_t *pObj);
int32_t DP83822_StartAutoNego(dp83822_Object_t *pObj);
int32_t DP83822_GetLinkState(dp83822_Object_t *pObj);
int32_t DP83822_SetLinkState(dp83822_Object_t *pObj, uint32_t LinkState);
int32_t DP83822_EnableLoopbackMode(dp83822_Object_t *pObj);
int32_t DP83822_DisableLoopbackMode(dp83822_Object_t *pObj);
int32_t DP83822_EnableIT(dp83822_Object_t *pObj, uint32_t Interrupt);
int32_t DP83822_DisableIT(dp83822_Object_t *pObj, uint32_t Interrupt);
int32_t DP83822_ClearIT(dp83822_Object_t *pObj, uint32_t Interrupt);
int32_t DP83822_GetITStatus(dp83822_Object_t *pObj, uint32_t Interrupt);

#ifdef __cplusplus
}
#endif

#endif /* DP83822_H */
