/******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 ******************************************************************************
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 *****************************************************************************/

#include "attribute_type_size.hpp"
#include "matter.h"

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;

// ZCL attribute types
constexpr uint8_t ZCL_NO_DATA_ATTRIBUTE_TYPES           = 0x00;
constexpr uint8_t ZCL_BOOLEAN_ATTRIBUTE_TYPES           = 0x10;
constexpr uint8_t ZCL_BITMAP8_ATTRIBUTE_TYPES           = 0x18;
constexpr uint8_t ZCL_BITMAP16_ATTRIBUTE_TYPES          = 0x19;
constexpr uint8_t ZCL_BITMAP24_ATTRIBUTE_TYPES          = 0x1A;
constexpr uint8_t ZCL_BITMAP32_ATTRIBUTE_TYPES          = 0x1B;
constexpr uint8_t ZCL_BITMAP64_ATTRIBUTE_TYPES          = 0x1F;
constexpr uint8_t ZCL_INT8U_ATTRIBUTE_TYPES             = 0x20;
constexpr uint8_t ZCL_INT16U_ATTRIBUTE_TYPES            = 0x21;
constexpr uint8_t ZCL_INT24U_ATTRIBUTE_TYPES            = 0x22;
constexpr uint8_t ZCL_INT32U_ATTRIBUTE_TYPES            = 0x23;
constexpr uint8_t ZCL_INT40U_ATTRIBUTE_TYPES            = 0x24;
constexpr uint8_t ZCL_INT48U_ATTRIBUTE_TYPES            = 0x25;
constexpr uint8_t ZCL_INT56U_ATTRIBUTE_TYPES            = 0x26;
constexpr uint8_t ZCL_INT64U_ATTRIBUTE_TYPES            = 0x27;
constexpr uint8_t ZCL_INT8S_ATTRIBUTE_TYPES             = 0x28;
constexpr uint8_t ZCL_INT16S_ATTRIBUTE_TYPES            = 0x29;
constexpr uint8_t ZCL_INT24S_ATTRIBUTE_TYPES            = 0x2A;
constexpr uint8_t ZCL_INT32S_ATTRIBUTE_TYPES            = 0x2B;
constexpr uint8_t ZCL_INT40S_ATTRIBUTE_TYPES            = 0x2C;
constexpr uint8_t ZCL_INT48S_ATTRIBUTE_TYPES            = 0x2D;
constexpr uint8_t ZCL_INT56S_ATTRIBUTE_TYPES            = 0x2E;
constexpr uint8_t ZCL_INT64S_ATTRIBUTE_TYPES            = 0x2F;
constexpr uint8_t ZCL_ENUM8_ATTRIBUTE_TYPES             = 0x30;
constexpr uint8_t ZCL_ENUM16_ATTRIBUTE_TYPES            = 0x31;
constexpr uint8_t ZCL_SINGLE_ATTRIBUTE_TYPES            = 0x39;
constexpr uint8_t ZCL_DOUBLE_ATTRIBUTE_TYPES            = 0x3A;
constexpr uint8_t ZCL_OCTET_STRING_ATTRIBUTE_TYPES      = 0x41;
constexpr uint8_t ZCL_CHAR_STRING_ATTRIBUTE_TYPES       = 0x42;
constexpr uint8_t ZCL_LONG_OCTET_STRING_ATTRIBUTE_TYPES = 0x43;
constexpr uint8_t ZCL_LONG_CHAR_STRING_ATTRIBUTE_TYPES  = 0x44;
constexpr uint8_t ZCL_ARRAY_ATTRIBUTE_TYPES             = 0x48;
constexpr uint8_t ZCL_STRUCT_ATTRIBUTE_TYPES            = 0x4C;
constexpr uint8_t ZCL_TOD_ATTRIBUTE_TYPES               = 0xE0;
constexpr uint8_t ZCL_DATE_ATTRIBUTE_TYPES              = 0xE1;
constexpr uint8_t ZCL_UTC_ATTRIBUTE_TYPES               = 0xE2;
constexpr uint8_t ZCL_EPOCH_US_ATTRIBUTE_TYPES          = 0xE3;
constexpr uint8_t ZCL_EPOCH_S_ATTRIBUTE_TYPES           = 0xE4;
constexpr uint8_t ZCL_SYSTIME_US_ATTRIBUTE_TYPES        = 0xE5;
constexpr uint8_t ZCL_PERCENT_ATTRIBUTE_TYPES           = 0xE6;
constexpr uint8_t ZCL_PERCENT100THS_ATTRIBUTE_TYPES     = 0xE7;
constexpr uint8_t ZCL_CLUSTER_ID_ATTRIBUTE_TYPES        = 0xE8;
constexpr uint8_t ZCL_ATTRIB_ID_ATTRIBUTE_TYPES         = 0xE9;
constexpr uint8_t ZCL_FIELD_ID_ATTRIBUTE_TYPES          = 0xEA;
constexpr uint8_t ZCL_EVENT_ID_ATTRIBUTE_TYPES          = 0xEB;
constexpr uint8_t ZCL_COMMAND_ID_ATTRIBUTE_TYPES        = 0xEC;
constexpr uint8_t ZCL_ACTION_ID_ATTRIBUTE_TYPES         = 0xED;
constexpr uint8_t ZCL_TRANS_ID_ATTRIBUTE_TYPES          = 0xEF;
constexpr uint8_t ZCL_NODE_ID_ATTRIBUTE_TYPES           = 0xF0;
constexpr uint8_t ZCL_VENDOR_ID_ATTRIBUTE_TYPES         = 0xF1;
constexpr uint8_t ZCL_DEVTYPE_ID_ATTRIBUTE_TYPES        = 0xF2;
constexpr uint8_t ZCL_FABRIC_ID_ATTRIBUTE_TYPES         = 0xF3;
constexpr uint8_t ZCL_GROUP_ID_ATTRIBUTE_TYPES          = 0xF4;
constexpr uint8_t ZCL_STATUS_ATTRIBUTE_TYPES            = 0xF5;
constexpr uint8_t ZCL_DATA_VER_ATTRIBUTE_TYPES          = 0xF6;
constexpr uint8_t ZCL_EVENT_NO_ATTRIBUTE_TYPES          = 0xF7;
constexpr uint8_t ZCL_ENDPOINT_NO_ATTRIBUTE_TYPES       = 0xF8;
constexpr uint8_t ZCL_FABRIC_IDX_ATTRIBUTE_TYPES        = 0xF9;
constexpr uint8_t ZCL_IPADR_ATTRIBUTE_TYPES             = 0xFA;
constexpr uint8_t ZCL_IPV4ADR_ATTRIBUTE_TYPES           = 0xFB;
constexpr uint8_t ZCL_IPV6ADR_ATTRIBUTE_TYPES           = 0xFC;
constexpr uint8_t ZCL_IPV6PRE_ATTRIBUTE_TYPES           = 0xFD;
constexpr uint8_t ZCL_HWADR_ATTRIBUTE_TYPES             = 0xFE;
constexpr uint8_t ZCL_UNKNOWN_ATTRIBUTE_TYPES           = 0xFF;

