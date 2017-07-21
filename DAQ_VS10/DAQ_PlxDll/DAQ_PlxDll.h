#if !defined(AFX_DAQ_PLXDLL_H__5D787C11_9A53_4B53_BAAF_CAE9E22D6BB4__INCLUDED_)
#define AFX_DAQ_PLXDLL_H__5D787C11_9A53_4B53_BAAF_CAE9E22D6BB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DAQ_Control.h"
#include <comip.h>

/* Base Attribute Definitions											*/
/************************************************************************/
#define IVI_ATTR_BASE											1000000
#define IVI_INHERENT_ATTR_BASE									IVI_ATTR_BASE + 50000
#define IVI_INSTR_SPECIFIC_ATTR_BASE							IVI_ATTR_BASE + 100000
#define IVI_CLASS_ATTR_BASE										IVI_ATTR_BASE + 200000
#define IVI_VENDOR_CLASS_EXT_ATTR_BASE							IVI_ATTR_BASE + 350000
#define IVI_VENDOR_INHERENT_EXT_ATTR_BASE						IVI_ATTR_BASE + 450000
#define IVI_MODULE_PRIVATE_ATTR_BASE							IVI_ATTR_BASE + 550000
#define IVILXISYNC_ATTR_BASE									IVI_ATTR_BASE + 950000
#define IVI_LXISYNC_ATTR_BASE									IVI_ATTR_BASE + 1950000

/************************************************************************/
/* Inherent Attribute Definitions                                       */
/************************************************************************/

/*======User Options Attributes======*/
#define DAQ_ATTR_RANGE_CHECK								IVI_INHERENT_ATTR_BASE + 2
#define DAQ_ATTR_QUERY_INSTRUMENT_STATUS					IVI_INHERENT_ATTR_BASE + 3
#define DAQ_ATTR_CACHE										IVI_INHERENT_ATTR_BASE + 4
#define DAQ_ATTR_SIMULATE									IVI_INHERENT_ATTR_BASE + 5
#define DAQ_ATTR_RECORD_COERCIONS							IVI_INHERENT_ATTR_BASE + 6
#define DAQ_ATTR_INTERCHANGE_CHECK							IVI_INHERENT_ATTR_BASE + 21
/*======Class Driver Identification Attributes======*/
#define DAQ_ATTR_CLASS_DRIVER_DESCRIPTION					IVI_INHERENT_ATTR_BASE + 514
#define DAQ_ATTR_CLASS_DRIVER_PREFIX						IVI_INHERENT_ATTR_BASE + 301
#define DAQ_ATTR_CLASS_DRIVER_VENDOR						IVI_INHERENT_ATTR_BASE + 517
#define DAQ_ATTR_CLASS_DRIVER_REVISION						IVI_INHERENT_ATTR_BASE + 552
#define DAQ_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION		IVI_INHERENT_ATTR_BASE + 519
#define DAQ_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION		IVI_INHERENT_ATTR_BASE + 520
/*======Driver Identification Attributes======*/
#define DAQ_ATTR_SPECIFIC_DRIVER_DESCRIPTION				IVI_INHERENT_ATTR_BASE + 514
#define DAQ_ATTR_SPECIFIC_DRIVER_PREFIX						IVI_INHERENT_ATTR_BASE + 302
#define DAQ_ATTR_SPECIFIC_DRIVER_LOCATOR					IVI_INHERENT_ATTR_BASE + 303
#define DAQ_ATTR_SPECIFIC_DRIVER_VENDOR						IVI_INHERENT_ATTR_BASE + 513
#define DAQ_ATTR_SPECIFIC_DRIVER_REVISION					IVI_INHERENT_ATTR_BASE + 551
#define DAQ_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION	IVI_INHERENT_ATTR_BASE + 515
#define DAQ_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION	IVI_INHERENT_ATTR_BASE + 516
/*======Driver Capabilities Attributes======*/
#define DAQ_ATTR_SUPPORTED_INSTRUMENT_MODELS				IVI_INHERENT_ATTR_BASE + 327
#define DAQ_ATTR_GROUP_CAPABILITIES							IVI_INHERENT_ATTR_BASE + 401
/*======Instrument Identification Attributes======*/
#define DAQ_ATTR_INSTRUMENT_MANUFACTURER					IVI_INHERENT_ATTR_BASE + 511
#define DAQ_ATTR_INSTRUMENT_MODEL							IVI_INHERENT_ATTR_BASE + 512
#define DAQ_ATTR_INSTRUMENT_FIRMWARE_REVISION				IVI_INHERENT_ATTR_BASE + 510
/*======Advanced Session Information Attributes======*/
#define DAQ_ATTR_LOGICAL_NAME								IVI_INHERENT_ATTR_BASE + 305
#define DAQ_ATTR_IO_RESOURCE_DESCRIPTOR						IVI_INHERENT_ATTR_BASE + 304
#define DAQ_ATTR_DRIVER_SETUP								IVI_INHERENT_ATTR_BASE + 7

/************************************************************************/
/* Instrument Attribute Definitions                                     */
/************************************************************************/

