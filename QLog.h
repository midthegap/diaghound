/*!**************************************************************************************
 *
 * \File        QLog.h
 * \Progetto    ETCS Specific Software
 * \Ambiente    Linux
 * \Data        30/11/2022
 * \Autore      F.Pacciani
 * \Versione    01.03
 *
 * \Descrizione Modulo header per Log Msg fra Layer di comunicazioni
 *
 * \Modifica    07/04/2023 - R.Grossi - Added data type ID
 * \Modifica    18/10/2023 - R.Grossi - Added socket ID
 * \Modifica    03/04/2024 - R.Grossi - Added CPU ID
 *
 */

#ifndef QLOG_H
#define QLOG_H

  /**
 * @def MAX_MSG_LEN
 * Maximum message length
 */
#define MAX_MSG_LEN 2048
/**
 * @def MAX_ITEM
 * Queue size
 */
#define MAX_ITEM    64

 /*!**************************************************************************************
  * Data type ID definition
  */
typedef enum
{
  QLOG_EVC_MT_APP  = 1,    /**< EVC-MT Messaggi applicativi Subset-026 [ONLINE] */
  QLOG_EVC_MT_L5   = 2,    /**< EVC-MT Safety Layer Subset-037 [ONLINE] */
  QLOG_EVC_MT_L4   = 3,    /**< EVC-MT Layer 4 stack GSM     [ONLINE] */
  QLOG_EVC_MT_L3   = 4,    /**< EVC-MT Layer 3 stack GSM     [OFFLINE] */
  QLOG_EVC_MT_L2   = 5,    /**< EVC-MT Layer 2 stack GSM     [OFFLINE] */
  QLOG_EVC_MT_GSM  = 6,    /**< EVC-MT Radio Trasmission FFFIS EuroRadio A11T6001 [ONLINE] */
  QLOG_EVC_JRU_APP = 7,    /**< EVC-JRU Subset-027           [ONLINE] */
  QLOG_STB_MVB_SIG = 8,    /**< STB-MVB Signals (port SCMT, RCEC, TTT) [ONLINE] */
  QLOG_EVC_STM_APP = 9,    /**< EVC-STM Subset-058           [ONLINE] */
  QLOG_EVC_STM_STL = 10,   /**< EVC-STM Subset-056           [OFFLINE] */
  QLOG_EVC_STM_SLL = 11,   /**< EVC-STM Subset-057           [OFFLINE] */
  QLOG_EVC_MT_ALE  = 12,   /**< EVC-MT ALE                   [ONLINE] */
  QLOG_RAW         = 100,  /**< Generic RAW data             [OFFLINE] */
  QLOG_STRING      = 101,  /**< Generic String data          [OFFLINE] */
  QLOG_STB_ADC_DMI = 102,  /**< STB-ADC stato DMI e azioni ADC  [ONLINE] */
  QLOG_STB_BTM_TLG = 103,  /**< STB-BTM dati telegramma      [ONLINE] */
  QLOG_STB_BTM_STS = 104,  /**< STB-BTM stato                [ONLINE] */
  QLOG_EVC_LDV_IO  = 105,  /**< EVC-LDV IO Subset-034        [ONLINE] */
  QLOG_STB_CFG_DAT = 106,  /**< STB-CFG dati configurazione  [OFFLINE] */
  QLOG_LIB_RL      = 107,  /**< LIB-RL libreria RL           [OFFLINE] */
  QLOG_EVC_EVENT   = 108,  /**< EVC event: shutdown, error, info [OFFLINE] */
  QLOG_INFO_EVENT  = 200,  /**< INFO eventi per Data Logger  [NOT REGISTERED] */
  QLOG_INFO_DATA   = 201,  /**< INFO data per Data Logger    [NOT REGISTERED] */
} QLOG_DATA_ID;

/*!**************************************************************************************
 * Message direction definition
 */
typedef enum
{
  QLOG_NONE = 0, /**< No direction                 */
  QLOG_IND  = 1, /**< Indication direction (Get)   */
  QLOG_REQ  = 2, /**< Registration direction (Put) */
} QLOG_DIR;

/*!**************************************************************************************
 * Queue message structure definition
 */
typedef struct
{
  INT32U      ulTimestamp;         /**< Message timestamp */
  QLOG_DIR    enDir;               /**< Message Direction */
  QLOG_DATA_ID enDataID;           /**< Data type ID      */
  INT8U       ubCPU;               /**< CPU type ID       */
  INT32U      ulMsgLen;            /**< Message length    */
  INT8U       ubMsg[MAX_MSG_LEN];  /**< Message data      */
} QLOG_ITEM;

/*!**************************************************************************************
 * Queue structure definition
 */
typedef struct
{
  QLOG_DATA_ID enDataID;        /**< Data type ID                */
  /* NOTE: internal data */
  INT32U      ulWrIdx;          /**< Write index                 */
  INT32U      ulRdIdx;          /**< Read index                  */
  INT32U      ulNumItem;        /**< Number of messeges in queue */
  INT32S      slSocket;         /**< socket to send messages */
  INT32U      ulTxToGTY;
  QLOG_ITEM   stQlog[MAX_ITEM]; /**< Queue buffer                */
} QLOG_QUEUE;


/* Dichiarazione Funzioni pubbliche */
BOOLEAN QLog_Init(QLOG_QUEUE *pQlogInstance, QLOG_DATA_ID enQlogDataID);
BOOLEAN QLog_Put(QLOG_QUEUE* pQlogInstance, QLOG_DIR Dir, INT8U* pMsg, INT32U ulLen);
INT32U  QLog_GetNumLog(QLOG_QUEUE *pQlogInstance, INT32U *pNumLog);
BOOLEAN QLog_Get(QLOG_QUEUE *pQlogInstance, QLOG_DIR *pDir, QLOG_DATA_ID* pQlogDataID, INT8U *pMsg, INT32U *pulLen, INT32U *pTimeStamp);

#else
#error "Inclusione multipla del file QLog.h"
#endif

/* Fine del File:  QLog.h */