// ZCL attribute sizes
constexpr uint8_t ZCL_BOOLEAN_ATTRIBUTE_TYPES_SIZE       = 1;
constexpr uint8_t ZCL_BITMAP8_ATTRIBUTE_TYPES_SIZE       = 1;
constexpr uint8_t ZCL_BITMAP16_ATTRIBUTE_TYPES_SIZE      = 2;
constexpr uint8_t ZCL_BITMAP24_ATTRIBUTE_TYPES_SIZE      = 3;
constexpr uint8_t ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE      = 4;
constexpr uint8_t ZCL_BITMAP64_ATTRIBUTE_TYPES_SIZE      = 8;
constexpr uint8_t ZCL_INT8U_ATTRIBUTE_TYPES_SIZE         = 1;
constexpr uint8_t ZCL_INT16U_ATTRIBUTE_TYPES_SIZE        = 2;
constexpr uint8_t ZCL_INT24U_ATTRIBUTE_TYPES_SIZE        = 3;
constexpr uint8_t ZCL_INT32U_ATTRIBUTE_TYPES_SIZE        = 4;
constexpr uint8_t ZCL_INT40U_ATTRIBUTE_TYPES_SIZE        = 5;
constexpr uint8_t ZCL_INT48U_ATTRIBUTE_TYPES_SIZE        = 6;
constexpr uint8_t ZCL_INT56U_ATTRIBUTE_TYPES_SIZE        = 7;
constexpr uint8_t ZCL_INT64U_ATTRIBUTE_TYPES_SIZE        = 8;
constexpr uint8_t ZCL_INT8S_ATTRIBUTE_TYPES_SIZE         = 1;
constexpr uint8_t ZCL_INT16S_ATTRIBUTE_TYPES_SIZE        = 2;
constexpr uint8_t ZCL_INT24S_ATTRIBUTE_TYPES_SIZE        = 3;
constexpr uint8_t ZCL_INT32S_ATTRIBUTE_TYPES_SIZE        = 4;
constexpr uint8_t ZCL_INT40S_ATTRIBUTE_TYPES_SIZE        = 5;
constexpr uint8_t ZCL_INT48S_ATTRIBUTE_TYPES_SIZE        = 6;
constexpr uint8_t ZCL_INT56S_ATTRIBUTE_TYPES_SIZE        = 7;
constexpr uint8_t ZCL_INT64S_ATTRIBUTE_TYPES_SIZE        = 8;
constexpr uint8_t ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE         = 1;
constexpr uint8_t ZCL_ENUM16_ATTRIBUTE_TYPES_SIZE        = 2;
constexpr uint8_t ZCL_SINGLE_ATTRIBUTE_TYPES_SIZE        = 4;
constexpr uint8_t ZCL_DOUBLE_ATTRIBUTE_TYPES_SIZE        = 8;
constexpr uint8_t ZCL_TOD_ATTRIBUTE_TYPES_SIZE           = 4;
constexpr uint8_t ZCL_DATE_ATTRIBUTE_TYPES_SIZE          = 4;
constexpr uint8_t ZCL_UTC_ATTRIBUTE_TYPES_SIZE           = 4;
constexpr uint8_t ZCL_EPOCH_US_ATTRIBUTE_TYPES_SIZE      = 8;
constexpr uint8_t ZCL_EPOCH_S_ATTRIBUTE_TYPES_SIZE       = 4;
constexpr uint8_t ZCL_SYSTIME_US_ATTRIBUTE_TYPES_SIZE    = 8;
constexpr uint8_t ZCL_PERCENT_ATTRIBUTE_TYPES_SIZE       = 1;
constexpr uint8_t ZCL_PERCENT100THS_ATTRIBUTE_TYPES_SIZE = 2;
constexpr uint8_t ZCL_CLUSTER_ID_ATTRIBUTE_TYPES_SIZE    = 4;
constexpr uint8_t ZCL_ATTRIB_ID_ATTRIBUTE_TYPES_SIZE     = 4;
constexpr uint8_t ZCL_FIELD_ID_ATTRIBUTE_TYPES_SIZE      = 4;
constexpr uint8_t ZCL_EVENT_ID_ATTRIBUTE_TYPES_SIZE      = 4;
constexpr uint8_t ZCL_COMMAND_ID_ATTRIBUTE_TYPES_SIZE    = 4;
constexpr uint8_t ZCL_ACTION_ID_ATTRIBUTE_TYPES_SIZE     = 1;
constexpr uint8_t ZCL_TRANS_ID_ATTRIBUTE_TYPES_SIZE      = 4;
constexpr uint8_t ZCL_NODE_ID_ATTRIBUTE_TYPES_SIZE       = 8;
constexpr uint8_t ZCL_VENDOR_ID_ATTRIBUTE_TYPES_SIZE     = 2;
constexpr uint8_t ZCL_DEVTYPE_ID_ATTRIBUTE_TYPES_SIZE    = 4;
constexpr uint8_t ZCL_FABRIC_ID_ATTRIBUTE_TYPES_SIZE     = 8;
constexpr uint8_t ZCL_GROUP_ID_ATTRIBUTE_TYPES_SIZE      = 2;
constexpr uint8_t ZCL_STATUS_ATTRIBUTE_TYPES_SIZE        = 2;
constexpr uint8_t ZCL_DATA_VER_ATTRIBUTE_TYPES_SIZE      = 4;
constexpr uint8_t ZCL_EVENT_NO_ATTRIBUTE_TYPES_SIZE      = 8;
constexpr uint8_t ZCL_ENDPOINT_NO_ATTRIBUTE_TYPES_SIZE   = 2;
constexpr uint8_t ZCL_FABRIC_IDX_ATTRIBUTE_TYPES_SIZE    = 1;
constexpr uint8_t ZCL_IPV4ADR_ATTRIBUTE_TYPES_SIZE       = 4;
constexpr uint8_t ZCL_IPV6ADR_ATTRIBUTE_TYPES_SIZE       = 16;

// Setting the attribute tpe size which is not defined in 'chip-type.xml'
constexpr uint8_t ZCL_NO_DATA_ATTRIBUTE_TYPES_SIZE           = 0;
constexpr uint8_t ZCL_OCTET_STRING_ATTRIBUTE_TYPES_SIZE      = 32;
constexpr uint8_t ZCL_CHAR_STRING_ATTRIBUTE_TYPES_SIZE       = 32;
constexpr uint8_t ZCL_LONG_OCTET_STRING_ATTRIBUTE_TYPES_SIZE = 32;
constexpr uint8_t ZCL_LONG_CHAR_STRING_ATTRIBUTE_TYPES_SIZE  = 32;
constexpr uint8_t ZCL_STRUCT_ATTRIBUTE_TYPES_SIZE            = 254;
constexpr uint8_t ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE             = 254;