/*======Acquisition Attributes=====*/
#define DAQ_ATTR_ACQUISITION_START_TIME						IVI_CLASS_ATTR_BASE + 109
#define DAQ_ATTR_ACQUISITION_TYPE							IVI_CLASS_ATTR_BASE + 101
#define DAQ_ATTR_HORZ_MIN_NUM_PTS							IVI_CLASS_ATTR_BASE + 9
#define DAQ_ATTR_HORZ_RECORD_LENGTH							IVI_CLASS_ATTR_BASE + 8
#define DAQ_ATTR_HORZ_SAMPLE_RATE							IVI_CLASS_ATTR_BASE + 10
#define DAQ_ATTR_HORZ_TIME_PER_RECORD						IVI_CLASS_ATTR_BASE + 7
#define DAQ_ATTR_INTERPOLATION								IVI_CLASS_ATTR_BASE + 19
#define DAQ_ATTR_SAMPLE_MODE								IVI_CLASS_ATTR_BASE + 106
#define DAQ_ATTR_NUM_AVERAGES								IVI_CLASS_ATTR_BASE + 104
#define DAQ_ATTR_NUM_ENVELOPES								IVI_CLASS_ATTR_BASE + 105
#define DAQ_ATTR_INITIATE_CONTINUOUS						IVI_CLASS_ATTR_BASE + 107
/*======Channel Attributes======*/
#define DAQ_ATTR_CHANNEL_COUNT								IVI_INHERENT_ATTR_BASE + 203
#define DAQ_ATTR_CHANNEL_ENABLED							IVI_CLASS_ATTR_BASE + 5
#define DAQ_ATTR_PROBE_ATTENUATION							IVI_CLASS_ATTR_BASE + 4
#define DAQ_ATTR_PROBE_SENSE_VALUE							IVI_CLASS_ATTR_BASE + 108
#define DAQ_ATTR_VERTICAL_RANGE								IVI_CLASS_ATTR_BASE + 1
#define DAQ_ATTR_VERTICAL_OFFSET							IVI_CLASS_ATTR_BASE + 2
#define DAQ_ATTR_VERTICAL_COUPLING							IVI_CLASS_ATTR_BASE + 3
#define DAQ_ATTR_MAX_INPUT_FREQUENCY						IVI_CLASS_ATTR_BASE + 6
#define DAQ_ATTR_INPUT_IMPEDANCE							IVI_CLASS_ATTR_BASE + 103
/*======Trigger Attributes======*/
#define DAQ_ATTR_TRIGGER_TYPE								IVI_CLASS_ATTR_BASE + 12
#define DAQ_ATTR_TRIGGER_SOURCE								IVI_CLASS_ATTR_BASE + 13
#define DAQ_ATTR_TRIGGER_COUPLING							IVI_CLASS_ATTR_BASE + 14
#define DAQ_ATTR_TRIGGER_HOLDOFF							IVI_CLASS_ATTR_BASE + 16
#define DAQ_ATTR_TRIGGER_LEVEL								IVI_CLASS_ATTR_BASE + 17
#define DAQ_ATTR_TRIGGER_DELAY							    IVI_CLASS_ATTR_BASE + 30
#define DAQ_ATTR_TRIGGER_MODIFIER							IVI_CLASS_ATTR_BASE + 102
/*======Edge Triggering Attributes======*/
#define DAQ_ATTR_TRIGGER_SLOPE								IVI_CLASS_ATTR_BASE + 18
/*======TV Triggering Attributes======*/
#define DAQ_ATTR_TV_TRIGGER_SIGNAL_FORMAT					IVI_CLASS_ATTR_BASE + 201
#define DAQ_ATTR_TV_TRIGGER_EVENT							IVI_CLASS_ATTR_BASE + 205
#define DAQ_ATTR_TV_TRIGGER_LINE_NUMBER						IVI_CLASS_ATTR_BASE + 206
#define DAQ_ATTR_TV_TRIGGER_POLARITY						IVI_CLASS_ATTR_BASE + 204
/*======Runt Triggering Attributes======*/
#define DAQ_ATTR_RUNT_HIGH_THRESHOLD						IVI_CLASS_ATTR_BASE + 301
#define DAQ_ATTR_RUNT_LOW_THRESHOLD							IVI_CLASS_ATTR_BASE + 302
#define DAQ_ATTR_RUNT_POLARITY								IVI_CLASS_ATTR_BASE + 303
/*======Glitch Triggerin======*/
#define DAQ_ATTR_GLITCH_WIDTH								IVI_CLASS_ATTR_BASE + 401
#define DAQ_ATTR_GLITCH_POLARITY							IVI_CLASS_ATTR_BASE + 402
#define DAQ_ATTR_GLITCH_CONDITION							IVI_CLASS_ATTR_BASE + 403
/*======Width Triggering Attributes======*/
#define DAQ_ATTR_WIDTH_CONDITION							IVI_CLASS_ATTR_BASE + 504
#define DAQ_ATTR_WIDTH_HIGH_THRESHOLD						IVI_CLASS_ATTR_BASE + 502
#define DAQ_ATTR_WIDTH_LOW_THRESHOLD						IVI_CLASS_ATTR_BASE + 501
#define DAQ_ATTR_WIDTH_POLARITY								IVI_CLASS_ATTR_BASE + 503
/*======AC Line Triggering Attributes======*/
#define DAQ_ATTR_AC_LINE_TRIGGER_SLOPE						IVI_CLASS_ATTR_BASE + 701
/*======Waveform Measurement Attributes======*/
#define DAQ_ATTR_MEAS_HIGH_REF								IVI_CLASS_ATTR_BASE + 607
#define DAQ_ATTR_MEAS_LOW_REF								IVI_CLASS_ATTR_BASE + 608
#define DAQ_ATTR_MEAS_MID_REF								IVI_CLASS_ATTR_BASE + 609
/*======Extend Attributes======*/
#define DAQ_ATTR_DRIVER_CONFIG								IVI_VENDOR_CLASS_EXT_ATTR_BASE + 1
#define DAQ_ATTR_INSTRUMENT_CONFIG							IVI_VENDOR_CLASS_EXT_ATTR_BASE + 2
#define DAQ_ATTR_INSTRUMENT_CONFIG_E						IVI_VENDOR_CLASS_EXT_ATTR_BASE + 3

