/********************************************************************************************************
 * @file    sampleSensorEpCfg.c
 *
 * @brief   This is the source file for sampleSensorEpCfg
 *
 * @author  Zigbee Group
 * @date    2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *******************************************************************************************************/

/**********************************************************************
 * INCLUDES
 */
#include "tl_common.h"
#include "zcl_include.h"
#include "zcl_relative_humidity.h"
#include "device.h"

/**********************************************************************
 * LOCAL CONSTANTS
 */
#ifndef ZCL_BASIC_MFG_NAME
#define ZCL_BASIC_MFG_NAME     {6,'X','i','a','o','m','i'}
#endif
#ifndef ZCL_BASIC_MODEL_ID
#define ZCL_BASIC_MODEL_ID	   {14,'l','u','m','i','.','s','e','n','s','o','r','_','h','t'}
#endif
#ifndef ZCL_BASIC_SW_BUILD_ID
#define ZCL_BASIC_SW_BUILD_ID     	{9,'3','0','0','0','-','0','0','0','1'}
#endif


/**********************************************************************
 * TYPEDEFS
 */


/**********************************************************************
 * GLOBAL VARIABLES
 */
/**
 *  @brief Definition for Incoming cluster / Sever Cluster
 */
const u16 sensorDevice_inClusterList[] =
{
	ZCL_CLUSTER_GEN_BASIC,
	ZCL_CLUSTER_GEN_IDENTIFY,

#ifdef ZCL_RELATIVE_HUMIDITY_MEASUREMENT
    ZCL_CLUSTER_MS_RELATIVE_HUMIDITY,
#endif
#ifdef ZCL_TEMPERATURE_MEASUREMENT
	ZCL_CLUSTER_MS_TEMPERATURE_MEASUREMENT,
#endif
#ifdef ZCL_POLL_CTRL
	ZCL_CLUSTER_GEN_POLL_CONTROL,
#endif
};

/**
 *  @brief Definition for Outgoing cluster / Client Cluster
 */
const u16 sensorDevice_outClusterList[] =
{
#ifdef ZCL_OTA
    ZCL_CLUSTER_OTA,
#endif
};

/**
 *  @brief Definition for Server cluster number and Client cluster number
 */
#define sensorDevice_IN_CLUSTER_NUM		(sizeof(sensorDevice_inClusterList)/sizeof(sensorDevice_inClusterList[0]))
#define sensorDevice_OUT_CLUSTER_NUM	(sizeof(sensorDevice_outClusterList)/sizeof(sensorDevice_outClusterList[0]))

/**
 *  @brief Definition for simple description for HA profile
 */
const af_simple_descriptor_t sensorDevice_simpleDesc =
{
	HA_PROFILE_ID,                      	/* Application profile identifier */
	HA_DEV_TEMPERATURE_SENSOR,              /* Application device identifier */
	SENSOR_DEVICE_ENDPOINT,         		/* Endpoint */
	0,                                  	/* Application device version */
	0,										/* Reserved */
	sensorDevice_IN_CLUSTER_NUM,           	/* Application input cluster count */
	sensorDevice_OUT_CLUSTER_NUM,          	/* Application output cluster count */
	(u16 *)sensorDevice_inClusterList,    	/* Application input cluster list */
	(u16 *)sensorDevice_outClusterList,   	/* Application output cluster list */
};

/* Basic */
zcl_basicAttr_t g_zcl_basicAttrs =
{
	.zclVersion 	= 0x03,
	.appVersion 	= 0x00,
	.stackVersion 	= 0x02,
	.hwVersion		= 0x00,
	.manuName		= ZCL_BASIC_MFG_NAME,
	.modelId		= ZCL_BASIC_MODEL_ID,
	.swBuildId		= ZCL_BASIC_SW_BUILD_ID,
	.powerSource	= POWER_SOURCE_BATTERY,
	.deviceEnable	= TRUE,
};