constexpr uint8_t ZCL_IDENTIFY_EFFECT_IDENTIFIER_ATTRIBUTE_TYPES      = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_IDENTIFY_EFFECT_IDENTIFIER_ATTRIBUTE_TYPES_SIZE = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_IDENTIFY_EFFECT_VARIANT_ATTRIBUTE_TYPES         = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_IDENTIFY_EFFECT_VARIANT_ATTRIBUTE_TYPES_SIZE    = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_IDENTIFY_IDENTIFY_TYPE_ATTRIBUTE_TYPES          = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_IDENTIFY_IDENTIFY_TYPE_ATTRIBUTE_TYPES_SIZE     = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_ON_OFF_CONTROL_ATTRIBUTE_TYPES      = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_ON_OFF_CONTROL_ATTRIBUTE_TYPES_SIZE = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_ON_OFF_FEATURE_ATTRIBUTE_TYPES      = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_ON_OFF_FEATURE_ATTRIBUTE_TYPES_SIZE = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_SCENE_FEATURES_ATTRIBUTE_TYPES      = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_SCENE_FEATURES_ATTRIBUTE_TYPES_SIZE = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_ON_OFF_DELAYED_ALL_OFF_EFFECT_VARIANT_ATTRIBUTE_TYPES      = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_ON_OFF_DELAYED_ALL_OFF_EFFECT_VARIANT_ATTRIBUTE_TYPES_SIZE = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_ON_OFF_DYING_LIGHT_EFFECT_VARIANT_ATTRIBUTE_TYPES          = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_ON_OFF_DYING_LIGHT_EFFECT_VARIANT_ATTRIBUTE_TYPES_SIZE     = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_ON_OFF_EFFECT_IDENTIFIER_ATTRIBUTE_TYPES                   = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_ON_OFF_EFFECT_IDENTIFIER_ATTRIBUTE_TYPES_SIZE              = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_ON_OFF_START_UP_ON_OFF_ATTRIBUTE_TYPES                     = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_ON_OFF_START_UP_ON_OFF_ATTRIBUTE_TYPES_SIZE                = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_LEVEL_CONTROL_FEATURE_ATTRIBUTE_TYPES      = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_LEVEL_CONTROL_FEATURE_ATTRIBUTE_TYPES_SIZE = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_LEVEL_CONTROL_OPTIONS_ATTRIBUTE_TYPES      = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_LEVEL_CONTROL_OPTIONS_ATTRIBUTE_TYPES_SIZE = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_MOVE_MODE_ATTRIBUTE_TYPES      = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_MOVE_MODE_ATTRIBUTE_TYPES_SIZE = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_STEP_MODE_ATTRIBUTE_TYPES      = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_STEP_MODE_ATTRIBUTE_TYPES_SIZE = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_DL_CREDENTIAL_RULE_MASK_ATTRIBUTE_TYPES                = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_CREDENTIAL_RULE_MASK_ATTRIBUTE_TYPES_SIZE           = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_CREDENTIAL_RULES_SUPPORT_ATTRIBUTE_TYPES            = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_CREDENTIAL_RULES_SUPPORT_ATTRIBUTE_TYPES_SIZE       = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_DAYS_MASK_MAP_ATTRIBUTE_TYPES                       = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_DAYS_MASK_MAP_ATTRIBUTE_TYPES_SIZE                  = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_DEFAULT_CONFIGURATION_REGISTER_ATTRIBUTE_TYPES      = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_DEFAULT_CONFIGURATION_REGISTER_ATTRIBUTE_TYPES_SIZE = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_KEYPAD_OPERATION_EVENT_MASK_ATTRIBUTE_TYPES         = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_KEYPAD_OPERATION_EVENT_MASK_ATTRIBUTE_TYPES_SIZE    = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_KEYPAD_PROGRAMMING_EVENT_MASK_ATTRIBUTE_TYPES       = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_KEYPAD_PROGRAMMING_EVENT_MASK_ATTRIBUTE_TYPES_SIZE  = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_LOCAL_PROGRAMMING_FEATURES_ATTRIBUTE_TYPES          = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_LOCAL_PROGRAMMING_FEATURES_ATTRIBUTE_TYPES_SIZE     = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_MANUAL_OPERATION_EVENT_MASK_ATTRIBUTE_TYPES         = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_MANUAL_OPERATION_EVENT_MASK_ATTRIBUTE_TYPES_SIZE    = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_RFID_OPERATION_EVENT_MASK_ATTRIBUTE_TYPES           = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_RFID_OPERATION_EVENT_MASK_ATTRIBUTE_TYPES_SIZE      = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_RFID_PROGRAMMING_EVENT_MASK_ATTRIBUTE_TYPES         = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_RFID_PROGRAMMING_EVENT_MASK_ATTRIBUTE_TYPES_SIZE    = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_REMOTE_OPERATION_EVENT_MASK_ATTRIBUTE_TYPES         = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_REMOTE_OPERATION_EVENT_MASK_ATTRIBUTE_TYPES_SIZE    = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_REMOTE_PROGRAMMING_EVENT_MASK_ATTRIBUTE_TYPES       = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_REMOTE_PROGRAMMING_EVENT_MASK_ATTRIBUTE_TYPES_SIZE  = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_SUPPORTED_OPERATING_MODES_ATTRIBUTE_TYPES           = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_SUPPORTED_OPERATING_MODES_ATTRIBUTE_TYPES_SIZE      = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DOOR_LOCK_DAY_OF_WEEK_ATTRIBUTE_TYPES                  = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DOOR_LOCK_DAY_OF_WEEK_ATTRIBUTE_TYPES_SIZE             = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DOOR_LOCK_FEATURE_ATTRIBUTE_TYPES                      = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DOOR_LOCK_FEATURE_ATTRIBUTE_TYPES_SIZE                 = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_DL_ALARM_CODE_ATTRIBUTE_TYPES                         = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_ALARM_CODE_ATTRIBUTE_TYPES_SIZE                    = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_CREDENTIAL_RULE_ATTRIBUTE_TYPES                    = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_CREDENTIAL_RULE_ATTRIBUTE_TYPES_SIZE               = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_CREDENTIAL_TYPE_ATTRIBUTE_TYPES                    = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_CREDENTIAL_TYPE_ATTRIBUTE_TYPES_SIZE               = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_DATA_OPERATION_TYPE_ATTRIBUTE_TYPES                = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_DATA_OPERATION_TYPE_ATTRIBUTE_TYPES_SIZE           = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_DOOR_STATE_ATTRIBUTE_TYPES                         = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_DOOR_STATE_ATTRIBUTE_TYPES_SIZE                    = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_LOCK_DATA_TYPE_ATTRIBUTE_TYPES                     = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_LOCK_DATA_TYPE_ATTRIBUTE_TYPES_SIZE                = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_LOCK_OPERATION_TYPE_ATTRIBUTE_TYPES                = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_LOCK_OPERATION_TYPE_ATTRIBUTE_TYPES_SIZE           = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_LOCK_STATE_ATTRIBUTE_TYPES                         = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_LOCK_STATE_ATTRIBUTE_TYPES_SIZE                    = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_LOCK_TYPE_ATTRIBUTE_TYPES                          = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_LOCK_TYPE_ATTRIBUTE_TYPES_SIZE                     = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_OPERATING_MODE_ATTRIBUTE_TYPES                     = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_OPERATING_MODE_ATTRIBUTE_TYPES_SIZE                = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_OPERATION_ERROR_ATTRIBUTE_TYPES                    = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_OPERATION_ERROR_ATTRIBUTE_TYPES_SIZE               = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_OPERATION_SOURCE_ATTRIBUTE_TYPES                   = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_OPERATION_SOURCE_ATTRIBUTE_TYPES_SIZE              = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_STATUS_ATTRIBUTE_TYPES                             = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_STATUS_ATTRIBUTE_TYPES_SIZE                        = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_USER_STATUS_ATTRIBUTE_TYPES                        = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_USER_STATUS_ATTRIBUTE_TYPES_SIZE                   = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DL_USER_TYPE_ATTRIBUTE_TYPES                          = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_USER_TYPE_ATTRIBUTE_TYPES_SIZE                     = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_ATTRIBUTE_TYPES        = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_ATTRIBUTE_TYPES_SIZE   = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DOOR_LOCK_PROGRAMMING_EVENT_CODE_ATTRIBUTE_TYPES      = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DOOR_LOCK_PROGRAMMING_EVENT_CODE_ATTRIBUTE_TYPES_SIZE = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DOOR_LOCK_SET_PIN_OR_ID_STATUS_ATTRIBUTE_TYPES        = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DOOR_LOCK_SET_PIN_OR_ID_STATUS_ATTRIBUTE_TYPES_SIZE   = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DOOR_LOCK_USER_STATUS_ATTRIBUTE_TYPES                 = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DOOR_LOCK_USER_STATUS_ATTRIBUTE_TYPES_SIZE            = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_DOOR_LOCK_USER_TYPE_ATTRIBUTE_TYPES                   = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DOOR_LOCK_USER_TYPE_ATTRIBUTE_TYPES_SIZE              = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_DL_CREDENTIAL_ATTRIBUTE_TYPES      = ZCL_STRUCT_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DL_CREDENTIAL_ATTRIBUTE_TYPES_SIZE = ZCL_STRUCT_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_DAY_OF_WEEK_ATTRIBUTE_TYPES             = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_DAY_OF_WEEK_ATTRIBUTE_TYPES_SIZE        = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_MODE_FOR_SEQUENCE_ATTRIBUTE_TYPES       = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_MODE_FOR_SEQUENCE_ATTRIBUTE_TYPES_SIZE  = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_THERMOSTAT_FEATURE_ATTRIBUTE_TYPES      = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_THERMOSTAT_FEATURE_ATTRIBUTE_TYPES_SIZE = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_SETPOINT_ADJUST_MODE_ATTRIBUTE_TYPES             = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_SETPOINT_ADJUST_MODE_ATTRIBUTE_TYPES_SIZE        = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_THERMOSTAT_CONTROL_SEQUENCE_ATTRIBUTE_TYPES      = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_THERMOSTAT_CONTROL_SEQUENCE_ATTRIBUTE_TYPES_SIZE = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_THERMOSTAT_RUNNING_MODE_ATTRIBUTE_TYPES          = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_THERMOSTAT_RUNNING_MODE_ATTRIBUTE_TYPES_SIZE     = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_THERMOSTAT_SYSTEM_MODE_ATTRIBUTE_TYPES           = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_THERMOSTAT_SYSTEM_MODE_ATTRIBUTE_TYPES_SIZE      = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_THERMOSTAT_SCHEDULE_TRANSITION_ATTRIBUTE_TYPES      = ZCL_STRUCT_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_THERMOSTAT_SCHEDULE_TRANSITION_ATTRIBUTE_TYPES_SIZE = ZCL_STRUCT_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_FAN_CONTROL_FEATURE_ATTRIBUTE_TYPES      = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_FAN_CONTROL_FEATURE_ATTRIBUTE_TYPES_SIZE = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_ROCK_SUPPORT_MASK_ATTRIBUTE_TYPES        = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_ROCK_SUPPORT_MASK_ATTRIBUTE_TYPES_SIZE   = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_WIND_SETTING_MASK_ATTRIBUTE_TYPES        = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_WIND_SETTING_MASK_ATTRIBUTE_TYPES_SIZE   = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_WIND_SUPPORT_MASK_ATTRIBUTE_TYPES        = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_WIND_SUPPORT_MASK_ATTRIBUTE_TYPES_SIZE   = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_FAN_MODE_SEQUENCE_TYPE_ATTRIBUTE_TYPES      = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_FAN_MODE_SEQUENCE_TYPE_ATTRIBUTE_TYPES_SIZE = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_FAN_MODE_TYPE_ATTRIBUTE_TYPES               = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_FAN_MODE_TYPE_ATTRIBUTE_TYPES_SIZE          = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_COLOR_CAPABILITIES_ATTRIBUTE_TYPES           = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_COLOR_CAPABILITIES_ATTRIBUTE_TYPES_SIZE      = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_COLOR_CONTROL_FEATURE_ATTRIBUTE_TYPES        = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_COLOR_CONTROL_FEATURE_ATTRIBUTE_TYPES_SIZE   = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_COLOR_LOOP_UPDATE_FLAGS_ATTRIBUTE_TYPES      = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_COLOR_LOOP_UPDATE_FLAGS_ATTRIBUTE_TYPES_SIZE = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_COLOR_LOOP_ACTION_ATTRIBUTE_TYPES         = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_COLOR_LOOP_ACTION_ATTRIBUTE_TYPES_SIZE    = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_COLOR_LOOP_DIRECTION_ATTRIBUTE_TYPES      = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_COLOR_LOOP_DIRECTION_ATTRIBUTE_TYPES_SIZE = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_COLOR_MODE_ATTRIBUTE_TYPES                = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_COLOR_MODE_ATTRIBUTE_TYPES_SIZE           = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_HUE_DIRECTION_ATTRIBUTE_TYPES             = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_HUE_DIRECTION_ATTRIBUTE_TYPES_SIZE        = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_HUE_MOVE_MODE_ATTRIBUTE_TYPES             = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_HUE_MOVE_MODE_ATTRIBUTE_TYPES_SIZE        = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_HUE_STEP_MODE_ATTRIBUTE_TYPES             = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_HUE_STEP_MODE_ATTRIBUTE_TYPES_SIZE        = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_SATURATION_MOVE_MODE_ATTRIBUTE_TYPES      = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_SATURATION_MOVE_MODE_ATTRIBUTE_TYPES_SIZE = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;
constexpr uint8_t ZCL_SATURATION_STEP_MODE_ATTRIBUTE_TYPES      = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_SATURATION_STEP_MODE_ATTRIBUTE_TYPES_SIZE = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_LIGHT_SENSOR_TYPE_ATTRIBUTE_TYPES      = ZCL_ENUM8_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_LIGHT_SENSOR_TYPE_ATTRIBUTE_TYPES_SIZE = ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE;