//////////////////////////////////////////////////////////////////////////
//  自定义属性
//////////////////////////////////////////////////////////////////////////
#define DAQ_ATTR_CAL_MAX_NUM							 IVI_VENDOR_CLASS_EXT_ATTR_BASE + 100
#define DAQ_ATTR_CAL_LOAD_NUM							 IVI_VENDOR_CLASS_EXT_ATTR_BASE + 101
#define DAQ_ATTR_STOP_FLAG_IN_SCAN_MODE                  IVI_VENDOR_CLASS_EXT_ATTR_BASE + 102
#define DAQ_ATTR_WAVE_SMOOTH_FLAG                        IVI_VENDOR_CLASS_EXT_ATTR_BASE + 103
#define DAQ_ATTR_READ_DATA_IN_IO_MODE                    IVI_VENDOR_CLASS_EXT_ATTR_BASE + 104

#define DAQ_ATTR_BANDWIDTH_HOLD                          IVI_VENDOR_CLASS_EXT_ATTR_BASE + 105//带宽抑制
#define DAQ_ATTR_AUTO_FLAG                               IVI_VENDOR_CLASS_EXT_ATTR_BASE + 106
#define DAQ_ATTR_CALIBRATION_CHECK                       IVI_VENDOR_CLASS_EXT_ATTR_BASE + 107

#define DAQ_ATTR_ACQUISITION_CLOCK                       IVI_VENDOR_CLASS_EXT_ATTR_BASE + 108
#define DAQ_ATTR_TRIGGER_BANDWIDTH_HOLD                  IVI_VENDOR_CLASS_EXT_ATTR_BASE + 109
#define DAQ_ATTR_INTERPOLATION_TYPE                      IVI_VENDOR_CLASS_EXT_ATTR_BASE + 110  

#define DAQ_ATTR_MEMORY_SIZE                             IVI_VENDOR_CLASS_EXT_ATTR_BASE + 111  // 存储深度    

/************************************************************************/
/* Attribute Value Definitions                                          */
/************************************************************************/

#define DAQ_VAL_NORMAL										0
#define DAQ_VAL_PEAK_DETECT									1
#define DAQ_VAL_HI_RES										2
#define DAQ_VAL_ENVELOPE									3
#define DAQ_VAL_AVERAGE										4
#define DAQ_VAL_ACQUISITION_TYPE_CLASS_EXT_BASE				100
#define DAQ_VAL_ACQUISITION_TYPE_SPECIFIC_EXT_BASE			1000

#define DAQ_VAL_PROBE_SENSE_ON								-1
#define DAQ_VAL_PROBE_ATTENUATION_CLASS_EXT_BASE			-100
#define DAQ_VAL_PROBE_ATTENUATION_SPECIFIC_EXT_BASE			-1000

#define DAQ_VAL_AC											0
#define DAQ_VAL_DC											1
#define DAQ_VAL_GND											2
#define DAQ_VAL_VERTICAL_COUPLING_CLASS_EXT_BASE			100
#define DAQ_VAL_VERTICAL_COUPLING_SPECIFIC_EXT_BASE			1000

#define DAQ_VAL_AC											0
#define DAQ_VAL_DC											1
#define DAQ_VAL_GND											2
#define DAQ_VAL_HF_REJECT									3
#define DAQ_VAL_LF_REJECT									4
#define DAQ_VAL_NOISE_REJECT								5
#define DAQ_VAL_TRIGGER_COUPLING_CLASS_EXT_BASE				100
#define DAQ_VAL_TRIGGER_COUPLING_SPECIFIC_EXT_BASE			1000

#define DAQ_VAL_NEGATIVE									0
#define DAQ_VAL_POSITIVE									1

#define DAQ_VAL_CH0											"VAL_CH0"
#define DAQ_VAL_CH1											"VAL_CH1"
#define DAQ_VAL_CH2											"VAL_CH2"
#define DAQ_VAL_CH3											"VAL_CH3"
#define DAQ_VAL_EXTERNAL									"VAL_EXTERNAL"
#define DAQ_VAL_EXTERNAL5									"VAL_EXTERNAL5"