const zclAttrInfo_t basic_attrTbl[] =
{
	{ ZCL_ATTRID_BASIC_ZCL_VER,      		ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs.zclVersion},
	{ ZCL_ATTRID_BASIC_APP_VER,      		ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs.appVersion},
	{ ZCL_ATTRID_BASIC_STACK_VER,    		ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs.stackVersion},
	{ ZCL_ATTRID_BASIC_HW_VER,       		ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs.hwVersion},
	{ ZCL_ATTRID_BASIC_MFR_NAME,     		ZCL_DATA_TYPE_CHAR_STR, ACCESS_CONTROL_READ,  						(u8*)g_zcl_basicAttrs.manuName},
	{ ZCL_ATTRID_BASIC_MODEL_ID,     		ZCL_DATA_TYPE_CHAR_STR, ACCESS_CONTROL_READ,  						(u8*)g_zcl_basicAttrs.modelId},
	{ ZCL_ATTRID_BASIC_POWER_SOURCE, 		ZCL_DATA_TYPE_ENUM8,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs.powerSource},
	{ ZCL_ATTRID_BASIC_DEV_ENABLED,  		ZCL_DATA_TYPE_BOOLEAN,  ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, (u8*)&g_zcl_basicAttrs.deviceEnable},
	{ ZCL_ATTRID_BASIC_SW_BUILD_ID,  		ZCL_DATA_TYPE_CHAR_STR, ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs.swBuildId},

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,  						(u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_BASIC_ATTR_NUM 				sizeof(basic_attrTbl) / sizeof(zclAttrInfo_t)


/* Identify */
zcl_identifyAttr_t g_zcl_identifyAttrs =
{
	.identifyTime	= 0x0000,
};

const zclAttrInfo_t identify_attrTbl[] =
{
	{ ZCL_ATTRID_IDENTIFY_TIME,  			ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, (u8*)&g_zcl_identifyAttrs.identifyTime },

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,  						(u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_IDENTIFY_ATTR_NUM			sizeof(identify_attrTbl) / sizeof(zclAttrInfo_t)

#ifdef ZCL_IAS_ZONE
/* IAS Zone */
zcl_iasZoneAttr_t g_zcl_iasZoneAttrs =
{
	.zoneState		= ZONE_STATE_NOT_ENROLLED,
	.zoneType		= ZONE_TYPE_CONTACT_SWITCH,
	.zoneStatus		= 0x00,
	.iasCieAddr		= {0x00},
	.zoneId 		= ZCL_ZONE_ID_INVALID,
};

const zclAttrInfo_t iasZone_attrTbl[] =
{
	{ ZCL_ATTRID_ZONE_STATE,   ZCL_DATA_TYPE_ENUM8,     ACCESS_CONTROL_READ,  						(u8*)&g_zcl_iasZoneAttrs.zoneState },
	{ ZCL_ATTRID_ZONE_TYPE,    ZCL_DATA_TYPE_ENUM16,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_iasZoneAttrs.zoneType },
	{ ZCL_ATTRID_ZONE_STATUS,  ZCL_DATA_TYPE_BITMAP16,  ACCESS_CONTROL_READ,  						(u8*)&g_zcl_iasZoneAttrs.zoneStatus },
	{ ZCL_ATTRID_IAS_CIE_ADDR, ZCL_DATA_TYPE_IEEE_ADDR, ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, (u8*)g_zcl_iasZoneAttrs.iasCieAddr },
	{ ZCL_ATTRID_ZONE_ID,	   ZCL_DATA_TYPE_UINT8,     ACCESS_CONTROL_READ,  						(u8*)&g_zcl_iasZoneAttrs.zoneId},

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, ZCL_DATA_TYPE_UINT16,  ACCESS_CONTROL_READ,  				(u8*)&zcl_attr_global_clusterRevision},
};

#define	ZCL_IASZONE_ATTR_NUM		 sizeof(iasZone_attrTbl) / sizeof(zclAttrInfo_t)
#endif



#ifdef ZCL_TEMPERATURE_MEASUREMENT
zcl_temperatureAttr_t g_zcl_temperatureAttrs =
{
	.measuredValue	= 0xFFFF,
};

const zclAttrInfo_t temperature_measurement_attrTbl[] =
{
	{ ZCL_TEMPERATURE_MEASUREMENT_ATTRID_MEASUREDVALUE,       ZCL_DATA_TYPE_INT16,    ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE, (u8*)&g_zcl_temperatureAttrs.measuredValue },

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,  						(u8*)&zcl_attr_global_clusterRevision},
};

#define	ZCL_TEMPERATURE_MEASUREMENT_ATTR_NUM		 sizeof(temperature_measurement_attrTbl) / sizeof(zclAttrInfo_t)
#endif


#ifdef ZCL_RELATIVE_HUMIDITY
zcl_relHumidityAttr_t g_zcl_relHumidityAttrs =
{
	.measuredValue	= 0xFFFF,
};

const zclAttrInfo_t relative_humdity_attrTbl[] =
{
	{ ZCL_RELATIVE_HUMIDITY_ATTRID_MEASUREDVALUE,       ZCL_DATA_TYPE_INT16,    ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE, (u8*)&g_zcl_relHumidityAttrs.measuredValue },

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,  						(u8*)&zcl_attr_global_clusterRevision},
};

#define	ZCL_RELATIVE_HUMIDITY_ATTR_NUM		 sizeof(relative_humdity_attrTbl) / sizeof(zclAttrInfo_t)
#endif


#ifdef ZCL_POLL_CTRL
/* Poll Control */
zcl_pollCtrlAttr_t g_zcl_pollCtrlAttrs =
{
	.chkInInterval			= 0x3840,
	.longPollInterval		= 0x14,
	.shortPollInterval		= 0x02,
	.fastPollTimeout		= 0x28,
	.chkInIntervalMin		= 0x00,
	.longPollIntervalMin	= 0x00,
	.fastPollTimeoutMax		= 0x00,
};

const zclAttrInfo_t pollCtrl_attrTbl[] =
{
	{ ZCL_ATTRID_CHK_IN_INTERVAL,  		ZCL_DATA_TYPE_UINT32, ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, (u8*)&g_zcl_pollCtrlAttrs.chkInInterval },
	{ ZCL_ATTRID_LONG_POLL_INTERVAL, 	ZCL_DATA_TYPE_UINT32, ACCESS_CONTROL_READ, 						  (u8*)&g_zcl_pollCtrlAttrs.longPollInterval },
	{ ZCL_ATTRID_SHORT_POLL_INTERVAL, 	ZCL_DATA_TYPE_UINT16, ACCESS_CONTROL_READ, 						  (u8*)&g_zcl_pollCtrlAttrs.shortPollInterval },
	{ ZCL_ATTRID_FAST_POLL_TIMEOUT, 	ZCL_DATA_TYPE_UINT16, ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, (u8*)&g_zcl_pollCtrlAttrs.fastPollTimeout },
	{ ZCL_ATTRID_CHK_IN_INTERVAL_MIN, 	ZCL_DATA_TYPE_UINT32, ACCESS_CONTROL_READ, 						  (u8*)&g_zcl_pollCtrlAttrs.chkInIntervalMin},
	{ ZCL_ATTRID_LONG_POLL_INTERVAL_MIN,ZCL_DATA_TYPE_UINT32, ACCESS_CONTROL_READ, 						  (u8*)&g_zcl_pollCtrlAttrs.longPollIntervalMin },
	{ ZCL_ATTRID_FAST_POLL_TIMEOUT_MAX, ZCL_DATA_TYPE_UINT16, ACCESS_CONTROL_READ, 						  (u8*)&g_zcl_pollCtrlAttrs.fastPollTimeoutMax},

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, ZCL_DATA_TYPE_UINT16,  ACCESS_CONTROL_READ,  					  (u8*)&zcl_attr_global_clusterRevision},
};