constexpr uint8_t ZCL_PRESSURE_FEATURE_ATTRIBUTE_TYPES      = ZCL_BITMAP32_ATTRIBUTE_TYPES;
constexpr uint8_t ZCL_PRESSURE_FEATURE_ATTRIBUTE_TYPES_SIZE = ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE;

attr_type_size get_attribute_type_size(uint16_t cluster_id, uint16_t attribute_id)
{
    switch (cluster_id)
    {
    case chip::app::Clusters::Identify::Id: {
        switch (attribute_id)
        {
        case Identify::Attributes::IdentifyTime::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case Identify::Attributes::IdentifyType::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case Identify::Attributes::GeneratedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case Identify::Attributes::AcceptedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case Identify::Attributes::AttributeList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case Identify::Attributes::FeatureMap::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case Identify::Attributes::ClusterRevision::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        default:
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
        }
    }
    case chip::app::Clusters::OnOff::Id: {
        switch (attribute_id)
        {
        case OnOff::Attributes::OnOff::Id: {
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, ZCL_BOOLEAN_ATTRIBUTE_TYPES_SIZE };
        }
        case OnOff::Attributes::GlobalSceneControl::Id: {
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, ZCL_BOOLEAN_ATTRIBUTE_TYPES_SIZE };
        }
        case OnOff::Attributes::OnTime::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case OnOff::Attributes::OffWaitTime::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case OnOff::Attributes::StartUpOnOff::Id: {
            return { ZCL_ON_OFF_START_UP_ON_OFF_ATTRIBUTE_TYPES, ZCL_ON_OFF_START_UP_ON_OFF_ATTRIBUTE_TYPES_SIZE };
        }
        case OnOff::Attributes::GeneratedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case OnOff::Attributes::AcceptedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case OnOff::Attributes::AttributeList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case OnOff::Attributes::FeatureMap::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case OnOff::Attributes::ClusterRevision::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        default:
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
        }
    }
    case chip::app::Clusters::LevelControl::Id: {
        switch (attribute_id)
        {
        case LevelControl::Attributes::CurrentLevel::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::RemainingTime::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::MinLevel::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::MaxLevel::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::CurrentFrequency::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::MinFrequency::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::MaxFrequency::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::Options::Id: {
            return { ZCL_LEVEL_CONTROL_OPTIONS_ATTRIBUTE_TYPES, ZCL_LEVEL_CONTROL_OPTIONS_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::OnOffTransitionTime::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::OnLevel::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::OnTransitionTime::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::OffTransitionTime::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::DefaultMoveRate::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::StartUpCurrentLevel::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::GeneratedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::AcceptedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::AttributeList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::FeatureMap::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case LevelControl::Attributes::ClusterRevision::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        default:
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
        }
    }
    case chip::app::Clusters::DoorLock::Id: {
        switch (attribute_id)
        {
        case DoorLock::Attributes::LockState::Id: {
            return { ZCL_DL_LOCK_STATE_ATTRIBUTE_TYPES, ZCL_DL_LOCK_STATE_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::LockType::Id: {
            return { ZCL_DL_LOCK_TYPE_ATTRIBUTE_TYPES, ZCL_DL_LOCK_TYPE_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::ActuatorEnabled::Id: {
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, ZCL_BOOLEAN_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::DoorState::Id: {
            return { ZCL_DL_DOOR_STATE_ATTRIBUTE_TYPES, ZCL_DL_DOOR_STATE_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::DoorOpenEvents::Id: {
            return { ZCL_INT32U_ATTRIBUTE_TYPES, ZCL_INT32U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::DoorClosedEvents::Id: {
            return { ZCL_INT32U_ATTRIBUTE_TYPES, ZCL_INT32U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::OpenPeriod::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::NumberOfTotalUsersSupported::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::NumberOfPINUsersSupported::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::NumberOfRFIDUsersSupported::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::NumberOfWeekDaySchedulesSupportedPerUser::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::NumberOfYearDaySchedulesSupportedPerUser::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::NumberOfHolidaySchedulesSupported::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::MaxPINCodeLength::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::MinPINCodeLength::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::MaxRFIDCodeLength::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::MinRFIDCodeLength::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::CredentialRulesSupport::Id: {
            return { ZCL_DL_CREDENTIAL_RULE_MASK_ATTRIBUTE_TYPES, ZCL_DL_CREDENTIAL_RULE_MASK_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::NumberOfCredentialsSupportedPerUser::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::Language::Id: {
            return { ZCL_CHAR_STRING_ATTRIBUTE_TYPES, ZCL_CHAR_STRING_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::LEDSettings::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::AutoRelockTime::Id: {
            return { ZCL_INT32U_ATTRIBUTE_TYPES, ZCL_INT32U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::SoundVolume::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::OperatingMode::Id: {
            return { ZCL_DL_OPERATING_MODE_ATTRIBUTE_TYPES, ZCL_DL_OPERATING_MODE_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::SupportedOperatingModes::Id: {
            return { ZCL_DL_SUPPORTED_OPERATING_MODES_ATTRIBUTE_TYPES, ZCL_DL_SUPPORTED_OPERATING_MODES_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::DefaultConfigurationRegister::Id: {
            return { ZCL_DL_DEFAULT_CONFIGURATION_REGISTER_ATTRIBUTE_TYPES,
                     ZCL_DL_DEFAULT_CONFIGURATION_REGISTER_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::EnableLocalProgramming::Id: {
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, ZCL_BOOLEAN_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::EnableOneTouchLocking::Id: {
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, ZCL_BOOLEAN_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::EnableInsideStatusLED::Id: {
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, ZCL_BOOLEAN_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::EnablePrivacyModeButton::Id: {
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, ZCL_BOOLEAN_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::LocalProgrammingFeatures::Id: {
            return { ZCL_DL_LOCAL_PROGRAMMING_FEATURES_ATTRIBUTE_TYPES, ZCL_DL_LOCAL_PROGRAMMING_FEATURES_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::WrongCodeEntryLimit::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::UserCodeTemporaryDisableTime::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::SendPINOverTheAir::Id: {
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, ZCL_BOOLEAN_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::RequirePINforRemoteOperation::Id: {
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, ZCL_BOOLEAN_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::ExpiringUserTimeout::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::GeneratedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::AcceptedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::AttributeList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::FeatureMap::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case DoorLock::Attributes::ClusterRevision::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        default:
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
        }
    }
    case chip::app::Clusters::BarrierControl::Id: {
        switch (attribute_id)
        {
        case BarrierControl::Attributes::BarrierMovingState::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case BarrierControl::Attributes::BarrierSafetyStatus::Id: {
            return { ZCL_BITMAP16_ATTRIBUTE_TYPES, ZCL_BITMAP16_ATTRIBUTE_TYPES_SIZE };
        }
        case BarrierControl::Attributes::BarrierCapabilities::Id: {
            return { ZCL_BITMAP8_ATTRIBUTE_TYPES, ZCL_BITMAP8_ATTRIBUTE_TYPES_SIZE };
        }
        case BarrierControl::Attributes::BarrierOpenEvents::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case BarrierControl::Attributes::BarrierCloseEvents::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case BarrierControl::Attributes::BarrierCommandOpenEvents::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case BarrierControl::Attributes::BarrierCommandCloseEvents::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case BarrierControl::Attributes::BarrierOpenPeriod::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case BarrierControl::Attributes::BarrierClosePeriod::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case BarrierControl::Attributes::BarrierPosition::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case BarrierControl::Attributes::GeneratedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case BarrierControl::Attributes::AcceptedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case BarrierControl::Attributes::AttributeList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case BarrierControl::Attributes::FeatureMap::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case BarrierControl::Attributes::ClusterRevision::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        default:
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
        }
    }
    case chip::app::Clusters::Thermostat::Id: {
        switch (attribute_id)
        {
        case Thermostat::Attributes::LocalTemperature::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::OutdoorTemperature::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::Occupancy::Id: {
            return { ZCL_BITMAP8_ATTRIBUTE_TYPES, ZCL_BITMAP8_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::AbsMinHeatSetpointLimit::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::AbsMaxHeatSetpointLimit::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::AbsMinCoolSetpointLimit::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::AbsMaxCoolSetpointLimit::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::PICoolingDemand::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::PIHeatingDemand::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::HVACSystemTypeConfiguration::Id: {
            return { ZCL_BITMAP8_ATTRIBUTE_TYPES, ZCL_BITMAP8_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::LocalTemperatureCalibration::Id: {
            return { ZCL_INT8S_ATTRIBUTE_TYPES, ZCL_INT8S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::OccupiedCoolingSetpoint::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::OccupiedHeatingSetpoint::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::UnoccupiedCoolingSetpoint::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::UnoccupiedHeatingSetpoint::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::MinHeatSetpointLimit::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::MaxHeatSetpointLimit::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::MinCoolSetpointLimit::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::MaxCoolSetpointLimit::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::MinSetpointDeadBand::Id: {
            return { ZCL_INT8S_ATTRIBUTE_TYPES, ZCL_INT8S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::RemoteSensing::Id: {
            return { ZCL_BITMAP8_ATTRIBUTE_TYPES, ZCL_BITMAP8_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::ControlSequenceOfOperation::Id: {
            return { ZCL_THERMOSTAT_CONTROL_SEQUENCE_ATTRIBUTE_TYPES, ZCL_THERMOSTAT_CONTROL_SEQUENCE_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::SystemMode::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::ThermostatRunningMode::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::StartOfWeek::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::NumberOfWeeklyTransitions::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::NumberOfDailyTransitions::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::TemperatureSetpointHold::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::TemperatureSetpointHoldDuration::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::ThermostatProgrammingOperationMode::Id: {
            return { ZCL_BITMAP8_ATTRIBUTE_TYPES, ZCL_BITMAP8_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::ThermostatRunningState::Id: {
            return { ZCL_BITMAP16_ATTRIBUTE_TYPES, ZCL_BITMAP16_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::SetpointChangeSource::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::SetpointChangeAmount::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::SetpointChangeSourceTimestamp::Id: {
            return { ZCL_UTC_ATTRIBUTE_TYPES, ZCL_UTC_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::OccupiedSetback::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::OccupiedSetbackMin::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::OccupiedSetbackMax::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::UnoccupiedSetback::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::UnoccupiedSetbackMin::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::UnoccupiedSetbackMax::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::EmergencyHeatDelta::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::ACType::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::ACCapacity::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::ACRefrigerantType::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::ACCompressorType::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::ACErrorCode::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::ACLouverPosition::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::ACCoilTemperature::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::ACCapacityformat::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::GeneratedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::AcceptedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::AttributeList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::FeatureMap::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case Thermostat::Attributes::ClusterRevision::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        default:
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
        }
    }
    case chip::app::Clusters::FanControl::Id: {
        switch (attribute_id)
        {
        case FanControl::Attributes::FanMode::Id: {
            return { ZCL_FAN_MODE_TYPE_ATTRIBUTE_TYPES, ZCL_FAN_MODE_TYPE_ATTRIBUTE_TYPES_SIZE };
        }
        case FanControl::Attributes::FanModeSequence::Id: {
            return { ZCL_FAN_MODE_SEQUENCE_TYPE_ATTRIBUTE_TYPES, ZCL_FAN_MODE_SEQUENCE_TYPE_ATTRIBUTE_TYPES_SIZE };
        }
        case FanControl::Attributes::PercentSetting::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case FanControl::Attributes::PercentCurrent::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case FanControl::Attributes::SpeedMax::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case FanControl::Attributes::SpeedSetting::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case FanControl::Attributes::SpeedCurrent::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case FanControl::Attributes::RockSupport::Id: {
            return { ZCL_BITMAP8_ATTRIBUTE_TYPES, ZCL_BITMAP8_ATTRIBUTE_TYPES_SIZE };
        }
        case FanControl::Attributes::RockSetting::Id: {
            return { ZCL_BITMAP8_ATTRIBUTE_TYPES, ZCL_BITMAP8_ATTRIBUTE_TYPES_SIZE };
        }
        case FanControl::Attributes::WindSupport::Id: {
            return { ZCL_BITMAP8_ATTRIBUTE_TYPES, ZCL_BITMAP8_ATTRIBUTE_TYPES_SIZE };
        }
        case FanControl::Attributes::WindSetting::Id: {
            return { ZCL_BITMAP8_ATTRIBUTE_TYPES, ZCL_BITMAP8_ATTRIBUTE_TYPES_SIZE };
        }
        case FanControl::Attributes::GeneratedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case FanControl::Attributes::AcceptedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case FanControl::Attributes::AttributeList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case FanControl::Attributes::FeatureMap::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case FanControl::Attributes::ClusterRevision::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        default:
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
        }
    }
    case chip::app::Clusters::ThermostatUserInterfaceConfiguration::Id: {
        switch (attribute_id)
        {
        case ThermostatUserInterfaceConfiguration::Attributes::TemperatureDisplayMode::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case ThermostatUserInterfaceConfiguration::Attributes::KeypadLockout::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case ThermostatUserInterfaceConfiguration::Attributes::ScheduleProgrammingVisibility::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case ThermostatUserInterfaceConfiguration::Attributes::GeneratedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case ThermostatUserInterfaceConfiguration::Attributes::AcceptedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case ThermostatUserInterfaceConfiguration::Attributes::AttributeList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case ThermostatUserInterfaceConfiguration::Attributes::FeatureMap::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case ThermostatUserInterfaceConfiguration::Attributes::ClusterRevision::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        default:
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
        }
    }
    case chip::app::Clusters::ColorControl::Id: {
        switch (attribute_id)
        {
        case ColorControl::Attributes::CurrentHue::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::CurrentSaturation::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::RemainingTime::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::CurrentX::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::CurrentY::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::DriftCompensation::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::CompensationText::Id: {
            return { ZCL_CHAR_STRING_ATTRIBUTE_TYPES, ZCL_CHAR_STRING_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorTemperatureMireds::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorMode::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Options::Id: {
            return { ZCL_BITMAP8_ATTRIBUTE_TYPES, ZCL_BITMAP8_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::NumberOfPrimaries::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary1X::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary1Y::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary1Intensity::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary2X::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary2Y::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary2Intensity::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary3X::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary3Y::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary3Intensity::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary4X::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary4Y::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary4Intensity::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary5X::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary5Y::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary5Intensity::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary6X::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary6Y::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::Primary6Intensity::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::WhitePointX::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::WhitePointY::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorPointRX::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorPointRY::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorPointRIntensity::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorPointGX::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorPointGY::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorPointGIntensity::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorPointBX::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorPointBY::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorPointBIntensity::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::EnhancedCurrentHue::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::EnhancedColorMode::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorLoopActive::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorLoopDirection::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorLoopTime::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorLoopStartEnhancedHue::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorLoopStoredEnhancedHue::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorCapabilities::Id: {
            return { ZCL_BITMAP16_ATTRIBUTE_TYPES, ZCL_BITMAP16_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorTempPhysicalMinMireds::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ColorTempPhysicalMaxMireds::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::CoupleColorTempToLevelMinMireds::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::StartUpColorTemperatureMireds::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::GeneratedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::AcceptedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::AttributeList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::FeatureMap::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case ColorControl::Attributes::ClusterRevision::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        default:
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
        }
    }
    case chip::app::Clusters::IlluminanceMeasurement::Id: {
        switch (attribute_id)
        {
        case IlluminanceMeasurement::Attributes::MeasuredValue::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case IlluminanceMeasurement::Attributes::MinMeasuredValue::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case IlluminanceMeasurement::Attributes::MaxMeasuredValue::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case IlluminanceMeasurement::Attributes::Tolerance::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case IlluminanceMeasurement::Attributes::LightSensorType::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case IlluminanceMeasurement::Attributes::GeneratedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case IlluminanceMeasurement::Attributes::AcceptedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case IlluminanceMeasurement::Attributes::AttributeList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case IlluminanceMeasurement::Attributes::FeatureMap::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case IlluminanceMeasurement::Attributes::ClusterRevision::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        default:
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
        }
    }
    case chip::app::Clusters::TemperatureMeasurement::Id: {
        switch (attribute_id)
        {
        case TemperatureMeasurement::Attributes::MeasuredValue::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case TemperatureMeasurement::Attributes::MinMeasuredValue::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case TemperatureMeasurement::Attributes::MaxMeasuredValue::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case TemperatureMeasurement::Attributes::Tolerance::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case TemperatureMeasurement::Attributes::GeneratedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case TemperatureMeasurement::Attributes::AcceptedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case TemperatureMeasurement::Attributes::AttributeList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case TemperatureMeasurement::Attributes::FeatureMap::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case TemperatureMeasurement::Attributes::ClusterRevision::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        default:
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
        }
    }
    case chip::app::Clusters::PressureMeasurement::Id: {
        switch (attribute_id)
        {
        case PressureMeasurement::Attributes::MeasuredValue::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case PressureMeasurement::Attributes::MinMeasuredValue::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case PressureMeasurement::Attributes::MaxMeasuredValue::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case PressureMeasurement::Attributes::Tolerance::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case PressureMeasurement::Attributes::ScaledValue::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case PressureMeasurement::Attributes::MinScaledValue::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case PressureMeasurement::Attributes::MaxScaledValue::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case PressureMeasurement::Attributes::ScaledTolerance::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case PressureMeasurement::Attributes::Scale::Id: {
            return { ZCL_INT8S_ATTRIBUTE_TYPES, ZCL_INT8S_ATTRIBUTE_TYPES_SIZE };
        }
        case PressureMeasurement::Attributes::GeneratedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case PressureMeasurement::Attributes::AcceptedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case PressureMeasurement::Attributes::AttributeList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case PressureMeasurement::Attributes::FeatureMap::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case PressureMeasurement::Attributes::ClusterRevision::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        default:
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
        }
    }
    case chip::app::Clusters::RelativeHumidityMeasurement::Id: {
        switch (attribute_id)
        {
        case RelativeHumidityMeasurement::Attributes::MeasuredValue::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case RelativeHumidityMeasurement::Attributes::MinMeasuredValue::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case RelativeHumidityMeasurement::Attributes::MaxMeasuredValue::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case RelativeHumidityMeasurement::Attributes::Tolerance::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case RelativeHumidityMeasurement::Attributes::GeneratedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case RelativeHumidityMeasurement::Attributes::AcceptedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case RelativeHumidityMeasurement::Attributes::AttributeList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case RelativeHumidityMeasurement::Attributes::FeatureMap::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case RelativeHumidityMeasurement::Attributes::ClusterRevision::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        default:
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
        }
    }
    case chip::app::Clusters::OccupancySensing::Id: {
        switch (attribute_id)
        {
        case OccupancySensing::Attributes::Occupancy::Id: {
            return { ZCL_BITMAP8_ATTRIBUTE_TYPES, ZCL_BITMAP8_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::OccupancySensorType::Id: {
            return { ZCL_ENUM8_ATTRIBUTE_TYPES, ZCL_ENUM8_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::OccupancySensorTypeBitmap::Id: {
            return { ZCL_BITMAP8_ATTRIBUTE_TYPES, ZCL_BITMAP8_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::PirOccupiedToUnoccupiedDelay::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::PirUnoccupiedToOccupiedDelay::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::PirUnoccupiedToOccupiedThreshold::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::UltrasonicOccupiedToUnoccupiedDelay::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::UltrasonicUnoccupiedToOccupiedDelay::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::UltrasonicUnoccupiedToOccupiedThreshold::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::PhysicalContactOccupiedToUnoccupiedDelay::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::PhysicalContactUnoccupiedToOccupiedDelay::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::PhysicalContactUnoccupiedToOccupiedThreshold::Id: {
            return { ZCL_INT8U_ATTRIBUTE_TYPES, ZCL_INT8U_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::GeneratedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::AcceptedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::AttributeList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::FeatureMap::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case OccupancySensing::Attributes::ClusterRevision::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        default:
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
        }
    }
    case chip::app::Clusters::ElectricalMeasurement::Id: {
        switch (attribute_id)
        {
        case ElectricalMeasurement::Attributes::MeasurementType::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::DcVoltage::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::DcVoltageMin::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::DcVoltageMax::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::DcCurrent::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::DcCurrentMin::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::DcCurrentMax::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::DcPower::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::DcPowerMin::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::DcPowerMax::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::DcVoltageMultiplier::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::DcVoltageDivisor::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::DcCurrentMultiplier::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::DcCurrentDivisor::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::DcPowerMultiplier::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::DcPowerDivisor::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcFrequency::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcFrequencyMin::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcFrequencyMax::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::NeutralCurrent::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::TotalActivePower::Id: {
            return { ZCL_INT32S_ATTRIBUTE_TYPES, ZCL_INT32S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::TotalReactivePower::Id: {
            return { ZCL_INT32S_ATTRIBUTE_TYPES, ZCL_INT32S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::TotalApparentPower::Id: {
            return { ZCL_INT32U_ATTRIBUTE_TYPES, ZCL_INT32U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::Measured1stHarmonicCurrent::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::Measured3rdHarmonicCurrent::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::Measured5thHarmonicCurrent::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::Measured7thHarmonicCurrent::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::Measured9thHarmonicCurrent::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::Measured11thHarmonicCurrent::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::MeasuredPhase1stHarmonicCurrent::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::MeasuredPhase3rdHarmonicCurrent::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::MeasuredPhase5thHarmonicCurrent::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::MeasuredPhase7thHarmonicCurrent::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::MeasuredPhase9thHarmonicCurrent::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::MeasuredPhase11thHarmonicCurrent::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcFrequencyMultiplier::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcFrequencyDivisor::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::PowerMultiplier::Id: {
            return { ZCL_INT32U_ATTRIBUTE_TYPES, ZCL_INT32U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::PowerDivisor::Id: {
            return { ZCL_INT32U_ATTRIBUTE_TYPES, ZCL_INT32U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::HarmonicCurrentMultiplier::Id: {
            return { ZCL_INT8S_ATTRIBUTE_TYPES, ZCL_INT8S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::PhaseHarmonicCurrentMultiplier::Id: {
            return { ZCL_INT8S_ATTRIBUTE_TYPES, ZCL_INT8S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::InstantaneousVoltage::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::InstantaneousLineCurrent::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::InstantaneousActiveCurrent::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::InstantaneousReactiveCurrent::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::InstantaneousPower::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltage::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltageMin::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltageMax::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsCurrent::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsCurrentMin::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsCurrentMax::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ActivePower::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ActivePowerMin::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ActivePowerMax::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ReactivePower::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ApparentPower::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::PowerFactor::Id: {
            return { ZCL_INT8S_ATTRIBUTE_TYPES, ZCL_INT8S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AverageRmsVoltageMeasurementPeriod::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AverageRmsUnderVoltageCounter::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsExtremeOverVoltagePeriod::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsExtremeUnderVoltagePeriod::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltageSagPeriod::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltageSwellPeriod::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcVoltageMultiplier::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcVoltageDivisor::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcCurrentMultiplier::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcCurrentDivisor::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcPowerMultiplier::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcPowerDivisor::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::OverloadAlarmsMask::Id: {
            return { ZCL_BITMAP8_ATTRIBUTE_TYPES, ZCL_BITMAP8_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::VoltageOverload::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::CurrentOverload::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcOverloadAlarmsMask::Id: {
            return { ZCL_BITMAP16_ATTRIBUTE_TYPES, ZCL_BITMAP16_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcVoltageOverload::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcCurrentOverload::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcActivePowerOverload::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcReactivePowerOverload::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AverageRmsOverVoltage::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AverageRmsUnderVoltage::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsExtremeOverVoltage::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsExtremeUnderVoltage::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltageSag::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltageSwell::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::LineCurrentPhaseB::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ActiveCurrentPhaseB::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ReactiveCurrentPhaseB::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltagePhaseB::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltageMinPhaseB::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltageMaxPhaseB::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsCurrentPhaseB::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsCurrentMinPhaseB::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsCurrentMaxPhaseB::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ActivePowerPhaseB::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ActivePowerMinPhaseB::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ActivePowerMaxPhaseB::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ReactivePowerPhaseB::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ApparentPowerPhaseB::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::PowerFactorPhaseB::Id: {
            return { ZCL_INT8S_ATTRIBUTE_TYPES, ZCL_INT8S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AverageRmsVoltageMeasurementPeriodPhaseB::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AverageRmsOverVoltageCounterPhaseB::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AverageRmsUnderVoltageCounterPhaseB::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsExtremeOverVoltagePeriodPhaseB::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsExtremeUnderVoltagePeriodPhaseB::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltageSagPeriodPhaseB::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltageSwellPeriodPhaseB::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::LineCurrentPhaseC::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ActiveCurrentPhaseC::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ReactiveCurrentPhaseC::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltagePhaseC::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltageMinPhaseC::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltageMaxPhaseC::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsCurrentPhaseC::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsCurrentMinPhaseC::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsCurrentMaxPhaseC::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ActivePowerPhaseC::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ActivePowerMinPhaseC::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ActivePowerMaxPhaseC::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ReactivePowerPhaseC::Id: {
            return { ZCL_INT16S_ATTRIBUTE_TYPES, ZCL_INT16S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ApparentPowerPhaseC::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::PowerFactorPhaseC::Id: {
            return { ZCL_INT8S_ATTRIBUTE_TYPES, ZCL_INT8S_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AverageRmsVoltageMeasurementPeriodPhaseC::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AverageRmsOverVoltageCounterPhaseC::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AverageRmsUnderVoltageCounterPhaseC::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsExtremeOverVoltagePeriodPhaseC::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsExtremeUnderVoltagePeriodPhaseC::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltageSagPeriodPhaseC::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::RmsVoltageSwellPeriodPhaseC::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::GeneratedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AcceptedCommandList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::AttributeList::Id: {
            return { ZCL_ARRAY_ATTRIBUTE_TYPES, ZCL_ARRAY_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::FeatureMap::Id: {
            return { ZCL_BITMAP32_ATTRIBUTE_TYPES, ZCL_BITMAP32_ATTRIBUTE_TYPES_SIZE };
        }
        case ElectricalMeasurement::Attributes::ClusterRevision::Id: {
            return { ZCL_INT16U_ATTRIBUTE_TYPES, ZCL_INT16U_ATTRIBUTE_TYPES_SIZE };
        }
        default:
            return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
        }
    }
    default:
        return { ZCL_BOOLEAN_ATTRIBUTE_TYPES, 0x01 };
    }
}