#define DAQ_VAL_ECL0										"VAL_ECL0"
#define DAQ_VAL_ECL1										"VAL_ECL1"
#define DAQ_VAL_LAN0										"VAL_LAN0"
#define DAQ_VAL_LAN1										"VAL_LAN1"
#define DAQ_VAL_LAN2										"VAL_LAN2"
#define DAQ_VAL_LAN3										"VAL_LAN3"
#define DAQ_VAL_LAN4										"VAL_LAN4"
#define DAQ_VAL_LAN5										"VAL_LAN5"
#define DAQ_VAL_LAN6										"VAL_LAN6"
#define DAQ_VAL_LAN7										"VAL_LAN7"
#define DAQ_VAL_LXI0										"VAL_LXI0"
#define DAQ_VAL_LXI1										"VAL_LXI1"
#define DAQ_VAL_LXI2										"VAL_LXI2"
#define DAQ_VAL_LXI3										"VAL_LXI3"
#define DAQ_VAL_LXI4										"VAL_LXI4"
#define DAQ_VAL_LXI5										"VAL_LXI5"
#define DAQ_VAL_LXI6										"VAL_LXI6"
#define DAQ_VAL_LXI7										"VAL_LXI7"
#define DAQ_VAL_PXI_STAR									"VAL_PXI_STAR"
#define DAQ_VAL_PXI_TRIG0									"VAL_PXI_TRIG0"
#define DAQ_VAL_PXI_TRIG1									"VAL_PXI_TRIG1"
#define DAQ_VAL_PXI_TRIG2									"VAL_PXI_TRIG2"
#define DAQ_VAL_PXI_TRIG3									"VAL_PXI_TRIG3"
#define DAQ_VAL_PXI_TRIG4									"VAL_PXI_TRIG4"
#define DAQ_VAL_PXI_TRIG5									"VAL_PXI_TRIG5"
#define DAQ_VAL_PXI_TRIG6									"VAL_PXI_TRIG6"
#define DAQ_VAL_PXI_TRIG7									"VAL_PXI_TRIG7"

#define DAQ_VAL_PXIe_DSTARA									"VAL_PXIe_DSTARA"
#define DAQ_VAL_PXIe_DSTARB									"VAL_PXIe_DSTARB"
#define DAQ_VAL_PXIe_DSTARC									"VAL_PXIe_DSTARC"
#define DAQ_VAL_RTSI_0										"VAL_RTSI_0"
#define DAQ_VAL_RTSI_1										"VAL_RTSI_1"
#define DAQ_VAL_RTSI_2										"VAL_RTSI_2"
#define DAQ_VAL_RTSI_3										"VAL_RTSI_3"
#define DAQ_VAL_RTSI_4										"VAL_RTSI_4"
#define DAQ_VAL_RTSI_5										"VAL_RTSI_5"
#define DAQ_VAL_RTSI_6										"VAL_RTSI_6"
#define DAQ_VAL_TTL0										"VAL_TTL0"
#define DAQ_VAL_TTL1										"VAL_TTL1"
#define DAQ_VAL_TTL2										"VAL_TTL2"
#define DAQ_VAL_TTL3										"VAL_TTL3"
#define DAQ_VAL_TTL4										"VAL_TTL4"
#define DAQ_VAL_TTL5										"VAL_TTL5"
#define DAQ_VAL_TTL6										"VAL_TTL6"
#define DAQ_VAL_TTL7										"VAL_TTL7"

#define DAQ_VAL_EDGE_TRIGGER								1
#define DAQ_VAL_WIDTH_TRIGGER								2
#define DAQ_VAL_RUNT_TRIGGER								3
#define DAQ_VAL_GLITCH_TRIGGER								4
#define DAQ_VAL_TV_TRIGGER									5
#define DAQ_VAL_IMMEDIATE_TRIGGER							6
#define DAQ_VAL_AC_LINE_TRIGGER								7
#define DAQ_VAL_TRIGGER_TYPE_CLASS_EXT_BASE					200
#define DAQ_VAL_TRIGGER_TYPE_SPECIFIC_EXT_BASE				1000
#define DAQ_VAL_PXI_TRIGGER									DAQ_VAL_TRIGGER_TYPE_SPECIFIC_EXT_BASE + 2
#define DAQ_VAL_LXI_TRIGGER									DAQ_VAL_TRIGGER_TYPE_SPECIFIC_EXT_BASE + 3

#define DAQ_VAL_NO_INTERPOLATION							1
#define DAQ_VAL_SINE_X										2
#define DAQ_VAL_LINEAR										3
#define DAQ_VAL_INTERPOLATION_CLASS_EXT_BASE				100
#define DAQ_VAL_INTERPOLATION_SPECIFIC_EXT_BASE				1000

#define DAQ_VAL_TV_EVENT_FIELD1								1
#define DAQ_VAL_TV_EVENT_FIELD2								2
#define DAQ_VAL_TV_EVENT_ANY_FIELD							3
#define DAQ_VAL_TV_EVENT_ANY_LINE							4
#define DAQ_VAL_TV_EVENT_LINE_NUMBER						5
#define DAQ_VAL_TV_TRIGGER_EVENT_CLASS_EXT_BASE				100
#define DAQ_VAL_TV_TRIGGER_EVENT_SPECIFIC_EXT_BASE			1000

#define DAQ_VAL_NTSC										1
#define DAQ_VAL_PAL											2
#define DAQ_VAL_SECAM										3
#define DAQ_VAL_TV_SIGNAL_FORMAT_CLASS_EXT_BASE				100
#define DAQ_VAL_TV_SIGNAL_FORMAT_SPECIFIC_EXT_BASE			1000

#define DAQ_VAL_TV_POSITIVE									1
#define DAQ_VAL_TV_NEGATIVE									2
#define DAQ_VAL_TV_TRIGGER_POLARITY_CLASS_EXT_BASE			100
#define DAQ_VAL_TV_TRIGGER_POLARITY_SPECIFIC_EXT_BASE		1000

#define	DAQ_VAL_RUNT_POSITIVE								1
#define DAQ_VAL_RUNT_NEGATIVE								2
#define DAQ_VAL_RUNT_EITHER									3

#define DAQ_VAL_GLITCH_POSITIVE								1
#define DAQ_VAL_GLITCH_NEGATIVE								2
#define DAQ_VAL_GLITCH_EITHER								3