#define	ZCL_POLLCTRL_ATTR_NUM		 sizeof(pollCtrl_attrTbl) / sizeof(zclAttrInfo_t)
#endif

/**
 *  @brief Definition for simple contact sensor ZCL specific cluster
 */
const zcl_specClusterInfo_t g_sampleSensorClusterList[] =
{
	{ZCL_CLUSTER_GEN_BASIC,			MANUFACTURER_CODE_NONE, ZCL_BASIC_ATTR_NUM, 	basic_attrTbl,  	zcl_basic_register,		sensorDevice_basicCb},
	{ZCL_CLUSTER_GEN_IDENTIFY,		MANUFACTURER_CODE_NONE, ZCL_IDENTIFY_ATTR_NUM,	identify_attrTbl,	zcl_identify_register,	sensorDevice_identifyCb},
#ifdef ZCL_IAS_ZONE
	{ZCL_CLUSTER_SS_IAS_ZONE,		MANUFACTURER_CODE_NONE, ZCL_IASZONE_ATTR_NUM,	iasZone_attrTbl,	zcl_iasZone_register,	sensorDevice_iasZoneCb},
#endif
#ifdef ZCL_TEMPERATURE_MEASUREMENT
	{ZCL_CLUSTER_MS_TEMPERATURE_MEASUREMENT,	MANUFACTURER_CODE_NONE, ZCL_TEMPERATURE_MEASUREMENT_ATTR_NUM, temperature_measurement_attrTbl, 	zcl_temperature_measurement_register, 	NULL},
#endif
#ifdef ZCL_RELATIVE_HUMIDITY
	{ZCL_CLUSTER_MS_RELATIVE_HUMIDITY,	MANUFACTURER_CODE_NONE, ZCL_RELATIVE_HUMIDITY_ATTR_NUM, 		relative_humdity_attrTbl,	zcl_relative_humidity_register, 	NULL},
#endif
#ifdef ZCL_POLL_CTRL
	{ZCL_CLUSTER_GEN_POLL_CONTROL,  MANUFACTURER_CODE_NONE, ZCL_POLLCTRL_ATTR_NUM, 	pollCtrl_attrTbl,   zcl_pollCtrl_register,	sensorDevice_pollCtrlCb},
#endif
};

u8 SENSOR_DEVICE_CB_CLUSTER_NUM = (sizeof(g_sampleSensorClusterList)/sizeof(g_sampleSensorClusterList[0]));

/**********************************************************************
 * FUNCTIONS
 */