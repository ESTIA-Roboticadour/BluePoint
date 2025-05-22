//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2023-2025 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------

/*!
\file
\brief A parameter class containing all parameters as members that are available for daA2448-70uc

Sources:
daA2448-70uc p=du1_imx548c/s=r/v=1.0.2/i=6515.14/h=61c0643
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------

#ifndef BASLER_PYLON_BASLERCAMERACAMERAPARAMS_H
#define BASLER_PYLON_BASLERCAMERACAMERAPARAMS_H

#pragma once

// common parameter types
#include <pylon/ParameterIncludes.h>
#include <pylon/EnumParameterT.h>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4250 ) // warning C4250: 'Pylon::CXYZParameter': inherits 'Pylon::CParameter::Pylon::CParameter::ZYX' via dominance
#endif

//! The namespace containing the a control interface and related enumeration types for daA2448-70uc
namespace Pylon
{
namespace BaslerCameraCameraParams_Params
{
    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
    //! Valid values for AcquisitionMode
    enum AcquisitionModeEnums
    {
        AcquisitionMode_Continuous,  //!< The acquisition mode is set to Continuous - Applies to: daA2448-70uc
        AcquisitionMode_SingleFrame  //!< The acquisition mode is set to Single Frame - Applies to: daA2448-70uc
    };

    //! Valid values for AcquisitionStatusSelector
    enum AcquisitionStatusSelectorEnums
    {
        AcquisitionStatusSelector_AcquisitionActive,  //!< A check determines whether the camera is currently acquiring one or multiple frames - Applies to: daA2448-70uc
        AcquisitionStatusSelector_ExposureActive,  //!< A check determines whether the camera is currently exposing a frame - Applies to: daA2448-70uc
        AcquisitionStatusSelector_ExposureTriggerWait,  //!< A check determines whether the camera is currently waiting for an Exposure Start trigger signal - Applies to: daA2448-70uc
        AcquisitionStatusSelector_FrameBurstActive,  //!< A check determines whether the camera is currently doing a frame burst of one or many frames - Applies to: daA2448-70uc
        AcquisitionStatusSelector_FrameBurstTriggerWait,  //!< A check determines whether the camera is currently waiting for a frame burst trigger - Applies to: daA2448-70uc
        AcquisitionStatusSelector_FrameTriggerWait  //!< A check determines whether the camera is currently waiting for a frame trigger - Applies to: daA2448-70uc
    };

    //! Valid values for AutoFunctionProfile
    enum AutoFunctionProfileEnums
    {
        AutoFunctionProfile_MinimizeExposureTime,  //!< Exposure time is kept as low as possible - Applies to: daA2448-70uc
        AutoFunctionProfile_MinimizeGain  //!< Gain is kept as low as possible - Applies to: daA2448-70uc
    };

    //! Valid values for AutoFunctionROISelector
    enum AutoFunctionROISelectorEnums
    {
        AutoFunctionROISelector_ROI1,  //!< Auto function ROI 1 can be configured - Applies to: daA2448-70uc
        AutoFunctionROISelector_ROI2  //!< Auto function ROI 2 can be configured - Applies to: daA2448-70uc
    };

    //! Valid values for BalanceRatioSelector
    enum BalanceRatioSelectorEnums
    {
        BalanceRatioSelector_Blue,  //!< Balance ratio is applied to the blue channel - Applies to: daA2448-70uc
        BalanceRatioSelector_Green,  //!< Balance ratio is applied to the green channel - Applies to: daA2448-70uc
        BalanceRatioSelector_Red  //!< Balance ratio is applied to the red channel - Applies to: daA2448-70uc
    };

    //! Valid values for BalanceWhiteAuto
    enum BalanceWhiteAutoEnums
    {
        BalanceWhiteAuto_Continuous,  //!< White balance is adjusted continuously while images are being acquired - Applies to: daA2448-70uc
        BalanceWhiteAuto_Off,  //!< The Balance White Auto auto function is disabled - Applies to: daA2448-70uc
        BalanceWhiteAuto_Once  //!< White balance is adjusted automatically to reach the specified target value - Applies to: daA2448-70uc
    };

    //! Valid values for BslAcquisitionBurstMode
    enum BslAcquisitionBurstModeEnums
    {
        BslAcquisitionBurstMode_HighSpeed,  //!< The High Speed burst mode is enabled - Applies to: daA2448-70uc
        BslAcquisitionBurstMode_Standard  //!< The Standard burst mode is enabled - Applies to: daA2448-70uc
    };

    //! Valid values for BslAcquisitionStopMode
    enum BslAcquisitionStopModeEnums
    {
        BslAcquisitionStopMode_AbortExposure,  //!< Acquisition Stop commands abort exposure - Applies to: daA2448-70uc
        BslAcquisitionStopMode_CompleteExposure  //!< Acquisition Stop commands allow the exposure to be completed - Applies to: daA2448-70uc
    };

    //! Valid values for BslChunkAutoBrightnessStatus
    enum BslChunkAutoBrightnessStatusEnums
    {
        BslChunkAutoBrightnessStatus_Todo  //!< TODO - Applies to: daA2448-70uc
    };

    //! Valid values for BslChunkTimestampSelector
    enum BslChunkTimestampSelectorEnums
    {
        BslChunkTimestampSelector_ExposureEnd,  //!< The Chunk Timestamp Value parameter indicates when exposure of the current image ended - Applies to: daA2448-70uc
        BslChunkTimestampSelector_ExposureStart,  //!< The Chunk Timestamp Value parameter indicates when exposure of the current image started - Applies to: daA2448-70uc
        BslChunkTimestampSelector_FrameStart  //!< The Chunk Timestamp Value parameter indicates when acquisition of the current image started - Applies to: daA2448-70uc
    };

    //! Valid values for BslColorSpace
    enum BslColorSpaceEnums
    {
        BslColorSpace_Off,  //!< No additional gamma correction value is applied - Applies to: daA2448-70uc
        BslColorSpace_sRgb  //!< The color space is set to sRGB - Applies to: daA2448-70uc
    };

    //! Valid values for BslContrastMode
    enum BslContrastModeEnums
    {
        BslContrastMode_Linear,  //!< The camera uses a linear function to adjust the contrast - Applies to: daA2448-70uc
        BslContrastMode_SCurve  //!< The camera uses an S-curve function to adjust the contrast - Applies to: daA2448-70uc
    };

    //! Valid values for BslDefectPixelCorrectionMode
    enum BslDefectPixelCorrectionModeEnums
    {
        BslDefectPixelCorrectionMode_Off,  //!< Defect pixel correction is disabled - Applies to: daA2448-70uc
        BslDefectPixelCorrectionMode_On,  //!< Defect pixel correction is enabled - Applies to: daA2448-70uc
        BslDefectPixelCorrectionMode_StaticOnly  //!< Only static defect pixel correction is enabled - Applies to: daA2448-70uc
    };

    //! Valid values for BslLightSourcePreset
    enum BslLightSourcePresetEnums
    {
        BslLightSourcePreset_Daylight5000K,  //!< The light source preset for image acquisitions with daylight of 5000 K is selected - Applies to: daA2448-70uc
        BslLightSourcePreset_Daylight6500K,  //!< The light source preset for image acquisitions with daylight of 6500 K is selected - Applies to: daA2448-70uc
        BslLightSourcePreset_FactoryLED6000K,  //!< The light source preset for image acquisitions with LED light is selected - Applies to: daA2448-70uc
        BslLightSourcePreset_Off,  //!< No light source preset is selected - Applies to: daA2448-70uc
        BslLightSourcePreset_Tungsten  //!< The light source preset for image acquisitions with tungsten incandescent light is selected - Applies to: daA2448-70uc
    };

    //! Valid values for BslLightSourcePresetFeatureSelector
    enum BslLightSourcePresetFeatureSelectorEnums
    {
        BslLightSourcePresetFeatureSelector_ColorAdjustment,  //!< Adjustment of the Color Adjustment feature can be enabled or disabled - Applies to: daA2448-70uc
        BslLightSourcePresetFeatureSelector_ColorTransformation,  //!< Adjustment of the Color Transformation feature can be enabled or disabled - Applies to: daA2448-70uc
        BslLightSourcePresetFeatureSelector_WhiteBalance  //!< Adjustment of the Balance White feature can be enabled or disabled - Applies to: daA2448-70uc
    };

    //! Valid values for BslLineConnection
    enum BslLineConnectionEnums
    {
        BslLineConnection_ConnectionOff,  //!< No connection signal is set for the currently selected line - Applies to: daA2448-70uc
        BslLineConnection_TwiScl,  //!< The TWI SCL signal is set for the currently selected line - Applies to: daA2448-70uc
        BslLineConnection_TwiSda  //!< The TWI SDA signal is set for the currently selected line - Applies to: daA2448-70uc
    };

    //! Valid values for BslSensorBitDepth
    enum BslSensorBitDepthEnums
    {
        BslSensorBitDepth_Bpp10,  //!< The sensor bit depth is set to 10 bits per pixel - Applies to: daA2448-70uc
        BslSensorBitDepth_Bpp12,  //!< The sensor bit depth is set to 12 bits per pixel - Applies to: daA2448-70uc
        BslSensorBitDepth_Bpp8  //!< The sensor bit depth is set to 8 bits per pixel - Applies to: daA2448-70uc
    };

    //! Valid values for BslSensorBitDepthMode
    enum BslSensorBitDepthModeEnums
    {
        BslSensorBitDepthMode_Auto,  //!< The sensor bit depth mode is set to Auto - Applies to: daA2448-70uc
        BslSensorBitDepthMode_Manual  //!< The sensor bit depth mode is set to Manual - Applies to: daA2448-70uc
    };

    //! Valid values for BslSensorState
    enum BslSensorStateEnums
    {
        BslSensorState_Off,  //!< The sensor power is switched off - Applies to: daA2448-70uc
        BslSensorState_On,  //!< The sensor power is switched on - Applies to: daA2448-70uc
        BslSensorState_Standby  //!< The sensor is in standby mode - Applies to: daA2448-70uc
    };

    //! Valid values for BslTemperatureStatus
    enum BslTemperatureStatusEnums
    {
        BslTemperatureStatus_Critical,  //!< The temperature is close to or at the allowed maximum  Provide cooling - Applies to: daA2448-70uc
        BslTemperatureStatus_Error,  //!< The temperature is above the allowed maximum  Provide cooling immediately - Applies to: daA2448-70uc
        BslTemperatureStatus_Ok  //!< The temperature is within the normal operating temperature range - Applies to: daA2448-70uc
    };

    //! Valid values for BslTwiBitrate
    enum BslTwiBitrateEnums
    {
        BslTwiBitrate_Bitrate100kbps,  //!< The bit rate is set to 100000 bits per second - Applies to: daA2448-70uc
        BslTwiBitrate_Bitrate10kbps,  //!< The bit rate is set to 10000 bits per second - Applies to: daA2448-70uc
        BslTwiBitrate_Bitrate200kbps,  //!< The bit rate is set to 200000 bits per second - Applies to: daA2448-70uc
        BslTwiBitrate_Bitrate20kbps,  //!< The bit rate is set to 20000 bits per second - Applies to: daA2448-70uc
        BslTwiBitrate_Bitrate400kbps,  //!< The bit rate is set to 400000 bits per second - Applies to: daA2448-70uc
        BslTwiBitrate_Bitrate50kbps  //!< The bit rate is set to 50000 bits per second - Applies to: daA2448-70uc
    };

    //! Valid values for BslTwiTransferStatus
    enum BslTwiTransferStatusEnums
    {
        BslTwiTransferStatus_NakAddress,  //!< The last transfer failed because a NAK was received when sending the address - Applies to: daA2448-70uc
        BslTwiTransferStatus_NakData,  //!< The last transfer failed because a NAK was received when sending data - Applies to: daA2448-70uc
        BslTwiTransferStatus_Pending,  //!< A transfer is pending - Applies to: daA2448-70uc
        BslTwiTransferStatus_Success  //!< The last transfer was successful - Applies to: daA2448-70uc
    };

    //! Valid values for BslUSBPowerSource
    enum BslUSBPowerSourceEnums
    {
        BslUSBPowerSource_Aux,  //!< Power is supplied via the I/O connector - Applies to: daA2448-70uc
        BslUSBPowerSource_Bus  //!< Power is supplied via the bus - Applies to: daA2448-70uc
    };

    //! Valid values for BslUSBSpeedMode
    enum BslUSBSpeedModeEnums
    {
        BslUSBSpeedMode_FullSpeed,  //!< The USB port is operating at Full Speed - Applies to: daA2448-70uc
        BslUSBSpeedMode_HighSpeed,  //!< The USB port is operating at High Speed - Applies to: daA2448-70uc
        BslUSBSpeedMode_LowSpeed,  //!< The USB port is operating at Low Speed - Applies to: daA2448-70uc
        BslUSBSpeedMode_SuperSpeed  //!< The USB port is operating at SuperSpeed - Applies to: daA2448-70uc
    };

    //! Valid values for ChunkCounterSelector
    enum ChunkCounterSelectorEnums
    {
        ChunkCounterSelector_Counter1,  //!< Chunk data can be retrieved from counter 1 - Applies to: daA2448-70uc
        ChunkCounterSelector_Counter2  //!< Chunk data can be retrieved from counter 2 - Applies to: daA2448-70uc
    };

    //! Valid values for ChunkSelector
    enum ChunkSelectorEnums
    {
        ChunkSelector_AutoBrightnessStatus,  //!< The Auto Brightness Status chunk can be enabled - Applies to: daA2448-70uc
        ChunkSelector_CounterValue,  //!< The Counter Value chunk can be enabled - Applies to: daA2448-70uc
        ChunkSelector_ExposureTime,  //!< The Exposure Time chunk can be enabled - Applies to: daA2448-70uc
        ChunkSelector_FrameID,  //!< The Frame ID chunk can be enabled - Applies to: daA2448-70uc
        ChunkSelector_Gain,  //!< The Gain chunk can be enabled - Applies to: daA2448-70uc
        ChunkSelector_LineStatusAll,  //!< The Line Status All chunk can be enabled - Applies to: daA2448-70uc
        ChunkSelector_PayloadCRC16,  //!< The CRC Checksum chunk can be enabled - Applies to: daA2448-70uc
        ChunkSelector_Timestamp  //!< The Timestamp chunk can be enabled - Applies to: daA2448-70uc
    };

    //! Valid values for CounterEventActivation
    enum CounterEventActivationEnums
    {
        CounterEventActivation_Todo  //!< TODO - Applies to: daA2448-70uc
    };

    //! Valid values for CounterEventSource
    enum CounterEventSourceEnums
    {
        CounterEventSource_AcquisitionActive,  //!< The selected counter counts the number of Acquisition Active signals - Applies to: daA2448-70uc
        CounterEventSource_Counter1Active,  //!< The selected counter counts the number of Counter 1 Active signals - Applies to: daA2448-70uc
        CounterEventSource_Counter1End,  //!< The selected counter counts the number of Counter 1 End signals - Applies to: daA2448-70uc
        CounterEventSource_Counter1Start,  //!< The selected counter counts the number of Counter 1 Start signals - Applies to: daA2448-70uc
        CounterEventSource_Counter2Active,  //!< The selected counter counts the number of Counter 2 Active signals - Applies to: daA2448-70uc
        CounterEventSource_Counter2End,  //!< The selected counter counts the number of Counter 2 End signals - Applies to: daA2448-70uc
        CounterEventSource_Counter2Start,  //!< The selected counter counts the number of Counter 2 Start signals - Applies to: daA2448-70uc
        CounterEventSource_ExposureActive,  //!< The selected counter counts the number of Exposure Active signals - Applies to: daA2448-70uc
        CounterEventSource_ExposureStart,  //!< The selected counter counts the number of Exposure Start signals - Applies to: daA2448-70uc
        CounterEventSource_ExposureTriggerWait,  //!< The selected counter counts the number of Exposure Trigger Wait signals - Applies to: daA2448-70uc
        CounterEventSource_FrameBurstActive,  //!< The selected counter counts the number of Frame Burst Active signals - Applies to: daA2448-70uc
        CounterEventSource_FrameBurstTriggerWait,  //!< The selected counter counts the number of Frame Burst Trigger Wait signals - Applies to: daA2448-70uc
        CounterEventSource_FrameTriggerWait,  //!< The selected counter counts the number of Frame Trigger Wait signals - Applies to: daA2448-70uc
        CounterEventSource_Line1,  //!< The selected counter counts the number of Line 1 signals - Applies to: daA2448-70uc
        CounterEventSource_Line2,  //!< The selected counter counts the number of Line 2 signals - Applies to: daA2448-70uc
        CounterEventSource_Line3,  //!< The selected counter counts the number of Line 3 signals - Applies to: daA2448-70uc
        CounterEventSource_Line4,  //!< The selected counter counts the number of Line 4 signals - Applies to: daA2448-70uc
        CounterEventSource_Off,  //!< The selected counter is disabled - Applies to: daA2448-70uc
        CounterEventSource_SoftwareSignal1,  //!< The selected counter counts the number of Software Signal 1 signals - Applies to: daA2448-70uc
        CounterEventSource_SoftwareSignal2,  //!< The selected counter counts the number of Software Signal 2 signals - Applies to: daA2448-70uc
        CounterEventSource_SoftwareSignal3,  //!< The selected counter counts the number of Software Signal 3 signals - Applies to: daA2448-70uc
        CounterEventSource_Timer1Active,  //!< The selected counter counts the number of Timer 1 Active signals - Applies to: daA2448-70uc
        CounterEventSource_Timer1End,  //!< The selected counter counts the number of Timer 1 End signals - Applies to: daA2448-70uc
        CounterEventSource_Timer2Active,  //!< The selected counter counts the number of Timer 2 Active signals - Applies to: daA2448-70uc
        CounterEventSource_Timer2End  //!< The selected counter counts the number of Timer 2 End signals - Applies to: daA2448-70uc
    };

    //! Valid values for CounterResetActivation
    enum CounterResetActivationEnums
    {
        CounterResetActivation_Todo  //!< TODO - Applies to: daA2448-70uc
    };

    //! Valid values for CounterResetSource
    enum CounterResetSourceEnums
    {
        CounterResetSource_AcquisitionActive,  //!< The selected counter can be reset by an Acquisition Active signal - Applies to: daA2448-70uc
        CounterResetSource_Counter1Active,  //!< The selected counter can be reset by a Counter 1 Active signal - Applies to: daA2448-70uc
        CounterResetSource_Counter1End,  //!< The selected counter can be reset by a Counter End 1 signal - Applies to: daA2448-70uc
        CounterResetSource_Counter1Start,  //!< The selected counter can be reset by a Counter 1 Start signal - Applies to: daA2448-70uc
        CounterResetSource_Counter2Active,  //!< The selected counter can be reset by a Counter 2 Active signal - Applies to: daA2448-70uc
        CounterResetSource_Counter2End,  //!< The selected counter can be reset by a Counter End 2 signal - Applies to: daA2448-70uc
        CounterResetSource_Counter2Start,  //!< The selected counter can be reset by a Counter 2 Start signal - Applies to: daA2448-70uc
        CounterResetSource_ExposureActive,  //!< The selected counter can be reset by an Exposure Active signal - Applies to: daA2448-70uc
        CounterResetSource_ExposureStart,  //!< The selected counter can be reset by an Exposure Start signal - Applies to: daA2448-70uc
        CounterResetSource_ExposureTriggerWait,  //!< The selected counter can be reset by an Exposure Trigger Wait signal - Applies to: daA2448-70uc
        CounterResetSource_FrameBurstActive,  //!< The selected counter can be reset by a Frame Burst Active signal - Applies to: daA2448-70uc
        CounterResetSource_FrameBurstTriggerWait,  //!< The selected counter can be reset by a Frame Burst Trigger Wait signal - Applies to: daA2448-70uc
        CounterResetSource_FrameTriggerWait,  //!< The selected counter can be reset by a Frame Trigger Wait signal - Applies to: daA2448-70uc
        CounterResetSource_Line1,  //!< The selected counter can be reset by a signal applied to Line 1 - Applies to: daA2448-70uc
        CounterResetSource_Line2,  //!< The selected counter can be reset by a signal applied to Line 2 - Applies to: daA2448-70uc
        CounterResetSource_Line3,  //!< The selected counter can be reset by a signal applied to Line 3 - Applies to: daA2448-70uc
        CounterResetSource_Line4,  //!< The selected counter can be reset by a signal applied to Line 4 - Applies to: daA2448-70uc
        CounterResetSource_Off,  //!< The counter reset is disabled - Applies to: daA2448-70uc
        CounterResetSource_SoftwareSignal1,  //!< The selected counter can be reset by a Software Signal 1 signal - Applies to: daA2448-70uc
        CounterResetSource_SoftwareSignal2,  //!< The selected counter can be reset by a Software Signal 2 signal - Applies to: daA2448-70uc
        CounterResetSource_SoftwareSignal3,  //!< The selected counter can be reset by a Software Signal 3 signal - Applies to: daA2448-70uc
        CounterResetSource_Timer1Active,  //!< The selected counter can be reset by a Timer 1 Active signal - Applies to: daA2448-70uc
        CounterResetSource_Timer1End,  //!< The selected counter can be reset by a Timer 1 End signal - Applies to: daA2448-70uc
        CounterResetSource_Timer2Active,  //!< The selected counter can be reset by a Timer 2 Active signal - Applies to: daA2448-70uc
        CounterResetSource_Timer2End  //!< The selected counter can be reset by a Timer 2 End signal - Applies to: daA2448-70uc
    };

    //! Valid values for CounterSelector
    enum CounterSelectorEnums
    {
        CounterSelector_Counter1,  //!< Counter 1 can be configured - Applies to: daA2448-70uc
        CounterSelector_Counter2  //!< Counter 2 can be configured - Applies to: daA2448-70uc
    };

    //! Valid values for CounterStatus
    enum CounterStatusEnums
    {
        CounterStatus_CounterActive,  //!< The counter is waiting to be increased by the selected event source or is currently counting - Applies to: daA2448-70uc
        CounterStatus_CounterCompleted,  //!< The counter has reached its maximum value defined by the Counter Duration parameter - Applies to: daA2448-70uc
        CounterStatus_CounterTriggerWait  //!< The counter is waiting to be started - Applies to: daA2448-70uc
    };

    //! Valid values for CounterTriggerActivation
    enum CounterTriggerActivationEnums
    {
        CounterTriggerActivation_Todo  //!< TODO - Applies to: daA2448-70uc
    };

    //! Valid values for CounterTriggerSource
    enum CounterTriggerSourceEnums
    {
        CounterTriggerSource_AcquisitionActive,  //!< The selected counter can be started by an Acquisition Active signal - Applies to: daA2448-70uc
        CounterTriggerSource_Counter1Active,  //!< The selected counter can be started by a Counter 1 Active signal - Applies to: daA2448-70uc
        CounterTriggerSource_Counter1End,  //!< The selected counter can be started by a Counter 1 End signal - Applies to: daA2448-70uc
        CounterTriggerSource_Counter1Start,  //!< The selected counter can be started by a Counter 1 Start signal - Applies to: daA2448-70uc
        CounterTriggerSource_Counter2Active,  //!< The selected counter can be started by a Counter 2 Active signal - Applies to: daA2448-70uc
        CounterTriggerSource_Counter2End,  //!< The selected counter can be started by a Counter 2 End signal - Applies to: daA2448-70uc
        CounterTriggerSource_Counter2Start,  //!< The selected counter can be started by a Counter 2 Start signal - Applies to: daA2448-70uc
        CounterTriggerSource_ExposureActive,  //!< The selected counter can be started by an Exposure Active signal - Applies to: daA2448-70uc
        CounterTriggerSource_ExposureStart,  //!< The selected counter can be started by an Exposure Start signal - Applies to: daA2448-70uc
        CounterTriggerSource_ExposureTriggerWait,  //!< The selected counter can be started by an Exposure Trigger Wait signal - Applies to: daA2448-70uc
        CounterTriggerSource_FrameBurstActive,  //!< The selected counter can be started by a Frame Burst Active signal - Applies to: daA2448-70uc
        CounterTriggerSource_FrameBurstTriggerWait,  //!< The selected counter can be started by a Frame Burst Trigger Wait signal - Applies to: daA2448-70uc
        CounterTriggerSource_FrameTriggerWait,  //!< The selected counter can be started by a Frame Trigger Wait signal - Applies to: daA2448-70uc
        CounterTriggerSource_Line1,  //!< The selected counter can be started by a Line 1 signal - Applies to: daA2448-70uc
        CounterTriggerSource_Line2,  //!< The selected counter can be started by a Line 2 signal - Applies to: daA2448-70uc
        CounterTriggerSource_Line3,  //!< The selected counter can be started by a Line 3 signal - Applies to: daA2448-70uc
        CounterTriggerSource_Line4,  //!< The selected counter can be started by a Line 4 signal - Applies to: daA2448-70uc
        CounterTriggerSource_Off,  //!< The selected counter is disabled and can't be started - Applies to: daA2448-70uc
        CounterTriggerSource_SoftwareSignal1,  //!< The selected counter can be started by a Software Signal 1 signal - Applies to: daA2448-70uc
        CounterTriggerSource_SoftwareSignal2,  //!< The selected counter can be started by a Software Signal 2 signal - Applies to: daA2448-70uc
        CounterTriggerSource_SoftwareSignal3,  //!< The selected counter can be started by a Software Signal 3 signal - Applies to: daA2448-70uc
        CounterTriggerSource_Timer1Active,  //!< The selected counter can be started by a Timer 1 Active signal - Applies to: daA2448-70uc
        CounterTriggerSource_Timer1End,  //!< The selected counter can be started by a Timer 1 End signal - Applies to: daA2448-70uc
        CounterTriggerSource_Timer2Active,  //!< The selected counter can be started by a Timer 2 Active signal - Applies to: daA2448-70uc
        CounterTriggerSource_Timer2End  //!< The selected counter can be started by a Timer 2 End signal - Applies to: daA2448-70uc
    };

    //! Valid values for DeviceCharacterSet
    enum DeviceCharacterSetEnums
    {
        DeviceCharacterSet_UTF8  //!< The strings of the device's bootstrap registers use the UTF-8 character set - Applies to: daA2448-70uc
    };

    //! Valid values for DeviceIndicatorMode
    enum DeviceIndicatorModeEnums
    {
        DeviceIndicatorMode_Active,  //!< The status LED of the camera is turned on - Applies to: daA2448-70uc
        DeviceIndicatorMode_ErrorStatus,  //!< The camera's status LED is inactive unless an error occurs - Applies to: daA2448-70uc
        DeviceIndicatorMode_Inactive  //!< The status LED of the camera is turned off - Applies to: daA2448-70uc
    };

    //! Valid values for DeviceLinkThroughputLimitMode
    enum DeviceLinkThroughputLimitModeEnums
    {
        DeviceLinkThroughputLimitMode_Off,  //!< The Device Link Throughput Limit parameter is disabled - Applies to: daA2448-70uc
        DeviceLinkThroughputLimitMode_On  //!< The Device Link Throughput Limit parameter is enabled - Applies to: daA2448-70uc
    };

    //! Valid values for DeviceRegistersEndianness
    enum DeviceRegistersEndiannessEnums
    {
        DeviceRegistersEndianness_Big,  //!< The endianness of the device's registers is big-endian - Applies to: daA2448-70uc
        DeviceRegistersEndianness_Little  //!< The endianness of the device's registers is little-endian - Applies to: daA2448-70uc
    };

    //! Valid values for DeviceScanType
    enum DeviceScanTypeEnums
    {
        DeviceScanType_Areascan,  //!< The camera has an area scan sensor - Applies to: daA2448-70uc
        DeviceScanType_Linescan  //!< The camera has a line scan sensor - Applies to: daA2448-70uc
    };

    //! Valid values for DeviceTLType
    enum DeviceTLTypeEnums
    {
        DeviceTLType_CoaXPress,  //!< The device provides a CoaXPress transport layer - Applies to: daA2448-70uc
        DeviceTLType_GigEVision,  //!< The device provides a GigE Vision transport layer - Applies to: daA2448-70uc
        DeviceTLType_USB3Vision  //!< The device provides a USB3 Vision transport layer - Applies to: daA2448-70uc
    };

    //! Valid values for DeviceTemperatureSelector
    enum DeviceTemperatureSelectorEnums
    {
        DeviceTemperatureSelector_FpgaCore,  //!< The temperature is measured on the FPGA board - Applies to: daA2448-70uc
        DeviceTemperatureSelector_Sensor  //!< The temperature is measured on the image sensor - Applies to: daA2448-70uc
    };

    //! Valid values for EventNotification
    enum EventNotificationEnums
    {
        EventNotification_Off,  //!< Event notifications are disabled - Applies to: daA2448-70uc
        EventNotification_On  //!< Event notifications are enabled - Applies to: daA2448-70uc
    };

    //! Valid values for EventSelector
    enum EventSelectorEnums
    {
        EventSelector_ExposureEnd,  //!< Event notifications for the Exposure End event can be enabled - Applies to: daA2448-70uc
        EventSelector_FrameStart,  //!< Event notifications for the Frame Start event can be enabled - Applies to: daA2448-70uc
        EventSelector_FrameTriggerMissed,  //!< Event notifications for the Frame Trigger Missed event can be enabled - Applies to: daA2448-70uc
        EventSelector_Overrun,  //!< Event notifications for the Overrun event can be enabled - Applies to: daA2448-70uc
        EventSelector_TemperatureStatusChanged,  //!< Event notifications for the Temperature Status Changed event can be enabled - Applies to: daA2448-70uc
        EventSelector_Test  //!< Event notifications for the Test event can be enabled - Applies to: daA2448-70uc
    };

    //! Valid values for EventTemperatureStatusChangedStatus
    enum EventTemperatureStatusChangedStatusEnums
    {
        EventTemperatureStatusChangedStatus_Todo  //!< TODO - Applies to: daA2448-70uc
    };

    //! Valid values for ExposureAuto
    enum ExposureAutoEnums
    {
        ExposureAuto_Continuous,  //!< The exposure time is adjusted continuously while images are being acquired - Applies to: daA2448-70uc
        ExposureAuto_Off,  //!< Automatic exposure time adjustment is disabled - Applies to: daA2448-70uc
        ExposureAuto_Once  //!< The exposure time is adjusted automatically to reach the specified target value - Applies to: daA2448-70uc
    };

    //! Valid values for ExposureMode
    enum ExposureModeEnums
    {
        ExposureMode_Timed,  //!< The exposure mode is set to Timed - Applies to: daA2448-70uc
        ExposureMode_TriggerControlled,  //!< The exposure mode is set to Trigger Controlled - Applies to: daA2448-70uc
        ExposureMode_TriggerWidth  //!< The exposure mode is set to Trigger Width - Applies to: daA2448-70uc
    };

    //! Valid values for FileOpenMode
    enum FileOpenModeEnums
    {
        FileOpenMode_Read,  //!< Files are opened in read-only mode - Applies to: daA2448-70uc
        FileOpenMode_Write  //!< Files are opened in write-only mode - Applies to: daA2448-70uc
    };

    //! Valid values for FileOperationSelector
    enum FileOperationSelectorEnums
    {
        FileOperationSelector_Close,  //!< The currently selected file can be closed - Applies to: daA2448-70uc
        FileOperationSelector_Open,  //!< The currently selected file can be opened - Applies to: daA2448-70uc
        FileOperationSelector_Read,  //!< The currently selected file can be read - Applies to: daA2448-70uc
        FileOperationSelector_Write  //!< The currently selected file can be written to - Applies to: daA2448-70uc
    };

    //! Valid values for FileOperationStatus
    enum FileOperationStatusEnums
    {
        FileOperationStatus_Failure,  //!< The file operation has failed - Applies to: daA2448-70uc
        FileOperationStatus_Success  //!< The file operation was successful - Applies to: daA2448-70uc
    };

    //! Valid values for FileSelector
    enum FileSelectorEnums
    {
        FileSelector_BootUpdate,  //!< The Boot Firmware Update file is selected - Applies to: daA2448-70uc
        FileSelector_BootUpdatePackage,  //!< The Boot Firmware Update Package file is selected - Applies to: daA2448-70uc
        FileSelector_FirmwareUpdate,  //!< The Firmware Update file is selected - Applies to: daA2448-70uc
        FileSelector_FirmwareUpdatePackage,  //!< The Firmware Update Package file is selected - Applies to: daA2448-70uc
        FileSelector_None,  //!< No file is selected - Applies to: daA2448-70uc
        FileSelector_UserData  //!< The User Data file is selected - Applies to: daA2448-70uc
    };

    //! Valid values for GainAuto
    enum GainAutoEnums
    {
        GainAuto_Continuous,  //!< The gain is adjusted continuously while images are being acquired - Applies to: daA2448-70uc
        GainAuto_Off,  //!< Automatic gain adjustment is disabled - Applies to: daA2448-70uc
        GainAuto_Once  //!< The gain is adjusted automatically to reach the specifed target value - Applies to: daA2448-70uc
    };

    //! Valid values for LineFormat
    enum LineFormatEnums
    {
        LineFormat_LVTTL,  //!< The line is currently accepting or sending LVTTL level signals - Applies to: daA2448-70uc
        LineFormat_OpenDrain,  //!< The output of the line is "open drain"/"open collector" - Applies to: daA2448-70uc
        LineFormat_OptoCoupled  //!< The line is opto-coupled - Applies to: daA2448-70uc
    };

    //! Valid values for LineMode
    enum LineModeEnums
    {
        LineMode_InOut,  //!< The selected physical line can be used to input and output an electrical signal - Applies to: daA2448-70uc
        LineMode_Input,  //!< The selected physical line can be used to input an electrical signal - Applies to: daA2448-70uc
        LineMode_Output  //!< The selected physical line can be used to output an electrical signal - Applies to: daA2448-70uc
    };

    //! Valid values for LineSelector
    enum LineSelectorEnums
    {
        LineSelector_Line1,  //!< Line 1 can be configured - Applies to: daA2448-70uc
        LineSelector_Line2,  //!< Line 2 can be configured - Applies to: daA2448-70uc
        LineSelector_Line3,  //!< Line 3 can be configured - Applies to: daA2448-70uc
        LineSelector_Line4  //!< Line 4 can be configured - Applies to: daA2448-70uc
    };

    //! Valid values for LineSource
    enum LineSourceEnums
    {
        LineSource_AcquisitionActive,  //!< The source signal for the currently selected line is set to Acquisition Active - Applies to: daA2448-70uc
        LineSource_Counter1Active,  //!< The source signal for the currently selected line is set to Counter 1 Active - Applies to: daA2448-70uc
        LineSource_Counter2Active,  //!< The source signal for the currently selected line is set to Counter 2 Active - Applies to: daA2448-70uc
        LineSource_ExposureActive,  //!< The source signal for the currently selected line is set to Exposure Active - Applies to: daA2448-70uc
        LineSource_ExposureTriggerWait,  //!< The source signal for the currently selected line is set to Exposure Trigger Wait - Applies to: daA2448-70uc
        LineSource_FrameBurstActive,  //!< The source signal for the currently selected line is set to Frame Burst Active - Applies to: daA2448-70uc
        LineSource_FrameBurstTriggerWait,  //!< The source signal for the currently selected line is set to Frame Burst Trigger Wait - Applies to: daA2448-70uc
        LineSource_FrameTriggerWait,  //!< The source signal for the currently selected line is set to Frame Trigger Wait - Applies to: daA2448-70uc
        LineSource_Off,  //!< No source signal is set for the currently selected line - Applies to: daA2448-70uc
        LineSource_Timer1Active,  //!< The source signal for the currently selected line is set to Timer 1 Active - Applies to: daA2448-70uc
        LineSource_Timer2Active,  //!< The source signal for the currently selected line is set to Timer 2 Active - Applies to: daA2448-70uc
        LineSource_UserOutput1,  //!< The source signal for the currently selected line is set to User Output 1 - Applies to: daA2448-70uc
        LineSource_UserOutput2,  //!< The source signal for the currently selected line is set to User Output 2 - Applies to: daA2448-70uc
        LineSource_UserOutput3,  //!< The source signal for the currently selected line is set to User Output 3 - Applies to: daA2448-70uc
        LineSource_UserOutput4  //!< The source signal for the currently selected line is set to User Output 4 - Applies to: daA2448-70uc
    };

    //! Valid values for PixelFormat
    enum PixelFormatEnums
    {
        PixelFormat_BGR8,  //!< The pixel format is set to BGR 8 - Applies to: daA2448-70uc
        PixelFormat_BayerBG10,  //!< The pixel format is set to Bayer BG 10 - Applies to: daA2448-70uc
        PixelFormat_BayerBG10p,  //!< The pixel format is set to Bayer BG 10p - Applies to: daA2448-70uc
        PixelFormat_BayerBG12,  //!< The pixel format is set to Bayer BG 12 - Applies to: daA2448-70uc
        PixelFormat_BayerBG12p,  //!< The pixel format is set to Bayer BG 12p - Applies to: daA2448-70uc
        PixelFormat_BayerBG8,  //!< The pixel format is set to Bayer BG 8 - Applies to: daA2448-70uc
        PixelFormat_BayerGB10,  //!< The pixel format is set to Bayer GB 10 - Applies to: daA2448-70uc
        PixelFormat_BayerGB10p,  //!< The pixel format is set to Bayer GB 10p - Applies to: daA2448-70uc
        PixelFormat_BayerGB12,  //!< The pixel format is set to Bayer GB 12 - Applies to: daA2448-70uc
        PixelFormat_BayerGB12p,  //!< The pixel format is set to Bayer GB 12p - Applies to: daA2448-70uc
        PixelFormat_BayerGB8,  //!< The pixel format is set to Bayer GB 8 - Applies to: daA2448-70uc
        PixelFormat_BayerGR10,  //!< The pixel format is set to Bayer GR 10 - Applies to: daA2448-70uc
        PixelFormat_BayerGR10p,  //!< The pixel format is set to Bayer GR 10p - Applies to: daA2448-70uc
        PixelFormat_BayerGR12,  //!< The pixel format is set to Bayer GR 12 - Applies to: daA2448-70uc
        PixelFormat_BayerGR12p,  //!< The pixel format is set to Bayer GR 12p - Applies to: daA2448-70uc
        PixelFormat_BayerGR8,  //!< The pixel format is set to Bayer GR 8 - Applies to: daA2448-70uc
        PixelFormat_BayerRG10,  //!< The pixel format is set to Bayer RG 10 - Applies to: daA2448-70uc
        PixelFormat_BayerRG10p,  //!< The pixel format is set to Bayer RG 10p - Applies to: daA2448-70uc
        PixelFormat_BayerRG12,  //!< The pixel format is set to Bayer RG 12 - Applies to: daA2448-70uc
        PixelFormat_BayerRG12p,  //!< The pixel format is set to Bayer RG 12p - Applies to: daA2448-70uc
        PixelFormat_BayerRG8,  //!< The pixel format is set to Bayer RG 8 - Applies to: daA2448-70uc
        PixelFormat_Mono10,  //!< The pixel format is set to Mono 10 - Applies to: daA2448-70uc
        PixelFormat_Mono10p,  //!< The pixel format is set to Mono 10p - Applies to: daA2448-70uc
        PixelFormat_Mono12,  //!< The pixel format is set to Mono 12 - Applies to: daA2448-70uc
        PixelFormat_Mono12p,  //!< The pixel format is set to Mono 12p - Applies to: daA2448-70uc
        PixelFormat_Mono8,  //!< The pixel format is set to Mono 8 - Applies to: daA2448-70uc
        PixelFormat_RGB8,  //!< The pixel format is set to RGB 8 - Applies to: daA2448-70uc
        PixelFormat_YCbCr422_8,  //!< The pixel format is set to YCbCr 422 - Applies to: daA2448-70uc
        PixelFormat_YUV422_8  //!< The pixel format is set to YUV 4:2:2 8 bit packed - Applies to: daA2448-70uc
    };

    //! Valid values for PixelSize
    enum PixelSizeEnums
    {
        PixelSize_Bpp10,  //!< The pixel depth in the acquired images is 10 bits per pixel - Applies to: daA2448-70uc
        PixelSize_Bpp12,  //!< The pixel depth in the acquired images is 12 bits per pixel - Applies to: daA2448-70uc
        PixelSize_Bpp16,  //!< The pixel depth in the acquired images is 16 bits per pixel - Applies to: daA2448-70uc
        PixelSize_Bpp24,  //!< The pixel depth in the acquired images is 24 bits per pixel - Applies to: daA2448-70uc
        PixelSize_Bpp8  //!< The pixel depth in the acquired images is 8 bits per pixel - Applies to: daA2448-70uc
    };

    //! Valid values for SoftwareSignalSelector
    enum SoftwareSignalSelectorEnums
    {
        SoftwareSignalSelector_SoftwareSignal1,  //!< Software signal 1 can be executed - Applies to: daA2448-70uc
        SoftwareSignalSelector_SoftwareSignal2,  //!< Software signal 2 can be executed - Applies to: daA2448-70uc
        SoftwareSignalSelector_SoftwareSignal3  //!< Software signal 3 can be executed - Applies to: daA2448-70uc
    };

    //! Valid values for TestPattern
    enum TestPatternEnums
    {
        TestPattern_Black,  //!< The camera generates a black test pattern - Applies to: daA2448-70uc
        TestPattern_Off,  //!< No test pattern is generated - Applies to: daA2448-70uc
        TestPattern_Testimage1,  //!< The camera generates a test image with the test image 1 pattern - Applies to: daA2448-70uc
        TestPattern_Testimage2,  //!< The camera generates a test image with the test image 2 pattern - Applies to: daA2448-70uc
        TestPattern_Testimage3,  //!< The camera generates a test image with the test image 3 pattern - Applies to: daA2448-70uc
        TestPattern_Testimage6,  //!< The camera generates a test image with the test image 6 pattern - Applies to: daA2448-70uc
        TestPattern_White  //!< The camera generates a white test pattern - Applies to: daA2448-70uc
    };

    //! Valid values for TimerSelector
    enum TimerSelectorEnums
    {
        TimerSelector_Timer1,  //!< Timer 1 can be configured - Applies to: daA2448-70uc
        TimerSelector_Timer2  //!< Timer 2 can be configured - Applies to: daA2448-70uc
    };

    //! Valid values for TimerStatus
    enum TimerStatusEnums
    {
        TimerStatus_TimerActive,  //!< The timer has been started - Applies to: daA2448-70uc
        TimerStatus_TimerIdle,  //!< The timer is idle - Applies to: daA2448-70uc
        TimerStatus_TimerTriggerWait  //!< The timer is waiting to be started - Applies to: daA2448-70uc
    };

    //! Valid values for TimerTriggerActivation
    enum TimerTriggerActivationEnums
    {
        TimerTriggerActivation_Todo  //!< TODO - Applies to: daA2448-70uc
    };

    //! Valid values for TimerTriggerSource
    enum TimerTriggerSourceEnums
    {
        TimerTriggerSource_AcquisitionActive,  //!< The selected timer can be started by an Acquisition Active signal - Applies to: daA2448-70uc
        TimerTriggerSource_Counter1Active,  //!< The selected timer can be started by a Counter 1 Active signal - Applies to: daA2448-70uc
        TimerTriggerSource_Counter1End,  //!< The selected timer can be started by a Counter 1 End signal - Applies to: daA2448-70uc
        TimerTriggerSource_Counter1Start,  //!< The selected timer can be started by a Counter 1 Start signal - Applies to: daA2448-70uc
        TimerTriggerSource_Counter2Active,  //!< The selected timer can be started by a Counter 2 Active signal - Applies to: daA2448-70uc
        TimerTriggerSource_Counter2End,  //!< The selected timer can be started by a Counter 2 End signal - Applies to: daA2448-70uc
        TimerTriggerSource_Counter2Start,  //!< The selected timer can be started by a Counter 2 Start signal - Applies to: daA2448-70uc
        TimerTriggerSource_ExposureActive,  //!< The selected timer can be started by an Exposure Active signal - Applies to: daA2448-70uc
        TimerTriggerSource_ExposureStart,  //!< The selected timer can be started by an Exposure Start signal - Applies to: daA2448-70uc
        TimerTriggerSource_ExposureTriggerWait,  //!< The selected timer can be started by an Exposure Trigger Wait signal - Applies to: daA2448-70uc
        TimerTriggerSource_FrameBurstActive,  //!< The selected timer can be started by a Frame Burst Active signal - Applies to: daA2448-70uc
        TimerTriggerSource_FrameBurstTriggerWait,  //!< The selected timer can be started by a Frame Burst Trigger Wait signal - Applies to: daA2448-70uc
        TimerTriggerSource_FrameTriggerWait,  //!< The selected timer can be started by a Frame Trigger Wait signal - Applies to: daA2448-70uc
        TimerTriggerSource_Line1,  //!< The selected timer can be started by a Line 1 signal - Applies to: daA2448-70uc
        TimerTriggerSource_Line2,  //!< The selected timer can be started by a Line 2 signal - Applies to: daA2448-70uc
        TimerTriggerSource_Line3,  //!< The selected timer can be started by a Line 3 signal - Applies to: daA2448-70uc
        TimerTriggerSource_Line4,  //!< The selected timer can be started by a Line 4 signal - Applies to: daA2448-70uc
        TimerTriggerSource_Off,  //!< The selected timer is disabled and can't be started - Applies to: daA2448-70uc
        TimerTriggerSource_SoftwareSignal1,  //!< The selected timer can be started by a Software Signal 1 signal - Applies to: daA2448-70uc
        TimerTriggerSource_SoftwareSignal2,  //!< The selected timer can be started by a Software Signal 2 signal - Applies to: daA2448-70uc
        TimerTriggerSource_SoftwareSignal3,  //!< The selected timer can be started by a Software Signal 3 signal - Applies to: daA2448-70uc
        TimerTriggerSource_Timer1Active,  //!< The selected timer can be started by a Timer 1 Active signal - Applies to: daA2448-70uc
        TimerTriggerSource_Timer1End,  //!< The selected timer can be started by a Timer 1 End signal - Applies to: daA2448-70uc
        TimerTriggerSource_Timer2Active,  //!< The selected timer can be started by a Timer 2 Active signal - Applies to: daA2448-70uc
        TimerTriggerSource_Timer2End  //!< The selected timer can be started by a Timer 2 End signal - Applies to: daA2448-70uc
    };

    //! Valid values for TriggerActivation
    enum TriggerActivationEnums
    {
        TriggerActivation_Todo  //!< TODO - Applies to: daA2448-70uc
    };

    //! Valid values for TriggerMode
    enum TriggerModeEnums
    {
        TriggerMode_Off,  //!< The currently selected trigger is turned off - Applies to: daA2448-70uc
        TriggerMode_On  //!< The currently selected trigger is turned on - Applies to: daA2448-70uc
    };

    //! Valid values for TriggerSelector
    enum TriggerSelectorEnums
    {
        TriggerSelector_ExposureActive,  //!< The Exposure Active trigger can be configured - Applies to: daA2448-70uc
        TriggerSelector_ExposureEnd,  //!< The Exposure End trigger can be configured - Applies to: daA2448-70uc
        TriggerSelector_ExposureStart,  //!< The Exposure Start trigger can be configured - Applies to: daA2448-70uc
        TriggerSelector_FrameActive,  //!< The Frame Active trigger can be configured - Applies to: daA2448-70uc
        TriggerSelector_FrameBurstActive,  //!< The Frame Burst Active trigger can be configured - Applies to: daA2448-70uc
        TriggerSelector_FrameBurstEnd,  //!< The Frame Burst End trigger can be configured - Applies to: daA2448-70uc
        TriggerSelector_FrameBurstStart,  //!< The Frame Burst Start trigger can be configured - Applies to: daA2448-70uc
        TriggerSelector_FrameEnd,  //!< The Frame End trigger can be configured - Applies to: daA2448-70uc
        TriggerSelector_FrameStart  //!< The Frame Start trigger can be configured - Applies to: daA2448-70uc
    };

    //! Valid values for TriggerSource
    enum TriggerSourceEnums
    {
        TriggerSource_Counter1Active,  //!< The Counter 1 Active trigger can be configured - Applies to: daA2448-70uc
        TriggerSource_Counter1End,  //!< The Counter 1 End trigger can be configured - Applies to: daA2448-70uc
        TriggerSource_Counter1Start,  //!< The Counter 1 Start trigger can be configured - Applies to: daA2448-70uc
        TriggerSource_Counter2Active,  //!< The Counter 2 Active trigger can be configured - Applies to: daA2448-70uc
        TriggerSource_Counter2End,  //!< The Counter 2 End trigger can be configured - Applies to: daA2448-70uc
        TriggerSource_Counter2Start,  //!< The Counter 2 Start trigger can be configured - Applies to: daA2448-70uc
        TriggerSource_Line1,  //!< The source signal for the selected trigger is set to Line 1 - Applies to: daA2448-70uc
        TriggerSource_Line2,  //!< The source signal for the selected trigger is set to Line 2 - Applies to: daA2448-70uc
        TriggerSource_Line3,  //!< The source signal for the selected trigger is set to Line 3 - Applies to: daA2448-70uc
        TriggerSource_Line4,  //!< The source signal for the selected trigger is set to Line 4 - Applies to: daA2448-70uc
        TriggerSource_Software,  //!< The source signal for the selected trigger is set to software triggering - Applies to: daA2448-70uc
        TriggerSource_SoftwareSignal1,  //!< The source signal for the selected trigger is set to software signal 1 - Applies to: daA2448-70uc
        TriggerSource_SoftwareSignal2,  //!< The source signal for the selected trigger is set to software signal 2 - Applies to: daA2448-70uc
        TriggerSource_SoftwareSignal3,  //!< The source signal for the selected trigger is set to software signal 3 - Applies to: daA2448-70uc
        TriggerSource_Timer1Active,  //!< The Timer 1 Active trigger can be configured - Applies to: daA2448-70uc
        TriggerSource_Timer1End,  //!< The Timer 1 End trigger can be configured - Applies to: daA2448-70uc
        TriggerSource_Timer2Active,  //!< The Timer 2 Active trigger can be configured - Applies to: daA2448-70uc
        TriggerSource_Timer2End  //!< The Timer 2 End trigger can be configured - Applies to: daA2448-70uc
    };

    //! Valid values for UserDefinedValueSelector
    enum UserDefinedValueSelectorEnums
    {
        UserDefinedValueSelector_Value1,  //!< The user-defined value 1 can be configured - Applies to: daA2448-70uc
        UserDefinedValueSelector_Value2,  //!< The user-defined value 2 can be configured - Applies to: daA2448-70uc
        UserDefinedValueSelector_Value3,  //!< The user-defined value 3 can be configured - Applies to: daA2448-70uc
        UserDefinedValueSelector_Value4,  //!< The user-defined value 4 can be configured - Applies to: daA2448-70uc
        UserDefinedValueSelector_Value5  //!< The user-defined value 5 can be configured - Applies to: daA2448-70uc
    };

    //! Valid values for UserOutputSelector
    enum UserOutputSelectorEnums
    {
        UserOutputSelector_UserOutput1,  //!< The user-settable output signal 1 can be configured - Applies to: daA2448-70uc
        UserOutputSelector_UserOutput2,  //!< The user-settable output signal 2 can be configured - Applies to: daA2448-70uc
        UserOutputSelector_UserOutput3,  //!< The user-settable output signal 3 can be configured - Applies to: daA2448-70uc
        UserOutputSelector_UserOutput4  //!< The user-settable output signal 4 can be configured - Applies to: daA2448-70uc
    };

    //! Valid values for UserSetDefault
    enum UserSetDefaultEnums
    {
        UserSetDefault_Default,  //!< The Default User Set factory set is set as the default startup set - Applies to: daA2448-70uc
        UserSetDefault_UserSet1,  //!< User set 1 is set as the default startup set - Applies to: daA2448-70uc
        UserSetDefault_UserSet2,  //!< User set 2 is set as the default startup set - Applies to: daA2448-70uc
        UserSetDefault_UserSet3  //!< User set 3 is set as the default startup set - Applies to: daA2448-70uc
    };

    //! Valid values for UserSetSelector
    enum UserSetSelectorEnums
    {
        UserSetSelector_Default,  //!< The Default User Set factory set can be loaded - Applies to: daA2448-70uc
        UserSetSelector_UserSet1,  //!< User set 1 can be saved, loaded, or configured - Applies to: daA2448-70uc
        UserSetSelector_UserSet2,  //!< User set 2 can be saved, loaded, or configured - Applies to: daA2448-70uc
        UserSetSelector_UserSet3  //!< User set 3 can be saved, loaded, or configured - Applies to: daA2448-70uc
    };


    
    
    //**************************************************************************************************
    // Parameter class BaslerCameraCameraParams
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for daA2448-70uc

    Sources:
    daA2448-70uc p=du1_imx548c/s=r/v=1.0.2/i=6515.14/h=61c0643
    */
    class BaslerCameraCameraParams
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
            //! Constructor
            BaslerCameraCameraParams(void);

            //! Destructor
            ~BaslerCameraCameraParams(void);

            //! Initializes the references
            void _Initialize(GENAPI_NAMESPACE::INodeMap*);

    //! \endcond

    private:
        class BaslerCameraCameraParams_Data;
        BaslerCameraCameraParams_Data* m_pData;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Aborts the acquisition of images - Applies to: daA2448-70uc

        Aborts the acquisition of images. If the camera is currently exposing a frame, the camera stops exposing immediately. The readout process, if already started, is aborted. The current frame will be incomplete. Afterwards, image acquisition is switched off.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionAbort" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& AcquisitionAbort;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Number of frames to acquire for each Frame Burst Start trigger - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionBurstFrameCount" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& AcquisitionBurstFrameCount;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Acquisition frame rate of the camera in frames per second - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionFrameRate" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& AcquisitionFrameRate;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Enables setting the camera's acquisition frame rate to a specified value - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionFrameRateEnable" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& AcquisitionFrameRateEnable;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Sets the image acquisition mode - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionMode" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<AcquisitionModeEnums>& AcquisitionMode;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Starts the acquisition of images - Applies to: daA2448-70uc

        Starts the acquisition of images. If the camera is configured for single frame acquisition, it will start the acquisition of one frame. If the camera is configured for continuous frame acquisition, it will start the continuous acquisition of frames.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionStart" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& AcquisitionStart;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Indicates whether the camera is waiting for trigger signals - Applies to: daA2448-70uc

        Indicates whether the camera is waiting for trigger signals. You should only use this feature if the camera is configured for software triggering. If the camera is configured for hardware triggering, monitor the camera's Trigger Wait signals instead.
    
        Visibility: Expert

        Selected by: AcquisitionStatusSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionStatus" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& AcquisitionStatus;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Sets the signal whose status you want to check - Applies to: daA2448-70uc

        Sets the signal whose status you want to check. Its status can be checked by reading the Acquisition Status parameter value.
    
        Visibility: Expert

        Selecting Parameters: AcquisitionStatus

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionStatusSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<AcquisitionStatusSelectorEnums>& AcquisitionStatusSelector;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Stops the acquisition of images - Applies to: daA2448-70uc

        Stops the acquisition of images if a continuous image acquisition is in progress.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AcquisitionStop" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& AcquisitionStop;

    //@}


    //! \name Categories: AutoFunctionControl
    //@{
    /*!
        \brief Lower limit of the Exposure Time parameter when the Exposure Auto auto function is active - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoExposureTimeLowerLimit" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& AutoExposureTimeLowerLimit;

    //@}


    //! \name Categories: AutoFunctionControl
    //@{
    /*!
        \brief Upper limit of the Exposure Time parameter when the Exposure Auto auto function is active - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoExposureTimeUpperLimit" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& AutoExposureTimeUpperLimit;

    //@}


    //! \name Categories: AutoFunctionControl
    //@{
    /*!
        \brief Sets how gain and exposure time will be balanced when the camera is making automatic adjustments - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionProfile" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<AutoFunctionProfileEnums>& AutoFunctionProfile;

    //@}


    //! \name Categories: AutoFunctionROIControl
    //@{
    /*!
        \brief Height of the auto function ROI (in pixels) - Applies to: daA2448-70uc

    
        Visibility: Beginner

        Selected by: AutoFunctionROISelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROIHeight" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& AutoFunctionROIHeight;

    //@}


    //! \name Categories: AutoFunctionROIControl
    //@{
    /*!
        \brief Highlights the current auto function ROI in the image window - Applies to: daA2448-70uc

        Highlights the current auto function ROI in the image window. Areas that do not belong to the current ROI appear darker.
    
        Visibility: Beginner

        Selected by: AutoFunctionROISelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROIHighlight" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& AutoFunctionROIHighlight;

    //@}


    //! \name Categories: AutoFunctionROIControl
    //@{
    /*!
        \brief Horizontal offset of the auto function ROI from the left side of the sensor (in pixels) - Applies to: daA2448-70uc

    
        Visibility: Beginner

        Selected by: AutoFunctionROISelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROIOffsetX" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& AutoFunctionROIOffsetX;

    //@}


    //! \name Categories: AutoFunctionROIControl
    //@{
    /*!
        \brief Vertical offset from the top of the sensor to the auto function ROI (in pixels) - Applies to: daA2448-70uc

        Vertical offset of the auto function ROI from the top of the sensor (in pixels).
    
        Visibility: Beginner

        Selected by: AutoFunctionROISelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROIOffsetY" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& AutoFunctionROIOffsetY;

    //@}


    //! \name Categories: AutoFunctionROIControl
    //@{
    /*!
        \brief Sets which auto function ROI can be configured - Applies to: daA2448-70uc

    
        Visibility: Beginner

        Selecting Parameters: AutoFunctionROIUseBrightness, AutoFunctionROIUseWhiteBalance, AutoFunctionROIWidth, AutoFunctionROIHeight, AutoFunctionROIOffsetX, AutoFunctionROIOffsetY and AutoFunctionROIHighlight

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROISelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<AutoFunctionROISelectorEnums>& AutoFunctionROISelector;

    //@}


    //! \name Categories: AutoFunctionROIControl
    //@{
    /*!
        \brief Assigns the Gain Auto and the Exposure Auto auto functions to the currently selected auto function ROI - Applies to: daA2448-70uc

        Assigns the Gain Auto and the Exposure Auto auto functions to the currently selected auto function ROI. For this parameter, Gain Auto and Exposure Auto are considered as a single auto function named 'Brightness'.
    
        Visibility: Beginner

        Selected by: AutoFunctionROISelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROIUseBrightness" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& AutoFunctionROIUseBrightness;

    //@}


    //! \name Categories: AutoFunctionROIControl
    //@{
    /*!
        \brief Assigns the Balance White Auto auto function to the currently selected auto function ROI - Applies to: daA2448-70uc

    
        Visibility: Beginner

        Selected by: AutoFunctionROISelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROIUseWhiteBalance" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& AutoFunctionROIUseWhiteBalance;

    //@}


    //! \name Categories: AutoFunctionROIControl
    //@{
    /*!
        \brief Width of the auto function ROI (in pixels) - Applies to: daA2448-70uc

    
        Visibility: Beginner

        Selected by: AutoFunctionROISelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoFunctionROIWidth" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& AutoFunctionROIWidth;

    //@}


    //! \name Categories: AutoFunctionControl
    //@{
    /*!
        \brief Lower limit of the Gain parameter when the Gain Auto auto function is active - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoGainLowerLimit" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& AutoGainLowerLimit;

    //@}


    //! \name Categories: AutoFunctionControl
    //@{
    /*!
        \brief Upper limit of the Gain parameter when the Gain Auto auto function is active - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoGainUpperLimit" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& AutoGainUpperLimit;

    //@}


    //! \name Categories: AutoFunctionControl
    //@{
    /*!
        \brief Target brightness for the Gain Auto and the Exposure Auto auto functions - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoTargetBrightness" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& AutoTargetBrightness;

    //@}


    //! \name Categories: WhiteBalanceControl
    //@{
    /*!
        \brief Balance Ratio value to be applied to the currently selected channel - Applies to: daA2448-70uc

    
        Visibility: Beginner

        Selected by: BalanceRatioSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BalanceRatio" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BalanceRatio;

    //@}


    //! \name Categories: WhiteBalanceControl
    //@{
    /*!
        \brief Sets which color channel can be adjusted when performing manual white balance - Applies to: daA2448-70uc

        Sets which color channel can be adjusted when performing manual white balance. All changes to the Balance Ratio parameter will be applied to the selected color channel.
    
        Visibility: Beginner

        Selecting Parameters: BalanceRatio

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BalanceRatioSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BalanceRatioSelectorEnums>& BalanceRatioSelector;

    //@}


    //! \name Categories: WhiteBalanceControl
    //@{
    /*!
        \brief Sets the operation mode of the Balance White Auto auto function - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BalanceWhiteAuto" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BalanceWhiteAutoEnums>& BalanceWhiteAuto;

    //@}


    //! \name Categories: AnalogControl
    //@{
    /*!
        \brief Black level value to be applied to the currently selected sensor tap - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: BlackLevelSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BlackLevel" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BlackLevel;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Sets the burst mode - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslAcquisitionBurstMode" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslAcquisitionBurstModeEnums>& BslAcquisitionBurstMode;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Sets whether Acquisition Stop commands abort exposure - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslAcquisitionStopMode" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslAcquisitionStopModeEnums>& BslAcquisitionStopMode;

    //@}


    //! \name Categories: ImageProcessingControl
    //@{
    /*!
        \brief Brightness value to be applied - Applies to: daA2448-70uc

        Adjusting the brightness lightens or darkens the entire image.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslBrightness" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BslBrightness;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Centers the image horizontally - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslCenterX" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& BslCenterX;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Centers the image vertically - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslCenterY" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& BslCenterY;

    //@}


    //! \name Categories: ChunkDataControl
    //@{
    /*!
        \brief Indicates the status of the target brightness adjustments performed by the Exposure Auto and Gain Auto auto functions - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslChunkAutoBrightnessStatus" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslChunkAutoBrightnessStatusEnums>& BslChunkAutoBrightnessStatus;

    //@}


    //! \name Categories: ChunkDataControl
    //@{
    /*!
        \brief Sets which information should be included in the Chunk Timestamp Value chunk - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selecting Parameters: BslChunkTimestampValue

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslChunkTimestampSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslChunkTimestampSelectorEnums>& BslChunkTimestampSelector;

    //@}


    //! \name Categories: ChunkDataControl
    //@{
    /*!
        \brief Value of the timestamp when the image was acquired - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: BslChunkTimestampSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslChunkTimestampValue" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& BslChunkTimestampValue;

    //@}


    //! \name Categories: AnalogControl and ImageProcessingControl
    //@{
    /*!
        \brief Sets the color space for image acquisitions - Applies to: daA2448-70uc

        Sets the color space for image acquisitions. Note that the gamma correction value also influences the perception of brightness in the resulting images.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslColorSpace" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslColorSpaceEnums>& BslColorSpace;

    //@}


    //! \name Categories: ImageProcessingControl
    //@{
    /*!
        \brief Contrast value to be applied - Applies to: daA2448-70uc

        Adjusting the contrast increases the difference between light and dark areas in the image.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslContrast" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BslContrast;

    //@}


    //! \name Categories: ImageProcessingControl
    //@{
    /*!
        \brief Sets the contrast mode - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslContrastMode" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslContrastModeEnums>& BslContrastMode;

    //@}


    //! \name Categories: ImageProcessingControl
    //@{
    /*!
        \brief Identifies outlier pixels and adjusts their intensity value - Applies to: daA2448-70uc

        Pixels that have a significantly higher or lower intensity value than the neighboring pixels are called outlier pixels. This feature identifies them and adjusts their intensity value.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslDefectPixelCorrectionMode" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslDefectPixelCorrectionModeEnums>& BslDefectPixelCorrectionMode;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Actual bandwidth the camera will use - Applies to: daA2448-70uc

        Actual bandwidth (in bytes per second) that the camera will use to transmit image data and chunk data with the current camera settings.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslDeviceLinkCurrentThroughput" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& BslDeviceLinkCurrentThroughput;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Current exposure time - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslEffectiveExposureTime" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BslEffectiveExposureTime;

    //@}


    //! \name Categories: ErrorReportControl
    //@{
    /*!
        \brief Indicates whether an internal error occured on the device - Applies to: daA2448-70uc

        Indicates whether an internal error occured on the device. If an error occured, you can use the Error Report Next command to determine the error code.
    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslErrorPresent" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& BslErrorPresent;

    //@}


    //! \name Categories: ErrorReportControl
    //@{
    /*!
        \brief Retrieves the next error code from the device - Applies to: daA2448-70uc

        Retrieves the next error code from the device. To check the error code, get the value of the Error Report Value parameter.
    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslErrorReportNext" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& BslErrorReportNext;

    //@}


    //! \name Categories: ErrorReportControl
    //@{
    /*!
        \brief Error code indicating the cause of the internal error - Applies to: daA2448-70uc

        Error code indicating the cause of the internal error. If there are multiple errors, execute the Error Report Next command to retrieve the next error code. A parameter value of 0 means that there are no more error codes to retrieve.
    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslErrorReportValue" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& BslErrorReportValue;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Exposure start delay with current settings - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslExposureStartDelay" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BslExposureStartDelay;

    //@}


    //! \name Categories: ImageProcessingControl
    //@{
    /*!
        \brief Hue shift value to be applied - Applies to: daA2448-70uc

        Adjusting the hue shifts the colors of the image. This can be useful, e.g., to correct minor color shifts or to create false-color images.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslHue" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BslHue;

    //@}


    //! \name Categories: DigitalIOControl
    //@{
    /*!
        \brief Time period in which the camera evaluates all changes and durations of logical states of the input signal - Applies to: daA2448-70uc

        Time period in which the camera evaluates all changes and durations of logical states of the input signal. During evaluation, the camera calculates the mean value over time and applies a threshold function to the result to reconstruct the digital signal. This removes noise, interference, etc. as well as signal pulses shorter than the filter time.
    
        Visibility: Expert

        Selected by: LineSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslInputFilterTime" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BslInputFilterTime;

    //@}


    //! \name Categories: DigitalIOControl
    //@{
    /*!
        \brief Time period in which the camera doesn't accept any further trigger signals or signal changes after receiving an input trigger signal - Applies to: daA2448-70uc

        Time period in which the camera doesn't accept any further trigger signals or signal changes after receiving an input trigger signal. This is useful if you want to avoid false triggering caused by multiple trigger signals arriving in quick succession (contact bounce).
    
        Visibility: Expert

        Selected by: LineSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslInputHoldOffTime" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BslInputHoldOffTime;

    //@}


    //! \name Categories: ImageProcessingControl
    //@{
    /*!
        \brief Sets the light source preset - Applies to: daA2448-70uc

        Sets the light source preset. The colors in the image will be corrected so that they are appropriate for the selected light source.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightSourcePreset" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslLightSourcePresetEnums>& BslLightSourcePreset;

    //@}


    //! \name Categories: ImageProcessingControl
    //@{
    /*!
        \brief Enables adjustment of the selected feature - Applies to: daA2448-70uc

        Enables adjustment of the feature specified by the Light Source Preset Feature Selector parameter.
    
        Visibility: Expert

        Selected by: BslLightSourcePresetFeatureSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightSourcePresetFeatureEnable" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& BslLightSourcePresetFeatureEnable;

    //@}


    //! \name Categories: ImageProcessingControl
    //@{
    /*!
        \brief Sets which features the camera adjusts when you select a light source preset - Applies to: daA2448-70uc

        Sets which features the camera adjusts when you select a light source preset. By default, the camera adjust all features.
    
        Visibility: Expert

        Selecting Parameters: BslLightSourcePresetFeatureEnable

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLightSourcePresetFeatureSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslLightSourcePresetFeatureSelectorEnums>& BslLightSourcePresetFeatureSelector;

    //@}


    //! \name Categories: DigitalIOControl
    //@{
    /*!
        \brief Sets the connection signal for the currently selected line - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: LineSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslLineConnection" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslLineConnectionEnums>& BslLineConnection;

    //@}


    //! \name Categories: PGIControl
    //@{
    /*!
        \brief Amount of noise reduction to be applied - Applies to: daA2448-70uc

        Amount of noise reduction to be applied. The higher the value, the less chroma noise will be visible in your images. However, very high values may result in image information loss.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslNoiseReduction" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BslNoiseReduction;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Maximum number of frames that can be acquired per second with current camera settings - Applies to: daA2448-70uc

        Maximum number of frames that can be acquired per second with current camera settings. In High Speed burst mode, this value is usually higher than the Resulting Transfer Frame Rate parameter value.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslResultingAcquisitionFrameRate" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BslResultingAcquisitionFrameRate;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Maximum number of bursts per second with current camera settings - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslResultingFrameBurstRate" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BslResultingFrameBurstRate;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Maximum number of frames that can be transferred per second with current camera settings - Applies to: daA2448-70uc

        Maximum number of frames that can be transferred per second with current camera settings. This value indicates the peak frame rate to be expected at the camera's output. In High Speed burst mode, this value is usually lower than the Resulting Acquisition Frame Rate parameter value.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslResultingTransferFrameRate" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BslResultingTransferFrameRate;

    //@}


    //! \name Categories: ImageProcessingControl
    //@{
    /*!
        \brief Saturation value to be applied - Applies to: daA2448-70uc

        Adjusting the saturation changes the colorfulness (intensity) of the colors. A higher saturation, for example, makes colors easier to distinguish.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSaturation" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BslSaturation;

    //@}


    //! \name Categories: ImageProcessingControl
    //@{
    /*!
        \brief Scaling factor to be applied to all images - Applies to: daA2448-70uc

        Scaling factor to be applied to all images. Scaling is performed using the Pixel Beyond feature.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslScalingFactor" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BslScalingFactor;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Sets the bit depth of the image sensor's data output - Applies to: daA2448-70uc

        Sets the bit depth of the image sensor's data output. You can set the sensor bit depth independently of the pixel format used if the Sensor Bit Depth Mode parameter is set to Manual. If that parameter is set to Auto, the sensor bit depth is adjusted automatically depending on the pixel format used.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSensorBitDepth" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslSensorBitDepthEnums>& BslSensorBitDepth;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Sets the sensor bit depth mode - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSensorBitDepthMode" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslSensorBitDepthModeEnums>& BslSensorBitDepthMode;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Switches the sensor power off - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSensorOff" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& BslSensorOff;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Switches the sensor power on - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSensorOn" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& BslSensorOn;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Puts the sensor in standby mode - Applies to: daA2448-70uc

        Puts the sensor in standby mode. In standby mode, power consumption is reduced significantly, which results in a lower camera temperature. Certain parameters can only be configured when the sensor is in standby mode.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSensorStandby" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& BslSensorStandby;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Returns the current power state of the sensor - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSensorState" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslSensorStateEnums>& BslSensorState;

    //@}


    //! \name Categories: PGIControl
    //@{
    /*!
        \brief Sharpening value to be applied - Applies to: daA2448-70uc

        Sharpening value to be applied. The higher the sharpness, the more distinct the image subject's contours will be. However, very high values may result in image information loss.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslSharpnessEnhancement" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BslSharpnessEnhancement;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Indicates the maximum temperature the camera reached during operation - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTemperatureMax" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& BslTemperatureMax;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Indicates the temperature state - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTemperatureStatus" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslTemperatureStatusEnums>& BslTemperatureStatus;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Indicates how often the temperature state changed to Error - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTemperatureStatusErrorCount" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& BslTemperatureStatusErrorCount;

    //@}


    //! \name Categories: BslTwiControl
    //@{
    /*!
        \brief Sets the bit rate for TWI communication - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTwiBitrate" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslTwiBitrateEnums>& BslTwiBitrate;

    //@}


    //! \name Categories: BslTwiControl
    //@{
    /*!
        \brief Pulls SCL low, which is rarely needed - Applies to: daA2448-70uc

        Pulls SCL low, which is rarely needed. When SCL is pulled low, TWI communication isn't possible.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTwiPullSclLow" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& BslTwiPullSclLow;

    //@}


    //! \name Categories: BslTwiControl
    //@{
    /*!
        \brief Pulls SDA low, which is rarely needed - Applies to: daA2448-70uc

        Pulls SDA low, which is rarely needed. When SDA is pulled low, TWI communication isn't possible.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTwiPullSdaLow" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& BslTwiPullSdaLow;

    //@}


    //! \name Categories: BslTwiControl
    //@{
    /*!
        \brief Triggers a read transfer - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTwiRead" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& BslTwiRead;

    //@}


    //! \name Categories: BslTwiControl
    //@{
    /*!
        \brief Address of the target device - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTwiTargetAddress" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& BslTwiTargetAddress;

    //@}


    //! \name Categories: BslTwiControl
    //@{
    /*!
        \brief Buffer that holds data to be written or data that was read - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTwiTransferBuffer" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IRegisterEx& BslTwiTransferBuffer;

    //@}


    //! \name Categories: BslTwiControl
    //@{
    /*!
        \brief Number of bytes to be transferred from or to the transfer buffer - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTwiTransferLength" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& BslTwiTransferLength;

    //@}


    //! \name Categories: BslTwiControl
    //@{
    /*!
        \brief Indicates the status of an accepted read or write transfer - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTwiTransferStatus" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslTwiTransferStatusEnums>& BslTwiTransferStatus;

    //@}


    //! \name Categories: BslTwiControl
    //@{
    /*!
        \brief Triggers an update of the transfer status - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTwiUpdateTransferStatus" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& BslTwiUpdateTransferStatus;

    //@}


    //! \name Categories: BslTwiControl
    //@{
    /*!
        \brief Triggers a write transfer - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslTwiWrite" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& BslTwiWrite;

    //@}


    //! \name Categories: TransportLayerControl
    //@{
    /*!
        \brief Indicates how power is supplied to the device - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslUSBPowerSource" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslUSBPowerSourceEnums>& BslUSBPowerSource;

    //@}


    //! \name Categories: TransportLayerControl
    //@{
    /*!
        \brief Indicates the speed mode of the USB port - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=BslUSBSpeedMode" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<BslUSBSpeedModeEnums>& BslUSBSpeedMode;

    //@}


    //! \name Categories: ChunkDataControl
    //@{
    /*!
        \brief Sets which counter to retrieve chunk data from - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selecting Parameters: ChunkCounterValue

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkCounterSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<ChunkCounterSelectorEnums>& ChunkCounterSelector;

    //@}


    //! \name Categories: ChunkDataControl
    //@{
    /*!
        \brief Value of the selected chunk counter - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: ChunkCounterSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkCounterValue" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& ChunkCounterValue;

    //@}


    //! \name Categories: ChunkDataControl
    //@{
    /*!
        \brief Includes the currently selected chunk in the payload data - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: ChunkSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkEnable" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& ChunkEnable;

    //@}


    //! \name Categories: ChunkDataControl
    //@{
    /*!
        \brief Exposure time used to acquire the image - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkExposureTime" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& ChunkExposureTime;

    //@}


    //! \name Categories: ChunkDataControl
    //@{
    /*!
        \brief Unique identifier of the current frame - Applies to: daA2448-70uc

        Unique identifier of the current frame. The frame ID starts at 0 and keeps incrementing by 1 for each exposed image until the camera is powered off. The maximum value is 2^48.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkFrameID" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& ChunkFrameID;

    //@}


    //! \name Categories: ChunkDataControl
    //@{
    /*!
        \brief Gain used during image acquisition - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: ChunkGainSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkGain" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& ChunkGain;

    //@}


    //! \name Categories: ChunkDataControl
    //@{
    /*!
        \brief Bit field that indicates the status of all of the camera's input and output lines when the image was acquired - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkLineStatusAll" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& ChunkLineStatusAll;

    //@}


    //! \name Categories: ChunkDataControl
    //@{
    /*!
        \brief Enables the chunk mode - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkModeActive" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& ChunkModeActive;

    //@}


    //! \name Categories: ChunkDataControl
    //@{
    /*!
        \brief CRC checksum of the acquired image - Applies to: daA2448-70uc

        CRC checksum of the acquired image. The checksum is calculated using all of the image data and all of the appended chunks except for the checksum itself.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkPayloadCRC16" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& ChunkPayloadCRC16;

    //@}


    //! \name Categories: ChunkDataControl
    //@{
    /*!
        \brief Sets which chunk can be enabled - Applies to: daA2448-70uc

        Sets which chunk can be enabled. The chunk can be enabled using the Chunk Enable parameter.
    
        Visibility: Expert

        Selecting Parameters: ChunkEnable

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ChunkSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<ChunkSelectorEnums>& ChunkSelector;

    //@}


    //! \name Categories: CounterControl
    //@{
    /*!
        \brief Number of times a sequencer set is used before the Counter End event is generated - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: CounterSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterDuration" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& CounterDuration;

    //@}


    //! \name Categories: CounterControl
    //@{
    /*!
        \brief Sets the type of signal transition that the counter will count - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: CounterSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterEventActivation" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<CounterEventActivationEnums>& CounterEventActivation;

    //@}


    //! \name Categories: CounterControl
    //@{
    /*!
        \brief Sets which event increases the currently selected counter - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: CounterSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterEventSource" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<CounterEventSourceEnums>& CounterEventSource;

    //@}


    //! \name Categories: CounterControl
    //@{
    /*!
        \brief Immediately resets the selected counter - Applies to: daA2448-70uc

        Immediately resets the selected counter. The counter starts counting again immediately after the reset.
    
        Visibility: Expert

        Selected by: CounterSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterReset" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& CounterReset;

    //@}


    //! \name Categories: CounterControl
    //@{
    /*!
        \brief Sets which type of signal transition will reset the counter - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: CounterSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterResetActivation" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<CounterResetActivationEnums>& CounterResetActivation;

    //@}


    //! \name Categories: CounterControl
    //@{
    /*!
        \brief Sets which source signal will reset the currently selected counter - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: CounterSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterResetSource" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<CounterResetSourceEnums>& CounterResetSource;

    //@}


    //! \name Categories: CounterControl
    //@{
    /*!
        \brief Sets which counter can be configured - Applies to: daA2448-70uc

        Sets which counter can be configured. All changes to the counter settings will be applied to the selected counter.
    
        Visibility: Expert

        Selecting Parameters: CounterEventSource, CounterEventActivation, CounterResetSource, CounterResetActivation, CounterTriggerSource, CounterTriggerActivation, CounterValue, CounterDuration, CounterStatus and CounterReset

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<CounterSelectorEnums>& CounterSelector;

    //@}


    //! \name Categories: CounterControl
    //@{
    /*!
        \brief Returns the current status of the counter - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: CounterSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterStatus" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<CounterStatusEnums>& CounterStatus;

    //@}


    //! \name Categories: CounterControl
    //@{
    /*!
        \brief Sets the type of signal transition that will start the counter - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: CounterSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterTriggerActivation" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<CounterTriggerActivationEnums>& CounterTriggerActivation;

    //@}


    //! \name Categories: CounterControl
    //@{
    /*!
        \brief Sets the signal used to start the selected counter - Applies to: daA2448-70uc

        Sets the signal used to start the selected counter. If you start a counter, it will not necessarily start counting. If and when the counter counts, depends on the Counter Event Source parameter value.
    
        Visibility: Expert

        Selected by: CounterSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterTriggerSource" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<CounterTriggerSourceEnums>& CounterTriggerSource;

    //@}


    //! \name Categories: CounterControl
    //@{
    /*!
        \brief Current value of the counter - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: CounterSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=CounterValue" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& CounterValue;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Indicates the character set used by the strings of the device's bootstrap registers - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceCharacterSet" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<DeviceCharacterSetEnums>& DeviceCharacterSet;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Identifier of the product family of the device - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceFamilyName" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IStringEx& DeviceFamilyName;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Disables feature streaming on the device - Applies to: daA2448-70uc

        Disables feature streaming on the device. Feature streaming allows you to save camera settings outside of the device.
    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceFeaturePersistenceEnd" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& DeviceFeaturePersistenceEnd;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Enables feature streaming on the device - Applies to: daA2448-70uc

        Enables feature streaming on the device. Feature streaming allows you to save camera settings outside of the device.
    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceFeaturePersistenceStart" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& DeviceFeaturePersistenceStart;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Version of the camera's firmware - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceFirmwareVersion" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IStringEx& DeviceFirmwareVersion;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Major version of the GenCP protocol supported by the device - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceGenCPVersionMajor" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DeviceGenCPVersionMajor;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Minor version of the GenCP protocol supported by the device - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceGenCPVersionMinor" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DeviceGenCPVersionMinor;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Sets the behavior of the camera's status LED - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceIndicatorMode" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<DeviceIndicatorModeEnums>& DeviceIndicatorMode;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Speed of transmission negotiated on the selected link - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceLinkSpeed" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DeviceLinkSpeed;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Bandwidth limit for data transmission (in bytes per second) - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceLinkThroughputLimit" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DeviceLinkThroughputLimit;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Enables/disables the device link throughput limit - Applies to: daA2448-70uc

        Enables/disables the device link throughput limit. If disabled, the bandwidth used is determined by the settings of various other parameters, e.g., exposure time or frame rate.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceLinkThroughputLimitMode" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<DeviceLinkThroughputLimitModeEnums>& DeviceLinkThroughputLimitMode;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Major version number of the schema file of the selected manifest entry - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceManifestSchemaMajorVersion" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DeviceManifestSchemaMajorVersion;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Minor version number of the schema file of the selected manifest entry - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceManifestSchemaMinorVersion" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DeviceManifestSchemaMinorVersion;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Major version number of the GenICam XML file of the selected manifest entry - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceManifestXMLMajorVersion" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DeviceManifestXMLMajorVersion;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Minor version number of the GenICam XML file of the selected manifest entry - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceManifestXMLMinorVersion" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DeviceManifestXMLMinorVersion;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Subminor version number of the GenICam XML file of the selected manifest entry - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceManifestXMLSubMinorVersion" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DeviceManifestXMLSubMinorVersion;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Additional information from the vendor about the camera - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceManufacturerInfo" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IStringEx& DeviceManufacturerInfo;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Name of the camera model - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceModelName" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IStringEx& DeviceModelName;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Endianness of the registers of the device - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceRegistersEndianness" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<DeviceRegistersEndiannessEnums>& DeviceRegistersEndianness;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Announces the end of feature streaming - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceRegistersStreamingEnd" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& DeviceRegistersStreamingEnd;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Prepares the camera for feature streaming - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceRegistersStreamingStart" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& DeviceRegistersStreamingStart;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Immediately resets and restarts the camera - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceReset" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& DeviceReset;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Major version number of the SFNC specification that the camera is compatible with - Applies to: daA2448-70uc

        Major version number of the Standard Features Naming Convention (SFNC) specification that the camera is compatible with.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceSFNCVersionMajor" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DeviceSFNCVersionMajor;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Minor version number of the SFNC specification that the camera is compatible with - Applies to: daA2448-70uc

        Minor version number of the Standard Features Naming Convention (SFNC) specification that the camera is compatible with.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceSFNCVersionMinor" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DeviceSFNCVersionMinor;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Subminor version number of the SFNC specification that the camera is compatible with - Applies to: daA2448-70uc

        Subminor version number of the Standard Features Naming Convention (SFNC) specification that the camera is compatible with.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceSFNCVersionSubMinor" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DeviceSFNCVersionSubMinor;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Indicates the scan type of the camera's sensor (area or line scan) - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceScanType" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<DeviceScanTypeEnums>& DeviceScanType;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Serial number of the camera - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceSerialNumber" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IStringEx& DeviceSerialNumber;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Indicates the type of the device's transport layer - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceTLType" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<DeviceTLTypeEnums>& DeviceTLType;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Major version number of the device's transport layer - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceTLVersionMajor" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DeviceTLVersionMajor;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Minor version number of the device's transport layer - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceTLVersionMinor" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DeviceTLVersionMinor;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Subminor version number of the device's transport layer - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceTLVersionSubMinor" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DeviceTLVersionSubMinor;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Temperature at the selected location in the camera (in degrees centigrade) - Applies to: daA2448-70uc

        Temperature at the selected location in the camera (in degrees centigrade). The temperature is measured at the location specified by the Device Temperature Selector parameter.
    
        Visibility: Expert

        Selected by: DeviceTemperatureSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceTemperature" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& DeviceTemperature;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Sets the location in the camera where the temperature will be measured - Applies to: daA2448-70uc

        Sets the location in the camera where the temperature will be measured. The temperature can be retrieved using the Device Temperature parameter.
    
        Visibility: Expert

        Selecting Parameters: DeviceTemperature

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceTemperatureSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<DeviceTemperatureSelectorEnums>& DeviceTemperatureSelector;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief User-settable ID of the camera - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceUserID" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IStringEx& DeviceUserID;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Name of the camera vendor - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceVendorName" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IStringEx& DeviceVendorName;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Version of the camera - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DeviceVersion" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IStringEx& DeviceVersion;

    //@}


    //! \name Categories: AnalogControl
    //@{
    /*!
        \brief Digital shift to be applied - Applies to: daA2448-70uc

        Digital shift allows you to multiply the pixel values in an image. This increases the brightness of the image. If the parameter is set to zero, digital shift is disabled.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DigitalShift" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& DigitalShift;

    //@}


    //! \name Categories: EventExposureEndData
    //@{
    /*!
        \brief Unique identifier of the Exposure End event - Applies to: daA2448-70uc

        Unique identifier of the Exposure End event. Use this parameter to get notified when the event occurs.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventExposureEnd" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& EventExposureEnd;

    //@}


    //! \name Categories: EventExposureEndData
    //@{
    /*!
        \brief Frame ID of the Exposure End event - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventExposureEndFrameID" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& EventExposureEndFrameID;

    //@}


    //! \name Categories: EventExposureEndData
    //@{
    /*!
        \brief Timestamp of the Exposure End event - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventExposureEndTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& EventExposureEndTimestamp;

    //@}


    //! \name Categories: EventFrameStartData
    //@{
    /*!
        \brief Unique identifier of the Frame Start event - Applies to: daA2448-70uc

        Unique identifier of the Frame Start event. Use this parameter to get notified when the event occurs.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameStart" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& EventFrameStart;

    //@}


    //! \name Categories: EventFrameStartData
    //@{
    /*!
        \brief Frame ID of the Frame Start event - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameStartFrameID" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& EventFrameStartFrameID;

    //@}


    //! \name Categories: EventFrameStartData
    //@{
    /*!
        \brief Timestamp of the Frame Start event - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameStartTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& EventFrameStartTimestamp;

    //@}


    //! \name Categories: EventFrameTriggerMissedData
    //@{
    /*!
        \brief Unique identifier of the Frame Trigger Missed event - Applies to: daA2448-70uc

        Unique identifier of the Frame Trigger Missed event. Use this parameter to get notified when the event occurs.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameTriggerMissed" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& EventFrameTriggerMissed;

    //@}


    //! \name Categories: EventFrameTriggerMissedData
    //@{
    /*!
        \brief Timestamp of the Frame Trigger Missed event - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventFrameTriggerMissedTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& EventFrameTriggerMissedTimestamp;

    //@}


    //! \name Categories: EventControl
    //@{
    /*!
        \brief Enables event notifications for the currently selected event - Applies to: daA2448-70uc

        Enables event notifications for the currently selected event. The event can selected using the Event Selector parameter.
    
        Visibility: Expert

        Selected by: EventSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventNotification" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<EventNotificationEnums>& EventNotification;

    //@}


    //! \name Categories: EventOverrunData
    //@{
    /*!
        \brief Unique identifier of the Overrun event  Use this parameter to get notified when the event occurs - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverrun" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& EventOverrun;

    //@}


    //! \name Categories: EventOverrunData
    //@{
    /*!
        \brief Timestamp of the Event Overrun event - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventOverrunTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& EventOverrunTimestamp;

    //@}


    //! \name Categories: EventControl
    //@{
    /*!
        \brief Sets the event notification to be enabled - Applies to: daA2448-70uc

        Sets the event notification to be enabled. The notification can be enabled using the Event Notification parameter.
    
        Visibility: Expert

        Selecting Parameters: EventNotification

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<EventSelectorEnums>& EventSelector;

    //@}


    //! \name Categories: EventTemperatureStatusChangedData
    //@{
    /*!
        \brief Unique identifier of the Temperature Status Changed event - Applies to: daA2448-70uc

        Unique identifier of the Temperature Status Changed event. Use this parameter to get notified when the event occurs.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTemperatureStatusChanged" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& EventTemperatureStatusChanged;

    //@}


    //! \name Categories: EventTemperatureStatusChangedData
    //@{
    /*!
        \brief New temperature status that applies after the Temperature Status Changed event was raised - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTemperatureStatusChangedStatus" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<EventTemperatureStatusChangedStatusEnums>& EventTemperatureStatusChangedStatus;

    //@}


    //! \name Categories: EventTemperatureStatusChangedData
    //@{
    /*!
        \brief Timestamp of the Temperature Status Changed event - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTemperatureStatusChangedTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& EventTemperatureStatusChangedTimestamp;

    //@}


    //! \name Categories: EventTestData
    //@{
    /*!
        \brief Unique identifier of the Test event - Applies to: daA2448-70uc

        Unique identifier of the Test event. Use this parameter to get notified when the event occurs.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTest" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& EventTest;

    //@}


    //! \name Categories: EventTestData
    //@{
    /*!
        \brief Timestamp of the test event - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EventTestTimestamp" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& EventTestTimestamp;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Sets the operation mode of the Exposure Auto auto function - Applies to: daA2448-70uc

        Sets the operation mode of the Exposure Auto auto function. The Exposure Auto auto function automatically adjusts the exposure time within set limits until a target brightness value has been reached.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureAuto" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<ExposureAutoEnums>& ExposureAuto;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Sets the exposure mode - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureMode" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<ExposureModeEnums>& ExposureMode;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Exposure time of the camera in microseconds - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ExposureTime" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& ExposureTime;

    //@}


    //! \name Categories: FileAccessControl
    //@{
    /*!
        \brief Access buffer for file operations - Applies to: daA2448-70uc

        Access buffer for file operations. Basler advises against using this parameter. Use the appropriate feature for file access operations instead.
    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileAccessBuffer" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IRegisterEx& FileAccessBuffer;

    //@}


    //! \name Categories: FileAccessControl
    //@{
    /*!
        \brief Number of bytes read from the file into the file access buffer or written to the file from the file access buffer - Applies to: daA2448-70uc

        Number of bytes read from the file into the file access buffer or written to the file from the file access buffer. Basler advises against using this parameter. Use the appropriate feature for file access operations instead.
    
        Visibility: Guru

        Selected by: FileOperationSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileAccessLength" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& FileAccessLength;

    //@}


    //! \name Categories: FileAccessControl
    //@{
    /*!
        \brief Number of bytes after which FileAccessLength bytes are read from the file into the file access buffer or are written to the file from the file access buffer - Applies to: daA2448-70uc

        Number of bytes after which FileAccessLength bytes are read from the file into the file access buffer or are written to the file from the file access buffer. Basler advises against using this parameter. Use the appropriate feature for file access operations instead.
    
        Visibility: Guru

        Selected by: FileOperationSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileAccessOffset" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& FileAccessOffset;

    //@}


    //! \name Categories: FileAccessControl
    //@{
    /*!
        \brief Sets the access mode in which a file is opened in the camera - Applies to: daA2448-70uc

        Sets the access mode in which a file is opened in the camera. Basler advises against using this parameter. Use the appropriate feature for file access operations instead.
    
        Visibility: Beginner

        Selected by: FileSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileOpenMode" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<FileOpenModeEnums>& FileOpenMode;

    //@}


    //! \name Categories: FileAccessControl
    //@{
    /*!
        \brief Executes the operation selected by File Operation Selector parameter - Applies to: daA2448-70uc

        Executes the operation selected by File Operation Selector parameter. Basler advises against using this parameter. Use the appropriate feature for file access operations instead.
    
        Visibility: Guru

        Selected by: FileOperationSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileOperationExecute" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& FileOperationExecute;

    //@}


    //! \name Categories: FileAccessControl
    //@{
    /*!
        \brief File operation result - Applies to: daA2448-70uc

        File operation result. Basler advises against using this parameter. Use the appropriate feature for file access operations instead.
    
        Visibility: Guru

        Selected by: FileOperationSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileOperationResult" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& FileOperationResult;

    //@}


    //! \name Categories: FileAccessControl
    //@{
    /*!
        \brief Sets the target operation for the currently selected file - Applies to: daA2448-70uc

        Sets the target operation for the currently selected file. Basler advises against using this parameter. Use the appropriate feature for file access operations instead.
    
        Visibility: Guru

        Selected by: FileSelector

        Selecting Parameters: FileOperationExecute, FileAccessOffset, FileAccessLength, FileOperationStatus and FileOperationResult

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileOperationSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<FileOperationSelectorEnums>& FileOperationSelector;

    //@}


    //! \name Categories: FileAccessControl
    //@{
    /*!
        \brief Indicates the file operation execution status - Applies to: daA2448-70uc

        Indicates the file operation execution status. Basler advises against using this parameter. Use the appropriate feature for file access operations instead.
    
        Visibility: Guru

        Selected by: FileOperationSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileOperationStatus" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<FileOperationStatusEnums>& FileOperationStatus;

    //@}


    //! \name Categories: FileAccessControl
    //@{
    /*!
        \brief Sets the target file in the camera - Applies to: daA2448-70uc

        Sets the target file in the camera. Basler advises against using this parameter. Use the appropriate feature for file access operations instead.
    
        Visibility: Guru

        Selecting Parameters: FileOperationSelector and FileOpenMode

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FileSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<FileSelectorEnums>& FileSelector;

    //@}


    //! \name Categories: AnalogControl
    //@{
    /*!
        \brief Value of the currently selected gain in dB - Applies to: daA2448-70uc

    
        Visibility: Beginner

        Selected by: GainSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Gain" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& Gain;

    //@}


    //! \name Categories: AnalogControl
    //@{
    /*!
        \brief Sets the operation mode of the Gain Auto auto function - Applies to: daA2448-70uc

        Sets the operation mode of the Gain Auto auto function. The Gain Auto auto function automatically adjusts the gain within set limits until a target brightness value has been reached.
    
        Visibility: Beginner

        Selected by: GainSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=GainAuto" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<GainAutoEnums>& GainAuto;

    //@}


    //! \name Categories: AnalogControl
    //@{
    /*!
        \brief Gamma correction to be applied - Applies to: daA2448-70uc

        Gamma correction to be applied. Gamma correction allows you to optimize the brightness of acquired images for display on a monitor.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Gamma" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& Gamma;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Height of the camera's region of interest (area of interest) in pixels - Applies to: daA2448-70uc

        Height of the camera's region of interest (area of interest) in pixels. Depending on the camera model, the parameter can be set in different increments.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Height" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& Height;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Maximum height of the region of interest (area of interest) in pixels - Applies to: daA2448-70uc

        Maximum height of the region of interest (area of interest) in pixels. The value takes into account any features that may limit the maximum height, e.g., binning.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=HeightMax" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& HeightMax;

    //@}


    //! \name Categories: DigitalIOControl
    //@{
    /*!
        \brief Indicates the electrical configuration of the currently selected line - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: LineSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineFormat" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<LineFormatEnums>& LineFormat;

    //@}


    //! \name Categories: DigitalIOControl
    //@{
    /*!
        \brief Enables the signal inverter function for the currently selected input or output line - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: LineSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineInverter" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& LineInverter;

    //@}


    //! \name Categories: DigitalIOControl
    //@{
    /*!
        \brief Sets the mode for the selected line - Applies to: daA2448-70uc

        Sets the mode for the selected line. This controls whether the physical line is used to input or output a signal.
    
        Visibility: Expert

        Selected by: LineSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineMode" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<LineModeEnums>& LineMode;

    //@}


    //! \name Categories: DigitalIOControl
    //@{
    /*!
        \brief Sets the I/O line to be configured - Applies to: daA2448-70uc

        Sets the I/O line to be configured. All changes to the line settings will be applied to the selected line.
    
        Visibility: Expert

        Selecting Parameters: LineMode, LineFormat, LineSource, LineInverter, LineStatus, BslInputFilterTime, BslInputHoldOffTime and BslLineConnection

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<LineSelectorEnums>& LineSelector;

    //@}


    //! \name Categories: DigitalIOControl
    //@{
    /*!
        \brief Sets the source signal for the currently selected line - Applies to: daA2448-70uc

        Sets the source signal for the currently selected line. The currently selected line must be an output line.
    
        Visibility: Expert

        Selected by: LineSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineSource" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<LineSourceEnums>& LineSource;

    //@}


    //! \name Categories: DigitalIOControl
    //@{
    /*!
        \brief Indicates the current logical state of the selected line - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: LineSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineStatus" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& LineStatus;

    //@}


    //! \name Categories: DigitalIOControl
    //@{
    /*!
        \brief Single bit field indicating the current logical state of all available line signals at time of polling - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=LineStatusAll" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& LineStatusAll;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Horizontal offset of the region of interest (area of interest) from the left side of the sensor (in pixels) - Applies to: daA2448-70uc

        Horizontal offset from the left side of the sensor to the region of interest (area of interest) (in pixels).
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OffsetX" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& OffsetX;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Vertical offset of the region of interest (area of interest) from the top of the sensor (in pixels) - Applies to: daA2448-70uc

        Vertical offset from the top of the sensor to the region of interest (area of interest) (in pixels).
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=OffsetY" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& OffsetY;

    //@}


    //! \name Categories: TransportLayerControl
    //@{
    /*!
        \brief Size of the payload in bytes - Applies to: daA2448-70uc

        Size of the payload in bytes. This is the total number of bytes sent in the payload.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PayloadSize" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& PayloadSize;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Maximum possible pixel value that can be transferred from the camera - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelDynamicRangeMax" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& PixelDynamicRangeMax;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Minimum possible pixel value that can be transferred from the camera - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelDynamicRangeMin" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& PixelDynamicRangeMin;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Sets the format of the pixel data transmitted by the camera - Applies to: daA2448-70uc

        Sets the format of the pixel data transmitted by the camera. The available pixel formats depend on the camera model and whether the camera is monochrome or color.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelFormat" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<PixelFormatEnums>& PixelFormat;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Indicates the depth of the pixel values in the image (in bits per pixel) - Applies to: daA2448-70uc

        Indicates the depth of the pixel values in the image (in bits per pixel). The potential values depend on the pixel format setting.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelSize" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<PixelSizeEnums>& PixelSize;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Enables horizontal mirroring of the image - Applies to: daA2448-70uc

        Enables horizontal mirroring of the image. The pixel values of every line in a captured image will be swapped along the line's center. You can use the ROI feature when using the Reverse X feature. The position of the ROI relative to the sensor remains the same.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ReverseX" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& ReverseX;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Enables vertical mirroring of the image - Applies to: daA2448-70uc

        Enables vertical mirroring of the image. The pixel values of every column in a captured image will be swapped along the column's center. You can use the ROI feature when using the Reverse Y feature. The position of the ROI relative to the sensor remains the same.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ReverseY" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& ReverseY;

    //@}


    //! \name Categories: TransportLayerControl
    //@{
    /*!
        \brief For information only  May be required when contacting Basler support - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SIPayloadFinalTransfer1Size" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& SIPayloadFinalTransfer1Size;

    //@}


    //! \name Categories: TransportLayerControl
    //@{
    /*!
        \brief For information only  May be required when contacting Basler support - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SIPayloadFinalTransfer2Size" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& SIPayloadFinalTransfer2Size;

    //@}


    //! \name Categories: TransportLayerControl
    //@{
    /*!
        \brief For information only  May be required when contacting Basler support - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SIPayloadTransferCount" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& SIPayloadTransferCount;

    //@}


    //! \name Categories: TransportLayerControl
    //@{
    /*!
        \brief For information only  May be required when contacting Basler support - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SIPayloadTransferSize" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& SIPayloadTransferSize;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Height of the camera's sensor in pixels - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SensorHeight" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& SensorHeight;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Sensor readout time with current settings - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SensorReadoutTime" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& SensorReadoutTime;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Width of the camera's sensor in pixels - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SensorWidth" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& SensorWidth;

    //@}


    //! \name Categories: SoftwareSignalControl
    //@{
    /*!
        \brief Executes the selected software signal - Applies to: daA2448-70uc

    
        Visibility: Beginner

        Selected by: SoftwareSignalSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SoftwareSignalPulse" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& SoftwareSignalPulse;

    //@}


    //! \name Categories: SoftwareSignalControl
    //@{
    /*!
        \brief Sets the software signal to be executed - Applies to: daA2448-70uc

    
        Visibility: Beginner

        Selecting Parameters: SoftwareSignalPulse

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SoftwareSignalSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<SoftwareSignalSelectorEnums>& SoftwareSignalSelector;

    //@}


    //! \name Categories: TestControl
    //@{
    /*!
        \brief Generates a Test event that can be used for testing event notification - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TestEventGenerate" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& TestEventGenerate;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Sets the test pattern to display - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TestPattern" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<TestPatternEnums>& TestPattern;

    //@}


    //! \name Categories: TestControl
    //@{
    /*!
        \brief Test pending acknowledge time in milliseconds - Applies to: daA2448-70uc

        Test pending acknowledge time in milliseconds. On write, the camera waits for this time period before acknowledging the write. If the time period is longer than the value in the Maximum Device Response Time register, the camera must use PENDING_ACK during the completion of this request. On reads, the camera returns the current value without any additional wait time.
    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TestPendingAck" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& TestPendingAck;

    //@}


    //! \name Categories: TimerControl
    //@{
    /*!
        \brief Delay of the currently selected timer in microseconds - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: TimerSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerDelay" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& TimerDelay;

    //@}


    //! \name Categories: TimerControl
    //@{
    /*!
        \brief Duration of the currently selected timer in microseconds - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: TimerSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerDuration" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& TimerDuration;

    //@}


    //! \name Categories: TimerControl
    //@{
    /*!
        \brief Resets the selected timer - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: TimerSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerReset" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& TimerReset;

    //@}


    //! \name Categories: TimerControl
    //@{
    /*!
        \brief Sets the timer to be configured - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selecting Parameters: TimerTriggerSource, TimerTriggerActivation, TimerDelay, TimerDuration, TimerTriggerArmDelay, TimerStatus and TimerReset

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<TimerSelectorEnums>& TimerSelector;

    //@}


    //! \name Categories: TimerControl
    //@{
    /*!
        \brief Indicates the status of the currently selected timer - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: TimerSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerStatus" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<TimerStatusEnums>& TimerStatus;

    //@}


    //! \name Categories: TimerControl
    //@{
    /*!
        \brief Sets the type of signal transition that will start the timer - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: TimerSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerTriggerActivation" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<TimerTriggerActivationEnums>& TimerTriggerActivation;

    //@}


    //! \name Categories: TimerControl
    //@{
    /*!
        \brief Arm delay of the currently selected timer - Applies to: daA2448-70uc

        Arm delay of the currently selected timer. If an arm delay is set and the timer is triggered, the camera accepts the trigger signal and stops accepting any further timer trigger signals until the arm delay has elapsed.
    
        Visibility: Expert

        Selected by: TimerSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerTriggerArmDelay" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& TimerTriggerArmDelay;

    //@}


    //! \name Categories: TimerControl
    //@{
    /*!
        \brief Sets the internal camera signal used to trigger the selected timer - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: TimerSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimerTriggerSource" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<TimerTriggerSourceEnums>& TimerTriggerSource;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Latches the current timestamp counter and stores its value in TimestampLatchValue - Applies to: daA2448-70uc

        Latches the current timestamp counter and stores its value in the Timestamp Latch Value parameter.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimestampLatch" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& TimestampLatch;

    //@}


    //! \name Categories: DeviceControl
    //@{
    /*!
        \brief Latched value of the timestamp counter - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TimestampLatchValue" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& TimestampLatchValue;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Sets the type of signal transition that will activate the selected trigger - Applies to: daA2448-70uc

    
        Visibility: Beginner

        Selected by: TriggerSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerActivation" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<TriggerActivationEnums>& TriggerActivation;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Trigger delay time in microseconds - Applies to: daA2448-70uc

        Trigger delay time in microseconds. The delay is applied after the trigger has been received and before effectively activating the trigger.
    
        Visibility: Expert

        Selected by: TriggerSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerDelay" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IFloatEx& TriggerDelay;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Sets the mode for the currently selected trigger - Applies to: daA2448-70uc

    
        Visibility: Beginner

        Selected by: TriggerSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerMode" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<TriggerModeEnums>& TriggerMode;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Sets the trigger type to be configured - Applies to: daA2448-70uc

        Sets the trigger type to be configured. All changes to the trigger settings will be applied to the selected trigger.
    
        Visibility: Beginner

        Selecting Parameters: TriggerMode, TriggerSource, TriggerActivation, TriggerSoftware and TriggerDelay

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<TriggerSelectorEnums>& TriggerSelector;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Generates a software trigger signal - Applies to: daA2448-70uc

        Generates a software trigger signal. The software trigger signal will be used if the Trigger Source parameter is set to Trigger Software.
    
        Visibility: Beginner

        Selected by: TriggerSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerSoftware" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& TriggerSoftware;

    //@}


    //! \name Categories: AcquisitionControl
    //@{
    /*!
        \brief Sets the source signal for the selected trigger - Applies to: daA2448-70uc

    
        Visibility: Beginner

        Selected by: TriggerSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TriggerSource" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<TriggerSourceEnums>& TriggerSource;

    //@}


    //! \name Categories: UserDefinedValues
    //@{
    /*!
        \brief User-defined value - Applies to: daA2448-70uc

        User-defined value. The value can serve as storage location for the camera user. It has no impact on the operation of the camera.
    
        Visibility: Guru

        Selected by: UserDefinedValueSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserDefinedValue" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& UserDefinedValue;

    //@}


    //! \name Categories: UserDefinedValues
    //@{
    /*!
        \brief Sets the user-defined value to set or read - Applies to: daA2448-70uc

    
        Visibility: Guru

        Selecting Parameters: UserDefinedValue

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserDefinedValueSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<UserDefinedValueSelectorEnums>& UserDefinedValueSelector;

    //@}


    //! \name Categories: DigitalIOControl
    //@{
    /*!
        \brief Sets the user-settable output signal to be configured - Applies to: daA2448-70uc

        Sets the user-settable output signal to be configured. All changes to the user-settable output signal settings will be applied to the selected user-settable output signal.
    
        Visibility: Expert

        Selecting Parameters: UserOutputValue

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserOutputSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<UserOutputSelectorEnums>& UserOutputSelector;

    //@}


    //! \name Categories: DigitalIOControl
    //@{
    /*!
        \brief Enables the selected user-settable output line - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: UserOutputSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserOutputValue" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& UserOutputValue;

    //@}


    //! \name Categories: DigitalIOControl
    //@{
    /*!
        \brief Single bit field that sets the state of all user-settable output signals in one access - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserOutputValueAll" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& UserOutputValueAll;

    //@}


    //! \name Categories: UserSetControl
    //@{
    /*!
        \brief Sets the user set or the factory set to be used as the startup set - Applies to: daA2448-70uc

        Sets the user set or the factory set to be used as the startup set. The startup set will be loaded as the active set whenever the camera is powered on or reset.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserSetDefault" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<UserSetDefaultEnums>& UserSetDefault;

    //@}


    //! \name Categories: UserSetControl
    //@{
    /*!
        \brief Loads the selected set into the camera's volatile memory and makes it the active configuration set - Applies to: daA2448-70uc

        Loads the selected set into the camera's volatile memory and makes it the active configuration set. After the selected set has been loaded, the parameters in that set will control the camera.
    
        Visibility: Beginner

        Selected by: UserSetSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserSetLoad" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& UserSetLoad;

    //@}


    //! \name Categories: UserSetControl
    //@{
    /*!
        \brief Saves the current active set as the selected user set - Applies to: daA2448-70uc

    
        Visibility: Beginner

        Selected by: UserSetSelector

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserSetSave" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::ICommandEx& UserSetSave;

    //@}


    //! \name Categories: UserSetControl
    //@{
    /*!
        \brief Sets the user set or the factory set to load, save, or configure - Applies to: daA2448-70uc

    
        Visibility: Beginner

        Selecting Parameters: UserSetLoad and UserSetSave

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=UserSetSelector" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IEnumParameterT<UserSetSelectorEnums>& UserSetSelector;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Width of the camera's region of interest (area of interest) in pixels - Applies to: daA2448-70uc

        Width of the camera's region of interest (area of interest) in pixels. Depending on the camera model, the parameter can be set in different increments.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Width" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& Width;

    //@}


    //! \name Categories: ImageFormatControl
    //@{
    /*!
        \brief Maximum width of the region of interest (area of interest) in pixels - Applies to: daA2448-70uc

        Maximum width of the region of interest (area of interest) in pixels. The value takes into account any function that may limit the maximum width.
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=WidthMax" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& WidthMax;

    //@}


        private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
            BaslerCameraCameraParams(BaslerCameraCameraParams&);

            //! not implemented assignment operator
            BaslerCameraCameraParams& operator=(BaslerCameraCameraParams&);

        //! \endcond
    };

} // namespace Pylon
} // namespace BaslerCameraCameraParams_Params

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // BASLER_PYLON_BASLERCAMERACAMERAPARAMS_H