#define DAQ_VAL_GLITCH_LESS_THAN							1
#define DAQ_VAL_GLITCH_GREATER_THAN							2

#define DAQ_VAL_WIDTH_WITHIN								1
#define DAQ_VAL_WIDTH_OUTSIDE								2
#define DAQ_VAL_WIDTH_EQUAL									3
#define DAQ_VAL_WIDTH_NOT_EQUAL 							4

#define DAQ_VAL_WIDTH_POSITIVE								1
#define DAQ_VAL_WIDTH_NEGATIVE								2
#define DAQ_VAL_WIDTH_EITHER								3

#define DAQ_VAL_AC_LINE_POSITIVE							1
#define DAQ_VAL_AC_LINE_NEGATIVE							2
#define DAQ_VAL_AC_LINE_EITHER								3

#define DAQ_VAL_REAL_TIME									0
#define DAQ_VAL_EQUIVALENT_TIME								1

#define DAQ_VAL_NO_TRIGGER_MOD								1
#define DAQ_VAL_AUTO										2
#define DAQ_VAL_AUTO_LEVEL									3
#define DAQ_VAL_TRIGGER_MOD_CLASS_EXT_BASE					100
#define DAQ_VAL_TRIGGER_MOD_SPECIFIC_EXT_BASE				1000

#define DAQ_VAL_RISE_TIME									0
#define DAQ_VAL_FALL_TIME									1
#define DAQ_VAL_FREQUENCY									2
#define DAQ_VAL_PERIOD										3
#define DAQ_VAL_VOLTAGE_RMS									4
#define DAQ_VAL_VOLTAGE_PEAK_TO_PEAK						5
#define DAQ_VAL_VOLTAGE_MAX									6
#define DAQ_VAL_VOLTAGE_MIN									7
#define DAQ_VAL_VOLTAGE_HIGH								8
#define DAQ_VAL_VOLTAGE_LOW									9
#define DAQ_VAL_VOLTAGE_AVERAGE								10
#define DAQ_VAL_WIDTH_NEG									11
#define DAQ_VAL_WIDTH_POS									12
#define DAQ_VAL_DUTY_CYCLE_NEG								13
#define DAQ_VAL_DUTY_CYCLE_POS								14
#define DAQ_VAL_AMPLITUDE									15
#define DAQ_VAL_VOLTAGE_CYCLE_RMS							16
#define DAQ_VAL_VOLTAGE_CYCLE_AVERAGE						17
#define DAQ_VAL_OVERSHOOT									18
#define DAQ_VAL_PRESHOOT									19
#define DAQ_VAL_MEASUREMENT_FUNCTION_CLASS_EXT_BASE			100
#define DAQ_VAL_MEASUREMENT_FUNCTION_SPECIFIC_EXT_BASE		1000
#define DAQ_VAL_MAX_TIME_IMMEDIATE							0x0
#define DAQ_VAL_MAX_TIME_INFINITE							0xFFFFFFFFUL

// 查询采集状态时，暂定这些状态，后期优化可减少查询？
#define DAQ_VAL_ACQ_COMPLETE								1//采集完成
#define DAQ_VAL_ACQ_CAN_INIT_ACQ                            2//可以开始下一次采集
#define DAQ_VAL_ACQ_IN_PROGRESS								0
#define DAQ_VAL_ACQ_STATUS_UNKNOWN							-1


// DDR采集状态定义
#define DAQ_VAL_ACQ_DDR_COMPLETE	                        1							
#define DAQ_VAL_ACQ_DDR_RESET                               2
#define DAQ_VAL_ACQ_DDR_IN_PROGRESS                         3
#define DAQ_VAL_ACQ_DDR_CAN_READ                            4


#define DAQ_VAL_CLOCK_INTERNAL								0//内时钟
#define DAQ_VAL_CLOCK_MAINBOARD								1//背板时钟
#define DAQ_VAL_NF_REJECT									0//无带宽抑制

// DAQ
// Attribute
#define DAQ_ATTR_DEVICE_HANDLE				IVI_CLASS_ATTR_BASE + 1000
#define DAQ_ATTR_DEVICE_CHANNEL             IVI_CLASS_ATTR_BASE + 1001


/************************************************************************/
/* Instrument LxiSync Attribute Definitions                             */
/************************************************************************/

/*======Arm Attributes======*/
#define DAQ_ATTR_IVILXISYNC_ARM_COUNT						IVILXISYNC_ATTR_BASE + 21
#define DAQ_ATTR_IVILXISYNC_ARM_DELAY						IVILXISYNC_ATTR_BASE + 8
/*======Arm Alarm Attributes======*/
#define DAQ_ATTR_IVILXISYNC_ARM_ALARM_COUNT					IVILXISYNC_ATTR_BASE + 1
#define DAQ_ATTR_IVILXISYNC_ARM_ALARM_ENABLED				IVILXISYNC_ATTR_BASE + 2
#define DAQ_ATTR_IVILXISYNC_ARM_ALARM_PERIOD				IVILXISYNC_ATTR_BASE + 3
#define DAQ_ATTR_IVILXISYNC_ARM_ALARM_REPEAT_COUNT			IVILXISYNC_ATTR_BASE + 4
#define DAQ_ATTR_IVILXISYNC_ARM_ALARM_TIME_SECONDS			IVILXISYNC_ATTR_BASE + 6
#define DAQ_ATTR_IVILXISYNC_ARM_ALARM_TIME_FRACTION			IVILXISYNC_ATTR_BASE + 5
/*======Arm Source Attributes======*/
#define DAQ_ATTR_IVILXISYNC_ARM_SOURCE_COUNT				IVILXISYNC_ATTR_BASE + 9
#define DAQ_ATTR_IVILXISYNC_ARM_SOURCE_DETECTION			IVILXISYNC_ATTR_BASE + 10
#define DAQ_ATTR_IVILXISYNC_ARM_SOURCE_ENABLED				IVILXISYNC_ATTR_BASE + 11
#define DAQ_ATTR_IVILXISYNC_ARM_SOURCE_OR_ENABLED			IVILXISYNC_ATTR_BASE + 14
#define DAQ_ATTR_IVILXISYNC_ARM_SOURCE_EVENTID				IVILXISYNC_ATTR_BASE + 12
#define DAQ_ATTR_IVILXISYNC_ARM_SOURCE_FILTER				IVILXISYNC_ATTR_BASE + 13
/*======Trigger Attributes======*/
#define DAQ_ATTR_IVILXISYNC_TRIGGER_COUNT					IVILXISYNC_ATTR_BASE + 21
#define DAQ_ATTR_IVILXISYNC_TRIGGER_SOURCE					IVILXISYNC_ATTR_BASE + 22
/*======Trigger Alarm Attributes======*/
#define DAQ_ATTR_IVILXISYNC_TRIGGER_ALARM_COUNT				IVILXISYNC_ATTR_BASE + 15
#define DAQ_ATTR_IVILXISYNC_TRIGGER_ALARM_ENABLED			IVILXISYNC_ATTR_BASE + 16
#define DAQ_ATTR_IVILXISYNC_TRIGGER_ALARM_PERIOD			IVILXISYNC_ATTR_BASE + 17
#define DAQ_ATTR_IVILXISYNC_TRIGGER_ALARM_REPEAT_COUNT		IVILXISYNC_ATTR_BASE + 18
#define DAQ_ATTR_IVILXISYNC_TRIGGER_ALARM_TIME_SECONDS		IVILXISYNC_ATTR_BASE + 20
#define DAQ_ATTR_IVILXISYNC_TRIGGER_ALARM_TIME_FRACTION		IVILXISYNC_ATTR_BASE + 19
/*======Trigger Source Attributes======*/
#define DAQ_ATTR_IVILXISYNC_TRIGGER_SOURCE_COUNT			IVILXISYNC_ATTR_BASE + 23
#define DAQ_ATTR_IVILXISYNC_TRIGGER_SOURCE_DELAY			IVILXISYNC_ATTR_BASE + 24
#define DAQ_ATTR_IVILXISYNC_TRIGGER_SOURCE_DETECTION		IVILXISYNC_ATTR_BASE + 25
#define DAQ_ATTR_IVILXISYNC_TRIGGER_SOURCE_EVENTID			IVILXISYNC_ATTR_BASE + 26
#define DAQ_ATTR_IVILXISYNC_TRIGGER_SOURCE_FILTER			IVILXISYNC_ATTR_BASE + 27
/*======Event Attributes======*/
#define DAQ_ATTR_IVILXISYNC_EVENT_COUNT						IVILXISYNC_ATTR_BASE + 28
#define DAQ_ATTR_IVILXISYNC_EVENT_WIRED_OR_BIAS_MODE		IVILXISYNC_ATTR_BASE + 33
#define DAQ_ATTR_IVILXISYNC_EVENT_DESTINATION_PATH			IVILXISYNC_ATTR_BASE + 29
#define DAQ_ATTR_IVILXISYNC_EVENT_DRIVE_MODE				IVILXISYNC_ATTR_BASE + 30
#define DAQ_ATTR_IVILXISYNC_EVENT_SLOPE						IVILXISYNC_ATTR_BASE + 31
#define DAQ_ATTR_IVILXISYNC_EVENT_SOURCE					IVILXISYNC_ATTR_BASE + 32
/*======Event Log Attributes======*/
#define DAQ_ATTR_IVILXISYNC_EVENT_LOG_ENABLED				IVILXISYNC_ATTR_BASE + 34
#define DAQ_ATTR_IVILXISYNC_EVENT_LOG_ENTRY_COUNT			IVILXISYNC_ATTR_BASE + 35
/*======Time Attributes======*/
#define DAQ_ATTR_IVILXISYNC_IS_TIME_MASTER					IVILXISYNC_ATTR_BASE + 36
#define DAQ_ATTR_IVILXISYNC_IS_TIME_SYNCHRONIZED			IVILXISYNC_ATTR_BASE + 37

/************************************************************************/
/* Instrument LxiSync Attribute Value Definitions                       */
/************************************************************************/
#define DAQ_VAL_IVILXISYNC_REPEAT_CONTINUOUS				0
#define DAQ_VAL_IVILXISYNC_DETECTION_RISE					0
#define DAQ_VAL_IVILXISYNC_DETECTION_FALL					1
#define DAQ_VAL_IVILXISYNC_DETECTION_HIGH					2
#define DAQ_VAL_IVILXISYNC_DETECTION_LOW					3
#define DAQ_VAL_IVILXISYNC_EVENT_DRIVEN						0
#define DAQ_VAL_IVILXISYNC_EVENT_OFF						1
#define DAQ_VAL_IVILXISYNC_EVENT_WIREDOR					2
#define DAQ_VAL_IVILXISYNC_SLOPE_RISE						0
#define DAQ_VAL_IVILXISYNC_SLOPE_FALL						1

/************************************************************************/
/* Base Error and Completion Code Value Definitions                     */
/************************************************************************/
#define IVI_INHERENT_ERROR_BASE									0xBFFA0000
#define IVI_INHERENT_WARN_BASE									0x3FFA0000
#define IVI_LXISYNC_ERROR_BASE									0xBFFA3000
#define IVI_LXISYNC_WARN_BASE									0x3FFA3000
#define IVI_SPECIFIC_ERROR_BASE									0xBFFA4000
#define IVI_SPECIFIC_WARN_BASE									0x3FFA4000
#define IVI_CLASS_ERROR_BASE									0xBFFA2000
#define IVI_CLASS_WARN_BASE										0x3FFA2000
#define IVI_SHARED_COMPONENT_ERROR_BASE							0xBFFA1000
#define IVI_SHARED_COMPONENT_WARN_BASE							0x3FFA1000
#define IVI_VENDOR_SPECIFIC_ERROR_BASE							0xBFFA6000
#define IVI_VENDOR_SPECIFIC_WARN_BASE							0x3FFA6000

/************************************************************************/
/* Inherent Error and Completion Code Value Definitions                 */
/************************************************************************/
#define IVI_ERROR_CANNOT_RECOVER								IVI_INHERENT_ERROR_BASE + 0x00
#define IVI_ERROR_INSTRUMENT_STATUS								IVI_INHERENT_ERROR_BASE + 0x01
#define IVI_ERROR_CANNOT_OPEN_FILE								IVI_INHERENT_ERROR_BASE + 0x02
#define IVI_ERROR_READING_FILE									IVI_INHERENT_ERROR_BASE + 0x03
#define IVI_ERROR_WRITING_FILE									IVI_INHERENT_ERROR_BASE + 0x04
#define IVI_ERROR_INVALID_PATHNAME								IVI_INHERENT_ERROR_BASE + 0x0B
#define IVI_ERROR_INVALID_ATTRIBUTE								IVI_INHERENT_ERROR_BASE + 0x0C
#define IVI_ERROR_ATTR_NOT_WRITEABLE							IVI_INHERENT_ERROR_BASE + 0x0D
#define IVI_ERROR_ATTR_NOT_READABLE								IVI_INHERENT_ERROR_BASE + 0x0E
#define IVI_ERROR_INVALID_VALUE									IVI_INHERENT_ERROR_BASE + 0x10
#define IVI_ERROR_FUNCTION_NOT_SUPPORTED						IVI_INHERENT_ERROR_BASE + 0x11
#define IVI_ERROR_ATTRIBUTE_NOT_SUPPORTED						IVI_INHERENT_ERROR_BASE + 0x12
#define IVI_ERROR_VALUE_NOT_SUPPORTED							IVI_INHERENT_ERROR_BASE + 0x13
#define IVI_ERROR_TYPES_DO_NOT_MATCH							IVI_INHERENT_ERROR_BASE + 0x15
#define IVI_ERROR_NOT_INITIALIZED								IVI_INHERENT_ERROR_BASE + 0x1D
#define IVI_ERROR_UNKNOWN_CHANNEL_NAME							IVI_INHERENT_ERROR_BASE + 0x20
#define IVI_ERROR_TOO_MANY_OPEN_FILES							IVI_INHERENT_ERROR_BASE + 0x23
#define IVI_ERROR_CHANNEL_NAME_REQUIRED							IVI_INHERENT_ERROR_BASE + 0x44
#define IVI_ERROR_CHANNEL_NAME_NOT_ALLOWED						IVI_INHERENT_ERROR_BASE + 0x45
#define IVI_ERROR_MISSING_OPTION_NAME							IVI_INHERENT_ERROR_BASE + 0x49
#define IVI_ERROR_MISSING_OPTION_VALUE							IVI_INHERENT_ERROR_BASE + 0x4A
#define IVI_ERROR_BAD_OPTION_NAME								IVI_INHERENT_ERROR_BASE + 0x4B
#define IVI_ERROR_BAD_OPTION_VALUE								IVI_INHERENT_ERROR_BASE + 0x4C
#define IVI_ERROR_OUT_OF_MEMORY									IVI_INHERENT_ERROR_BASE + 0x56
#define IVI_ERROR_OPERATION_PENDING								IVI_INHERENT_ERROR_BASE + 0x57
#define IVI_ERROR_NULL_POINTER									IVI_INHERENT_ERROR_BASE + 0x58
#define IVI_ERROR_UNEXPECTED_RESPONSE							IVI_INHERENT_ERROR_BASE + 0x59
#define IVI_ERROR_FILE_NOT_FOUND								IVI_INHERENT_ERROR_BASE + 0x5B
#define IVI_ERROR_INVALID_FILE_FORMAT							IVI_INHERENT_ERROR_BASE + 0x5C
#define IVI_ERROR_STATUS_NOT_AVAILABLE							IVI_INHERENT_ERROR_BASE + 0x5D
#define IVI_ERROR_ID_QUERY_FAILED								IVI_INHERENT_ERROR_BASE + 0x5E
#define IVI_ERROR_RESET_FAILED									IVI_INHERENT_ERROR_BASE + 0x5F
#define IVI_ERROR_RESOURCE_UNKNOWN								IVI_INHERENT_ERROR_BASE + 0x60
#define IVI_ERROR_ALREADY_INITIALIZED							IVI_INHERENT_ERROR_BASE + 0x61
#define IVI_ERROR_CANNOT_CHANGE_SIMULATION_STATE				IVI_INHERENT_ERROR_BASE + 0x62
#define IVI_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR			IVI_INHERENT_ERROR_BASE + 0x63
#define IVI_ERROR_INVALID_RANGE_IN_SELECTOR						IVI_INHERENT_ERROR_BASE + 0x64
#define IVI_ERROR_UNKNOWN_NAME_IN_SELECTOR						IVI_INHERENT_ERROR_BASE + 0x65
#define IVI_ERROR_BADLY_FORMED_SELECTOR							IVI_INHERENT_ERROR_BASE + 0x66
#define IVI_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER					IVI_INHERENT_ERROR_BASE + 0x67
#define IVI_WARN_NSUP_ID_QUERY									IVI_INHERENT_WARN_BASE + 0x65
#define IVI_WARN_NSUP_RESET										IVI_INHERENT_WARN_BASE + 0x66
#define IVI_WARN_NSUP_SELF_TEST									IVI_INHERENT_WARN_BASE + 0x67
#define IVI_WARN_NSUP_ERROR_QUERY								IVI_INHERENT_WARN_BASE + 0x68
#define IVI_WARN_NSUP_REV_QUERY									IVI_INHERENT_WARN_BASE + 0x69

/************************************************************************/
/* IviScope Error and Completion Code Value Definitions					*/
/************************************************************************/
#define DAQ_WARN_INVALID_WFM_ELEMENT						IVI_CLASS_WARN_BASE  + 1
#define DAQ_ERROR_CHANNEL_NOT_ENABLED						IVI_CLASS_ERROR_BASE + 1
#define DAQ_ERROR_UNABLE_TO_PERFORM_MEASUREMENT				IVI_CLASS_ERROR_BASE + 2
#define DAQ_ERROR_MAX_TIME_EXCEEDED							IVI_CLASS_ERROR_BASE + 3
#define DAQ_ERROR_INVALID_ACQ_TYPE							IVI_CLASS_ERROR_BASE + 4

/************************************************************************/
#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" { 
#endif	

	ViStatus _VI_FUNC DAQ_init(ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViSession *Vi);
	ViStatus _VI_FUNC DAQ_InitWithOptions(ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViConstString OptionsString, ViSession *Vi);
	ViStatus _VI_FUNC DAQ_close(ViSession Vi);
	ViStatus _VI_FUNC DAQ_ConfigureAcquisitionType(ViSession Vi, ViInt32 AcquisitionType);
	ViStatus _VI_FUNC DAQ_ConfigureAcquisitionRecord(ViSession Vi, ViReal64 TimePerRecord, ViInt32 MinNumPts, ViReal64 AcquisitionStartTime);
	ViStatus _VI_FUNC DAQ_ConfigureChannel(ViSession Vi, ViConstString Channel,	ViReal64 Range,	ViReal64 Offset, ViInt32 Coupling, ViReal64 ProbeAttenuation, ViBoolean Enabled);
	ViStatus _VI_FUNC DAQ_ConfigureTrigger(ViSession Vi, ViInt32 TriggerType, ViReal64 Holdoff);
	ViStatus _VI_FUNC DAQ_ConfigureEdgeTriggerSource(ViSession Vi, ViConstString Source, ViReal64 Level, ViInt32 Slope);
	ViStatus _VI_FUNC DAQ_ConfigureTriggerModifier(ViSession Vi, ViInt32 TriggerModifier);
	ViStatus _VI_FUNC DAQ_SampleRate(ViSession Vi, ViReal64 *SampleRate);
	ViStatus _VI_FUNC DAQ_InitiateAcquisition(ViSession Vi);
	ViStatus _VI_FUNC DAQ_AcquisitionStatus(ViSession Vi, ViInt32 *Status);
	ViStatus _VI_FUNC DAQ_FetchWaveform(ViSession Vi, ViConstString Channel, ViInt32 WaveformSize, ViReal64 WaveformArray[], ViInt32 *ActualPoints, ViReal64 *InitialX, ViReal64 *XIncrement);
	ViStatus _VI_FUNC DAQ_FetchMinMaxWaveform(ViSession Vi, ViConstString Channel, ViInt32 WaveformSize, ViReal64 MinWaveform[], ViReal64 MaxWaveform[], ViInt32 *ActualPoints, ViReal64 *InitialX, ViReal64 *XIncrement);
	ViStatus _VI_FUNC DAQ_FetchWholeWaveform(ViSession Vi, ViConstString Channel, ViInt32 WaveformSize, ViByte WaveformArray[]);
	ViStatus _VI_FUNC DAQ_FetchWaveformMeasurement(ViSession Vi, ViConstString Channel,	ViInt32 MeasFunction, ViReal64 *Measurement);
	ViStatus _VI_FUNC DAQ_Abort(ViSession Vi);	
	ViStatus _VI_FUNC DAQ_ResetAcquisition(ViSession Vi);

    // 配置系统四个显示通道的通道名和句柄（Vi = NULL）
    ViStatus _VI_FUNC DAQ_SetAttributeViString(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViConstString AttributeValue);
	ViStatus _VI_FUNC DAQ_SetAttributeViSession(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession AttributeValue);

	// 配置存储深度属性
	ViStatus _VI_FUNC DAQ_SetAttributeViInt32(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValue);
#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif

#endif // !defined(AFX_DAQ_PLXDLL_H__5D787C11_9A53_4B53_BAAF_CAE9E22D6BB4__INCLUDED_)