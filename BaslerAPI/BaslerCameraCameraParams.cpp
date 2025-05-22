//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2023-2025 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------

// common parameter types
#if defined(PYLON_GENERATED_PARAMETER_CLASSES_USE_STDAFX)
#include "stdafx.h"
#endif
#include "BaslerCameraCameraParams.h"

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
    // Enumeration support classes
    //**************************************************************************************************
    //! \cond HIDE_CLASS_METHODS

    ///////////////////////////////////////////////////////////////////////////
    //
    namespace EnumParameterClasses
    {
        ///////////////////////////////////////////////////////////////////////////
        //
        class AcquisitionModeEnumParameter : public Pylon::CEnumParameterT<AcquisitionModeEnums>
        {
        public:
            AcquisitionModeEnumParameter()
            {
            }

            virtual ~AcquisitionModeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Continuous", 11),
                    TableItem_t("SingleFrame", 12)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class AcquisitionStatusSelectorEnumParameter : public Pylon::CEnumParameterT<AcquisitionStatusSelectorEnums>
        {
        public:
            AcquisitionStatusSelectorEnumParameter()
            {
            }

            virtual ~AcquisitionStatusSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 6;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("AcquisitionActive", 18),
                    TableItem_t("ExposureActive", 15),
                    TableItem_t("ExposureTriggerWait", 20),
                    TableItem_t("FrameBurstActive", 17),
                    TableItem_t("FrameBurstTriggerWait", 22),
                    TableItem_t("FrameTriggerWait", 17)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class AutoFunctionProfileEnumParameter : public Pylon::CEnumParameterT<AutoFunctionProfileEnums>
        {
        public:
            AutoFunctionProfileEnumParameter()
            {
            }

            virtual ~AutoFunctionProfileEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("MinimizeExposureTime", 21),
                    TableItem_t("MinimizeGain", 13)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class AutoFunctionROISelectorEnumParameter : public Pylon::CEnumParameterT<AutoFunctionROISelectorEnums>
        {
        public:
            AutoFunctionROISelectorEnumParameter()
            {
            }

            virtual ~AutoFunctionROISelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("ROI1", 5),
                    TableItem_t("ROI2", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BalanceRatioSelectorEnumParameter : public Pylon::CEnumParameterT<BalanceRatioSelectorEnums>
        {
        public:
            BalanceRatioSelectorEnumParameter()
            {
            }

            virtual ~BalanceRatioSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Blue", 5),
                    TableItem_t("Green", 6),
                    TableItem_t("Red", 4)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BalanceWhiteAutoEnumParameter : public Pylon::CEnumParameterT<BalanceWhiteAutoEnums>
        {
        public:
            BalanceWhiteAutoEnumParameter()
            {
            }

            virtual ~BalanceWhiteAutoEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Continuous", 11),
                    TableItem_t("Off", 4),
                    TableItem_t("Once", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslAcquisitionBurstModeEnumParameter : public Pylon::CEnumParameterT<BslAcquisitionBurstModeEnums>
        {
        public:
            BslAcquisitionBurstModeEnumParameter()
            {
            }

            virtual ~BslAcquisitionBurstModeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("HighSpeed", 10),
                    TableItem_t("Standard", 9)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslAcquisitionStopModeEnumParameter : public Pylon::CEnumParameterT<BslAcquisitionStopModeEnums>
        {
        public:
            BslAcquisitionStopModeEnumParameter()
            {
            }

            virtual ~BslAcquisitionStopModeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("AbortExposure", 14),
                    TableItem_t("CompleteExposure", 17)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslChunkAutoBrightnessStatusEnumParameter : public Pylon::CEnumParameterT<BslChunkAutoBrightnessStatusEnums>
        {
        public:
            BslChunkAutoBrightnessStatusEnumParameter()
            {
            }

            virtual ~BslChunkAutoBrightnessStatusEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 1;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Todo", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslChunkTimestampSelectorEnumParameter : public Pylon::CEnumParameterT<BslChunkTimestampSelectorEnums>
        {
        public:
            BslChunkTimestampSelectorEnumParameter()
            {
            }

            virtual ~BslChunkTimestampSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("ExposureEnd", 12),
                    TableItem_t("ExposureStart", 14),
                    TableItem_t("FrameStart", 11)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslColorSpaceEnumParameter : public Pylon::CEnumParameterT<BslColorSpaceEnums>
        {
        public:
            BslColorSpaceEnumParameter()
            {
            }

            virtual ~BslColorSpaceEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Off", 4),
                    TableItem_t("sRgb", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslContrastModeEnumParameter : public Pylon::CEnumParameterT<BslContrastModeEnums>
        {
        public:
            BslContrastModeEnumParameter()
            {
            }

            virtual ~BslContrastModeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Linear", 7),
                    TableItem_t("SCurve", 7)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslDefectPixelCorrectionModeEnumParameter : public Pylon::CEnumParameterT<BslDefectPixelCorrectionModeEnums>
        {
        public:
            BslDefectPixelCorrectionModeEnumParameter()
            {
            }

            virtual ~BslDefectPixelCorrectionModeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Off", 4),
                    TableItem_t("On", 3),
                    TableItem_t("StaticOnly", 11)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslLightSourcePresetEnumParameter : public Pylon::CEnumParameterT<BslLightSourcePresetEnums>
        {
        public:
            BslLightSourcePresetEnumParameter()
            {
            }

            virtual ~BslLightSourcePresetEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 5;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Daylight5000K", 14),
                    TableItem_t("Daylight6500K", 14),
                    TableItem_t("FactoryLED6000K", 16),
                    TableItem_t("Off", 4),
                    TableItem_t("Tungsten", 9)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslLightSourcePresetFeatureSelectorEnumParameter : public Pylon::CEnumParameterT<BslLightSourcePresetFeatureSelectorEnums>
        {
        public:
            BslLightSourcePresetFeatureSelectorEnumParameter()
            {
            }

            virtual ~BslLightSourcePresetFeatureSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("ColorAdjustment", 16),
                    TableItem_t("ColorTransformation", 20),
                    TableItem_t("WhiteBalance", 13)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslLineConnectionEnumParameter : public Pylon::CEnumParameterT<BslLineConnectionEnums>
        {
        public:
            BslLineConnectionEnumParameter()
            {
            }

            virtual ~BslLineConnectionEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("ConnectionOff", 14),
                    TableItem_t("TwiScl", 7),
                    TableItem_t("TwiSda", 7)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslSensorBitDepthEnumParameter : public Pylon::CEnumParameterT<BslSensorBitDepthEnums>
        {
        public:
            BslSensorBitDepthEnumParameter()
            {
            }

            virtual ~BslSensorBitDepthEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Bpp10", 6),
                    TableItem_t("Bpp12", 6),
                    TableItem_t("Bpp8", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslSensorBitDepthModeEnumParameter : public Pylon::CEnumParameterT<BslSensorBitDepthModeEnums>
        {
        public:
            BslSensorBitDepthModeEnumParameter()
            {
            }

            virtual ~BslSensorBitDepthModeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Auto", 5),
                    TableItem_t("Manual", 7)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslSensorStateEnumParameter : public Pylon::CEnumParameterT<BslSensorStateEnums>
        {
        public:
            BslSensorStateEnumParameter()
            {
            }

            virtual ~BslSensorStateEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Off", 4),
                    TableItem_t("On", 3),
                    TableItem_t("Standby", 8)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslTemperatureStatusEnumParameter : public Pylon::CEnumParameterT<BslTemperatureStatusEnums>
        {
        public:
            BslTemperatureStatusEnumParameter()
            {
            }

            virtual ~BslTemperatureStatusEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Critical", 9),
                    TableItem_t("Error", 6),
                    TableItem_t("Ok", 3)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslTwiBitrateEnumParameter : public Pylon::CEnumParameterT<BslTwiBitrateEnums>
        {
        public:
            BslTwiBitrateEnumParameter()
            {
            }

            virtual ~BslTwiBitrateEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 6;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Bitrate100kbps", 15),
                    TableItem_t("Bitrate10kbps", 14),
                    TableItem_t("Bitrate200kbps", 15),
                    TableItem_t("Bitrate20kbps", 14),
                    TableItem_t("Bitrate400kbps", 15),
                    TableItem_t("Bitrate50kbps", 14)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslTwiTransferStatusEnumParameter : public Pylon::CEnumParameterT<BslTwiTransferStatusEnums>
        {
        public:
            BslTwiTransferStatusEnumParameter()
            {
            }

            virtual ~BslTwiTransferStatusEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 4;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("NakAddress", 11),
                    TableItem_t("NakData", 8),
                    TableItem_t("Pending", 8),
                    TableItem_t("Success", 8)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslUSBPowerSourceEnumParameter : public Pylon::CEnumParameterT<BslUSBPowerSourceEnums>
        {
        public:
            BslUSBPowerSourceEnumParameter()
            {
            }

            virtual ~BslUSBPowerSourceEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Aux", 4),
                    TableItem_t("Bus", 4)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class BslUSBSpeedModeEnumParameter : public Pylon::CEnumParameterT<BslUSBSpeedModeEnums>
        {
        public:
            BslUSBSpeedModeEnumParameter()
            {
            }

            virtual ~BslUSBSpeedModeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 4;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("FullSpeed", 10),
                    TableItem_t("HighSpeed", 10),
                    TableItem_t("LowSpeed", 9),
                    TableItem_t("SuperSpeed", 11)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class ChunkCounterSelectorEnumParameter : public Pylon::CEnumParameterT<ChunkCounterSelectorEnums>
        {
        public:
            ChunkCounterSelectorEnumParameter()
            {
            }

            virtual ~ChunkCounterSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Counter1", 9),
                    TableItem_t("Counter2", 9)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class ChunkSelectorEnumParameter : public Pylon::CEnumParameterT<ChunkSelectorEnums>
        {
        public:
            ChunkSelectorEnumParameter()
            {
            }

            virtual ~ChunkSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 8;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("AutoBrightnessStatus", 21),
                    TableItem_t("CounterValue", 13),
                    TableItem_t("ExposureTime", 13),
                    TableItem_t("FrameID", 8),
                    TableItem_t("Gain", 5),
                    TableItem_t("LineStatusAll", 14),
                    TableItem_t("PayloadCRC16", 13),
                    TableItem_t("Timestamp", 10)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class CounterEventActivationEnumParameter : public Pylon::CEnumParameterT<CounterEventActivationEnums>
        {
        public:
            CounterEventActivationEnumParameter()
            {
            }

            virtual ~CounterEventActivationEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 1;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Todo", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class CounterEventSourceEnumParameter : public Pylon::CEnumParameterT<CounterEventSourceEnums>
        {
        public:
            CounterEventSourceEnumParameter()
            {
            }

            virtual ~CounterEventSourceEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 25;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("AcquisitionActive", 18),
                    TableItem_t("Counter1Active", 15),
                    TableItem_t("Counter1End", 12),
                    TableItem_t("Counter1Start", 14),
                    TableItem_t("Counter2Active", 15),
                    TableItem_t("Counter2End", 12),
                    TableItem_t("Counter2Start", 14),
                    TableItem_t("ExposureActive", 15),
                    TableItem_t("ExposureStart", 14),
                    TableItem_t("ExposureTriggerWait", 20),
                    TableItem_t("FrameBurstActive", 17),
                    TableItem_t("FrameBurstTriggerWait", 22),
                    TableItem_t("FrameTriggerWait", 17),
                    TableItem_t("Line1", 6),
                    TableItem_t("Line2", 6),
                    TableItem_t("Line3", 6),
                    TableItem_t("Line4", 6),
                    TableItem_t("Off", 4),
                    TableItem_t("SoftwareSignal1", 16),
                    TableItem_t("SoftwareSignal2", 16),
                    TableItem_t("SoftwareSignal3", 16),
                    TableItem_t("Timer1Active", 13),
                    TableItem_t("Timer1End", 10),
                    TableItem_t("Timer2Active", 13),
                    TableItem_t("Timer2End", 10)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class CounterResetActivationEnumParameter : public Pylon::CEnumParameterT<CounterResetActivationEnums>
        {
        public:
            CounterResetActivationEnumParameter()
            {
            }

            virtual ~CounterResetActivationEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 1;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Todo", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class CounterResetSourceEnumParameter : public Pylon::CEnumParameterT<CounterResetSourceEnums>
        {
        public:
            CounterResetSourceEnumParameter()
            {
            }

            virtual ~CounterResetSourceEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 25;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("AcquisitionActive", 18),
                    TableItem_t("Counter1Active", 15),
                    TableItem_t("Counter1End", 12),
                    TableItem_t("Counter1Start", 14),
                    TableItem_t("Counter2Active", 15),
                    TableItem_t("Counter2End", 12),
                    TableItem_t("Counter2Start", 14),
                    TableItem_t("ExposureActive", 15),
                    TableItem_t("ExposureStart", 14),
                    TableItem_t("ExposureTriggerWait", 20),
                    TableItem_t("FrameBurstActive", 17),
                    TableItem_t("FrameBurstTriggerWait", 22),
                    TableItem_t("FrameTriggerWait", 17),
                    TableItem_t("Line1", 6),
                    TableItem_t("Line2", 6),
                    TableItem_t("Line3", 6),
                    TableItem_t("Line4", 6),
                    TableItem_t("Off", 4),
                    TableItem_t("SoftwareSignal1", 16),
                    TableItem_t("SoftwareSignal2", 16),
                    TableItem_t("SoftwareSignal3", 16),
                    TableItem_t("Timer1Active", 13),
                    TableItem_t("Timer1End", 10),
                    TableItem_t("Timer2Active", 13),
                    TableItem_t("Timer2End", 10)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class CounterSelectorEnumParameter : public Pylon::CEnumParameterT<CounterSelectorEnums>
        {
        public:
            CounterSelectorEnumParameter()
            {
            }

            virtual ~CounterSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Counter1", 9),
                    TableItem_t("Counter2", 9)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class CounterStatusEnumParameter : public Pylon::CEnumParameterT<CounterStatusEnums>
        {
        public:
            CounterStatusEnumParameter()
            {
            }

            virtual ~CounterStatusEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("CounterActive", 14),
                    TableItem_t("CounterCompleted", 17),
                    TableItem_t("CounterTriggerWait", 19)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class CounterTriggerActivationEnumParameter : public Pylon::CEnumParameterT<CounterTriggerActivationEnums>
        {
        public:
            CounterTriggerActivationEnumParameter()
            {
            }

            virtual ~CounterTriggerActivationEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 1;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Todo", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class CounterTriggerSourceEnumParameter : public Pylon::CEnumParameterT<CounterTriggerSourceEnums>
        {
        public:
            CounterTriggerSourceEnumParameter()
            {
            }

            virtual ~CounterTriggerSourceEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 25;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("AcquisitionActive", 18),
                    TableItem_t("Counter1Active", 15),
                    TableItem_t("Counter1End", 12),
                    TableItem_t("Counter1Start", 14),
                    TableItem_t("Counter2Active", 15),
                    TableItem_t("Counter2End", 12),
                    TableItem_t("Counter2Start", 14),
                    TableItem_t("ExposureActive", 15),
                    TableItem_t("ExposureStart", 14),
                    TableItem_t("ExposureTriggerWait", 20),
                    TableItem_t("FrameBurstActive", 17),
                    TableItem_t("FrameBurstTriggerWait", 22),
                    TableItem_t("FrameTriggerWait", 17),
                    TableItem_t("Line1", 6),
                    TableItem_t("Line2", 6),
                    TableItem_t("Line3", 6),
                    TableItem_t("Line4", 6),
                    TableItem_t("Off", 4),
                    TableItem_t("SoftwareSignal1", 16),
                    TableItem_t("SoftwareSignal2", 16),
                    TableItem_t("SoftwareSignal3", 16),
                    TableItem_t("Timer1Active", 13),
                    TableItem_t("Timer1End", 10),
                    TableItem_t("Timer2Active", 13),
                    TableItem_t("Timer2End", 10)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class DeviceCharacterSetEnumParameter : public Pylon::CEnumParameterT<DeviceCharacterSetEnums>
        {
        public:
            DeviceCharacterSetEnumParameter()
            {
            }

            virtual ~DeviceCharacterSetEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 1;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("UTF8", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class DeviceIndicatorModeEnumParameter : public Pylon::CEnumParameterT<DeviceIndicatorModeEnums>
        {
        public:
            DeviceIndicatorModeEnumParameter()
            {
            }

            virtual ~DeviceIndicatorModeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Active", 7),
                    TableItem_t("ErrorStatus", 12),
                    TableItem_t("Inactive", 9)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class DeviceLinkThroughputLimitModeEnumParameter : public Pylon::CEnumParameterT<DeviceLinkThroughputLimitModeEnums>
        {
        public:
            DeviceLinkThroughputLimitModeEnumParameter()
            {
            }

            virtual ~DeviceLinkThroughputLimitModeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Off", 4),
                    TableItem_t("On", 3)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class DeviceRegistersEndiannessEnumParameter : public Pylon::CEnumParameterT<DeviceRegistersEndiannessEnums>
        {
        public:
            DeviceRegistersEndiannessEnumParameter()
            {
            }

            virtual ~DeviceRegistersEndiannessEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Big", 4),
                    TableItem_t("Little", 7)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class DeviceScanTypeEnumParameter : public Pylon::CEnumParameterT<DeviceScanTypeEnums>
        {
        public:
            DeviceScanTypeEnumParameter()
            {
            }

            virtual ~DeviceScanTypeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Areascan", 9),
                    TableItem_t("Linescan", 9)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class DeviceTLTypeEnumParameter : public Pylon::CEnumParameterT<DeviceTLTypeEnums>
        {
        public:
            DeviceTLTypeEnumParameter()
            {
            }

            virtual ~DeviceTLTypeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("CoaXPress", 10),
                    TableItem_t("GigEVision", 11),
                    TableItem_t("USB3Vision", 11)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class DeviceTemperatureSelectorEnumParameter : public Pylon::CEnumParameterT<DeviceTemperatureSelectorEnums>
        {
        public:
            DeviceTemperatureSelectorEnumParameter()
            {
            }

            virtual ~DeviceTemperatureSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("FpgaCore", 9),
                    TableItem_t("Sensor", 7)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class EventNotificationEnumParameter : public Pylon::CEnumParameterT<EventNotificationEnums>
        {
        public:
            EventNotificationEnumParameter()
            {
            }

            virtual ~EventNotificationEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Off", 4),
                    TableItem_t("On", 3)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class EventSelectorEnumParameter : public Pylon::CEnumParameterT<EventSelectorEnums>
        {
        public:
            EventSelectorEnumParameter()
            {
            }

            virtual ~EventSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 6;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("ExposureEnd", 12),
                    TableItem_t("FrameStart", 11),
                    TableItem_t("FrameTriggerMissed", 19),
                    TableItem_t("Overrun", 8),
                    TableItem_t("TemperatureStatusChanged", 25),
                    TableItem_t("Test", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class EventTemperatureStatusChangedStatusEnumParameter : public Pylon::CEnumParameterT<EventTemperatureStatusChangedStatusEnums>
        {
        public:
            EventTemperatureStatusChangedStatusEnumParameter()
            {
            }

            virtual ~EventTemperatureStatusChangedStatusEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 1;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Todo", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class ExposureAutoEnumParameter : public Pylon::CEnumParameterT<ExposureAutoEnums>
        {
        public:
            ExposureAutoEnumParameter()
            {
            }

            virtual ~ExposureAutoEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Continuous", 11),
                    TableItem_t("Off", 4),
                    TableItem_t("Once", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class ExposureModeEnumParameter : public Pylon::CEnumParameterT<ExposureModeEnums>
        {
        public:
            ExposureModeEnumParameter()
            {
            }

            virtual ~ExposureModeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Timed", 6),
                    TableItem_t("TriggerControlled", 18),
                    TableItem_t("TriggerWidth", 13)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class FileOpenModeEnumParameter : public Pylon::CEnumParameterT<FileOpenModeEnums>
        {
        public:
            FileOpenModeEnumParameter()
            {
            }

            virtual ~FileOpenModeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Read", 5),
                    TableItem_t("Write", 6)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class FileOperationSelectorEnumParameter : public Pylon::CEnumParameterT<FileOperationSelectorEnums>
        {
        public:
            FileOperationSelectorEnumParameter()
            {
            }

            virtual ~FileOperationSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 4;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Close", 6),
                    TableItem_t("Open", 5),
                    TableItem_t("Read", 5),
                    TableItem_t("Write", 6)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class FileOperationStatusEnumParameter : public Pylon::CEnumParameterT<FileOperationStatusEnums>
        {
        public:
            FileOperationStatusEnumParameter()
            {
            }

            virtual ~FileOperationStatusEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Failure", 8),
                    TableItem_t("Success", 8)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class FileSelectorEnumParameter : public Pylon::CEnumParameterT<FileSelectorEnums>
        {
        public:
            FileSelectorEnumParameter()
            {
            }

            virtual ~FileSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 6;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("BootUpdate", 11),
                    TableItem_t("BootUpdatePackage", 18),
                    TableItem_t("FirmwareUpdate", 15),
                    TableItem_t("FirmwareUpdatePackage", 22),
                    TableItem_t("None", 5),
                    TableItem_t("UserData", 9)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class GainAutoEnumParameter : public Pylon::CEnumParameterT<GainAutoEnums>
        {
        public:
            GainAutoEnumParameter()
            {
            }

            virtual ~GainAutoEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Continuous", 11),
                    TableItem_t("Off", 4),
                    TableItem_t("Once", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class LineFormatEnumParameter : public Pylon::CEnumParameterT<LineFormatEnums>
        {
        public:
            LineFormatEnumParameter()
            {
            }

            virtual ~LineFormatEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("LVTTL", 6),
                    TableItem_t("OpenDrain", 10),
                    TableItem_t("OptoCoupled", 12)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class LineModeEnumParameter : public Pylon::CEnumParameterT<LineModeEnums>
        {
        public:
            LineModeEnumParameter()
            {
            }

            virtual ~LineModeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("InOut", 6),
                    TableItem_t("Input", 6),
                    TableItem_t("Output", 7)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class LineSelectorEnumParameter : public Pylon::CEnumParameterT<LineSelectorEnums>
        {
        public:
            LineSelectorEnumParameter()
            {
            }

            virtual ~LineSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 4;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Line1", 6),
                    TableItem_t("Line2", 6),
                    TableItem_t("Line3", 6),
                    TableItem_t("Line4", 6)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class LineSourceEnumParameter : public Pylon::CEnumParameterT<LineSourceEnums>
        {
        public:
            LineSourceEnumParameter()
            {
            }

            virtual ~LineSourceEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 15;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("AcquisitionActive", 18),
                    TableItem_t("Counter1Active", 15),
                    TableItem_t("Counter2Active", 15),
                    TableItem_t("ExposureActive", 15),
                    TableItem_t("ExposureTriggerWait", 20),
                    TableItem_t("FrameBurstActive", 17),
                    TableItem_t("FrameBurstTriggerWait", 22),
                    TableItem_t("FrameTriggerWait", 17),
                    TableItem_t("Off", 4),
                    TableItem_t("Timer1Active", 13),
                    TableItem_t("Timer2Active", 13),
                    TableItem_t("UserOutput1", 12),
                    TableItem_t("UserOutput2", 12),
                    TableItem_t("UserOutput3", 12),
                    TableItem_t("UserOutput4", 12)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class PixelFormatEnumParameter : public Pylon::CEnumParameterT<PixelFormatEnums>
        {
        public:
            PixelFormatEnumParameter()
            {
            }

            virtual ~PixelFormatEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 29;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("BGR8", 5),
                    TableItem_t("BayerBG10", 10),
                    TableItem_t("BayerBG10p", 11),
                    TableItem_t("BayerBG12", 10),
                    TableItem_t("BayerBG12p", 11),
                    TableItem_t("BayerBG8", 9),
                    TableItem_t("BayerGB10", 10),
                    TableItem_t("BayerGB10p", 11),
                    TableItem_t("BayerGB12", 10),
                    TableItem_t("BayerGB12p", 11),
                    TableItem_t("BayerGB8", 9),
                    TableItem_t("BayerGR10", 10),
                    TableItem_t("BayerGR10p", 11),
                    TableItem_t("BayerGR12", 10),
                    TableItem_t("BayerGR12p", 11),
                    TableItem_t("BayerGR8", 9),
                    TableItem_t("BayerRG10", 10),
                    TableItem_t("BayerRG10p", 11),
                    TableItem_t("BayerRG12", 10),
                    TableItem_t("BayerRG12p", 11),
                    TableItem_t("BayerRG8", 9),
                    TableItem_t("Mono10", 7),
                    TableItem_t("Mono10p", 8),
                    TableItem_t("Mono12", 7),
                    TableItem_t("Mono12p", 8),
                    TableItem_t("Mono8", 6),
                    TableItem_t("RGB8", 5),
                    TableItem_t("YCbCr422_8", 11),
                    TableItem_t("YUV422_8", 9)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class PixelSizeEnumParameter : public Pylon::CEnumParameterT<PixelSizeEnums>
        {
        public:
            PixelSizeEnumParameter()
            {
            }

            virtual ~PixelSizeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 5;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Bpp10", 6),
                    TableItem_t("Bpp12", 6),
                    TableItem_t("Bpp16", 6),
                    TableItem_t("Bpp24", 6),
                    TableItem_t("Bpp8", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class SoftwareSignalSelectorEnumParameter : public Pylon::CEnumParameterT<SoftwareSignalSelectorEnums>
        {
        public:
            SoftwareSignalSelectorEnumParameter()
            {
            }

            virtual ~SoftwareSignalSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("SoftwareSignal1", 16),
                    TableItem_t("SoftwareSignal2", 16),
                    TableItem_t("SoftwareSignal3", 16)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class TestPatternEnumParameter : public Pylon::CEnumParameterT<TestPatternEnums>
        {
        public:
            TestPatternEnumParameter()
            {
            }

            virtual ~TestPatternEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 7;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Black", 6),
                    TableItem_t("Off", 4),
                    TableItem_t("Testimage1", 11),
                    TableItem_t("Testimage2", 11),
                    TableItem_t("Testimage3", 11),
                    TableItem_t("Testimage6", 11),
                    TableItem_t("White", 6)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class TimerSelectorEnumParameter : public Pylon::CEnumParameterT<TimerSelectorEnums>
        {
        public:
            TimerSelectorEnumParameter()
            {
            }

            virtual ~TimerSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Timer1", 7),
                    TableItem_t("Timer2", 7)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class TimerStatusEnumParameter : public Pylon::CEnumParameterT<TimerStatusEnums>
        {
        public:
            TimerStatusEnumParameter()
            {
            }

            virtual ~TimerStatusEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 3;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("TimerActive", 12),
                    TableItem_t("TimerIdle", 10),
                    TableItem_t("TimerTriggerWait", 17)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class TimerTriggerActivationEnumParameter : public Pylon::CEnumParameterT<TimerTriggerActivationEnums>
        {
        public:
            TimerTriggerActivationEnumParameter()
            {
            }

            virtual ~TimerTriggerActivationEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 1;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Todo", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class TimerTriggerSourceEnumParameter : public Pylon::CEnumParameterT<TimerTriggerSourceEnums>
        {
        public:
            TimerTriggerSourceEnumParameter()
            {
            }

            virtual ~TimerTriggerSourceEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 25;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("AcquisitionActive", 18),
                    TableItem_t("Counter1Active", 15),
                    TableItem_t("Counter1End", 12),
                    TableItem_t("Counter1Start", 14),
                    TableItem_t("Counter2Active", 15),
                    TableItem_t("Counter2End", 12),
                    TableItem_t("Counter2Start", 14),
                    TableItem_t("ExposureActive", 15),
                    TableItem_t("ExposureStart", 14),
                    TableItem_t("ExposureTriggerWait", 20),
                    TableItem_t("FrameBurstActive", 17),
                    TableItem_t("FrameBurstTriggerWait", 22),
                    TableItem_t("FrameTriggerWait", 17),
                    TableItem_t("Line1", 6),
                    TableItem_t("Line2", 6),
                    TableItem_t("Line3", 6),
                    TableItem_t("Line4", 6),
                    TableItem_t("Off", 4),
                    TableItem_t("SoftwareSignal1", 16),
                    TableItem_t("SoftwareSignal2", 16),
                    TableItem_t("SoftwareSignal3", 16),
                    TableItem_t("Timer1Active", 13),
                    TableItem_t("Timer1End", 10),
                    TableItem_t("Timer2Active", 13),
                    TableItem_t("Timer2End", 10)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class TriggerActivationEnumParameter : public Pylon::CEnumParameterT<TriggerActivationEnums>
        {
        public:
            TriggerActivationEnumParameter()
            {
            }

            virtual ~TriggerActivationEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 1;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Todo", 5)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class TriggerModeEnumParameter : public Pylon::CEnumParameterT<TriggerModeEnums>
        {
        public:
            TriggerModeEnumParameter()
            {
            }

            virtual ~TriggerModeEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 2;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Off", 4),
                    TableItem_t("On", 3)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class TriggerSelectorEnumParameter : public Pylon::CEnumParameterT<TriggerSelectorEnums>
        {
        public:
            TriggerSelectorEnumParameter()
            {
            }

            virtual ~TriggerSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 9;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("ExposureActive", 15),
                    TableItem_t("ExposureEnd", 12),
                    TableItem_t("ExposureStart", 14),
                    TableItem_t("FrameActive", 12),
                    TableItem_t("FrameBurstActive", 17),
                    TableItem_t("FrameBurstEnd", 14),
                    TableItem_t("FrameBurstStart", 16),
                    TableItem_t("FrameEnd", 9),
                    TableItem_t("FrameStart", 11)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class TriggerSourceEnumParameter : public Pylon::CEnumParameterT<TriggerSourceEnums>
        {
        public:
            TriggerSourceEnumParameter()
            {
            }

            virtual ~TriggerSourceEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 18;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Counter1Active", 15),
                    TableItem_t("Counter1End", 12),
                    TableItem_t("Counter1Start", 14),
                    TableItem_t("Counter2Active", 15),
                    TableItem_t("Counter2End", 12),
                    TableItem_t("Counter2Start", 14),
                    TableItem_t("Line1", 6),
                    TableItem_t("Line2", 6),
                    TableItem_t("Line3", 6),
                    TableItem_t("Line4", 6),
                    TableItem_t("Software", 9),
                    TableItem_t("SoftwareSignal1", 16),
                    TableItem_t("SoftwareSignal2", 16),
                    TableItem_t("SoftwareSignal3", 16),
                    TableItem_t("Timer1Active", 13),
                    TableItem_t("Timer1End", 10),
                    TableItem_t("Timer2Active", 13),
                    TableItem_t("Timer2End", 10)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class UserDefinedValueSelectorEnumParameter : public Pylon::CEnumParameterT<UserDefinedValueSelectorEnums>
        {
        public:
            UserDefinedValueSelectorEnumParameter()
            {
            }

            virtual ~UserDefinedValueSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 5;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Value1", 7),
                    TableItem_t("Value2", 7),
                    TableItem_t("Value3", 7),
                    TableItem_t("Value4", 7),
                    TableItem_t("Value5", 7)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class UserOutputSelectorEnumParameter : public Pylon::CEnumParameterT<UserOutputSelectorEnums>
        {
        public:
            UserOutputSelectorEnumParameter()
            {
            }

            virtual ~UserOutputSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 4;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("UserOutput1", 12),
                    TableItem_t("UserOutput2", 12),
                    TableItem_t("UserOutput3", 12),
                    TableItem_t("UserOutput4", 12)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class UserSetDefaultEnumParameter : public Pylon::CEnumParameterT<UserSetDefaultEnums>
        {
        public:
            UserSetDefaultEnumParameter()
            {
            }

            virtual ~UserSetDefaultEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 4;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Default", 8),
                    TableItem_t("UserSet1", 9),
                    TableItem_t("UserSet2", 9),
                    TableItem_t("UserSet3", 9)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


        ///////////////////////////////////////////////////////////////////////////
        //
        class UserSetSelectorEnumParameter : public Pylon::CEnumParameterT<UserSetSelectorEnums>
        {
        public:
            UserSetSelectorEnumParameter()
            {
            }

            virtual ~UserSetSelectorEnumParameter()
            {
            }
        protected:
            virtual const Table_t& GetTable() const
            {
                static const size_t cItemCount = 4;
                static const TableItem_t cItems[cItemCount] =
                {
                    TableItem_t("Default", 8),
                    TableItem_t("UserSet1", 9),
                    TableItem_t("UserSet2", 9),
                    TableItem_t("UserSet3", 9)
                };
                static const Table_t table(cItems, cItemCount);
                return table;
            }
        };


    }

    //! \endcond
    //**************************************************************************************************
    // Parameter class BaslerCameraCameraParams implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS
    
    ///////////////////////////////////////////////////////////////////////////
    //
    class BaslerCameraCameraParams::BaslerCameraCameraParams_Data
    {
    public:
        Pylon::CCommandParameter AcquisitionAbort;
        Pylon::CIntegerParameter AcquisitionBurstFrameCount;
        Pylon::CFloatParameter AcquisitionFrameRate;
        Pylon::CBooleanParameter AcquisitionFrameRateEnable;
        EnumParameterClasses::AcquisitionModeEnumParameter AcquisitionMode;
        Pylon::CCommandParameter AcquisitionStart;
        Pylon::CBooleanParameter AcquisitionStatus;
        EnumParameterClasses::AcquisitionStatusSelectorEnumParameter AcquisitionStatusSelector;
        Pylon::CCommandParameter AcquisitionStop;
        Pylon::CFloatParameter AutoExposureTimeLowerLimit;
        Pylon::CFloatParameter AutoExposureTimeUpperLimit;
        EnumParameterClasses::AutoFunctionProfileEnumParameter AutoFunctionProfile;
        Pylon::CIntegerParameter AutoFunctionROIHeight;
        Pylon::CBooleanParameter AutoFunctionROIHighlight;
        Pylon::CIntegerParameter AutoFunctionROIOffsetX;
        Pylon::CIntegerParameter AutoFunctionROIOffsetY;
        EnumParameterClasses::AutoFunctionROISelectorEnumParameter AutoFunctionROISelector;
        Pylon::CBooleanParameter AutoFunctionROIUseBrightness;
        Pylon::CBooleanParameter AutoFunctionROIUseWhiteBalance;
        Pylon::CIntegerParameter AutoFunctionROIWidth;
        Pylon::CFloatParameter AutoGainLowerLimit;
        Pylon::CFloatParameter AutoGainUpperLimit;
        Pylon::CFloatParameter AutoTargetBrightness;
        Pylon::CFloatParameter BalanceRatio;
        EnumParameterClasses::BalanceRatioSelectorEnumParameter BalanceRatioSelector;
        EnumParameterClasses::BalanceWhiteAutoEnumParameter BalanceWhiteAuto;
        Pylon::CFloatParameter BlackLevel;
        EnumParameterClasses::BslAcquisitionBurstModeEnumParameter BslAcquisitionBurstMode;
        EnumParameterClasses::BslAcquisitionStopModeEnumParameter BslAcquisitionStopMode;
        Pylon::CFloatParameter BslBrightness;
        Pylon::CCommandParameter BslCenterX;
        Pylon::CCommandParameter BslCenterY;
        EnumParameterClasses::BslChunkAutoBrightnessStatusEnumParameter BslChunkAutoBrightnessStatus;
        EnumParameterClasses::BslChunkTimestampSelectorEnumParameter BslChunkTimestampSelector;
        Pylon::CIntegerParameter BslChunkTimestampValue;
        EnumParameterClasses::BslColorSpaceEnumParameter BslColorSpace;
        Pylon::CFloatParameter BslContrast;
        EnumParameterClasses::BslContrastModeEnumParameter BslContrastMode;
        EnumParameterClasses::BslDefectPixelCorrectionModeEnumParameter BslDefectPixelCorrectionMode;
        Pylon::CIntegerParameter BslDeviceLinkCurrentThroughput;
        Pylon::CFloatParameter BslEffectiveExposureTime;
        Pylon::CBooleanParameter BslErrorPresent;
        Pylon::CCommandParameter BslErrorReportNext;
        Pylon::CIntegerParameter BslErrorReportValue;
        Pylon::CFloatParameter BslExposureStartDelay;
        Pylon::CFloatParameter BslHue;
        Pylon::CFloatParameter BslInputFilterTime;
        Pylon::CFloatParameter BslInputHoldOffTime;
        EnumParameterClasses::BslLightSourcePresetEnumParameter BslLightSourcePreset;
        Pylon::CBooleanParameter BslLightSourcePresetFeatureEnable;
        EnumParameterClasses::BslLightSourcePresetFeatureSelectorEnumParameter BslLightSourcePresetFeatureSelector;
        EnumParameterClasses::BslLineConnectionEnumParameter BslLineConnection;
        Pylon::CFloatParameter BslNoiseReduction;
        Pylon::CFloatParameter BslResultingAcquisitionFrameRate;
        Pylon::CFloatParameter BslResultingFrameBurstRate;
        Pylon::CFloatParameter BslResultingTransferFrameRate;
        Pylon::CFloatParameter BslSaturation;
        Pylon::CFloatParameter BslScalingFactor;
        EnumParameterClasses::BslSensorBitDepthEnumParameter BslSensorBitDepth;
        EnumParameterClasses::BslSensorBitDepthModeEnumParameter BslSensorBitDepthMode;
        Pylon::CCommandParameter BslSensorOff;
        Pylon::CCommandParameter BslSensorOn;
        Pylon::CCommandParameter BslSensorStandby;
        EnumParameterClasses::BslSensorStateEnumParameter BslSensorState;
        Pylon::CFloatParameter BslSharpnessEnhancement;
        Pylon::CFloatParameter BslTemperatureMax;
        EnumParameterClasses::BslTemperatureStatusEnumParameter BslTemperatureStatus;
        Pylon::CIntegerParameter BslTemperatureStatusErrorCount;
        EnumParameterClasses::BslTwiBitrateEnumParameter BslTwiBitrate;
        Pylon::CBooleanParameter BslTwiPullSclLow;
        Pylon::CBooleanParameter BslTwiPullSdaLow;
        Pylon::CCommandParameter BslTwiRead;
        Pylon::CIntegerParameter BslTwiTargetAddress;
        Pylon::CArrayParameter BslTwiTransferBuffer;
        Pylon::CIntegerParameter BslTwiTransferLength;
        EnumParameterClasses::BslTwiTransferStatusEnumParameter BslTwiTransferStatus;
        Pylon::CCommandParameter BslTwiUpdateTransferStatus;
        Pylon::CCommandParameter BslTwiWrite;
        EnumParameterClasses::BslUSBPowerSourceEnumParameter BslUSBPowerSource;
        EnumParameterClasses::BslUSBSpeedModeEnumParameter BslUSBSpeedMode;
        EnumParameterClasses::ChunkCounterSelectorEnumParameter ChunkCounterSelector;
        Pylon::CIntegerParameter ChunkCounterValue;
        Pylon::CBooleanParameter ChunkEnable;
        Pylon::CFloatParameter ChunkExposureTime;
        Pylon::CIntegerParameter ChunkFrameID;
        Pylon::CFloatParameter ChunkGain;
        Pylon::CIntegerParameter ChunkLineStatusAll;
        Pylon::CBooleanParameter ChunkModeActive;
        Pylon::CIntegerParameter ChunkPayloadCRC16;
        EnumParameterClasses::ChunkSelectorEnumParameter ChunkSelector;
        Pylon::CIntegerParameter CounterDuration;
        EnumParameterClasses::CounterEventActivationEnumParameter CounterEventActivation;
        EnumParameterClasses::CounterEventSourceEnumParameter CounterEventSource;
        Pylon::CCommandParameter CounterReset;
        EnumParameterClasses::CounterResetActivationEnumParameter CounterResetActivation;
        EnumParameterClasses::CounterResetSourceEnumParameter CounterResetSource;
        EnumParameterClasses::CounterSelectorEnumParameter CounterSelector;
        EnumParameterClasses::CounterStatusEnumParameter CounterStatus;
        EnumParameterClasses::CounterTriggerActivationEnumParameter CounterTriggerActivation;
        EnumParameterClasses::CounterTriggerSourceEnumParameter CounterTriggerSource;
        Pylon::CIntegerParameter CounterValue;
        EnumParameterClasses::DeviceCharacterSetEnumParameter DeviceCharacterSet;
        Pylon::CStringParameter DeviceFamilyName;
        Pylon::CCommandParameter DeviceFeaturePersistenceEnd;
        Pylon::CCommandParameter DeviceFeaturePersistenceStart;
        Pylon::CStringParameter DeviceFirmwareVersion;
        Pylon::CIntegerParameter DeviceGenCPVersionMajor;
        Pylon::CIntegerParameter DeviceGenCPVersionMinor;
        EnumParameterClasses::DeviceIndicatorModeEnumParameter DeviceIndicatorMode;
        Pylon::CIntegerParameter DeviceLinkSpeed;
        Pylon::CIntegerParameter DeviceLinkThroughputLimit;
        EnumParameterClasses::DeviceLinkThroughputLimitModeEnumParameter DeviceLinkThroughputLimitMode;
        Pylon::CIntegerParameter DeviceManifestSchemaMajorVersion;
        Pylon::CIntegerParameter DeviceManifestSchemaMinorVersion;
        Pylon::CIntegerParameter DeviceManifestXMLMajorVersion;
        Pylon::CIntegerParameter DeviceManifestXMLMinorVersion;
        Pylon::CIntegerParameter DeviceManifestXMLSubMinorVersion;
        Pylon::CStringParameter DeviceManufacturerInfo;
        Pylon::CStringParameter DeviceModelName;
        EnumParameterClasses::DeviceRegistersEndiannessEnumParameter DeviceRegistersEndianness;
        Pylon::CCommandParameter DeviceRegistersStreamingEnd;
        Pylon::CCommandParameter DeviceRegistersStreamingStart;
        Pylon::CCommandParameter DeviceReset;
        Pylon::CIntegerParameter DeviceSFNCVersionMajor;
        Pylon::CIntegerParameter DeviceSFNCVersionMinor;
        Pylon::CIntegerParameter DeviceSFNCVersionSubMinor;
        EnumParameterClasses::DeviceScanTypeEnumParameter DeviceScanType;
        Pylon::CStringParameter DeviceSerialNumber;
        EnumParameterClasses::DeviceTLTypeEnumParameter DeviceTLType;
        Pylon::CIntegerParameter DeviceTLVersionMajor;
        Pylon::CIntegerParameter DeviceTLVersionMinor;
        Pylon::CIntegerParameter DeviceTLVersionSubMinor;
        Pylon::CFloatParameter DeviceTemperature;
        EnumParameterClasses::DeviceTemperatureSelectorEnumParameter DeviceTemperatureSelector;
        Pylon::CStringParameter DeviceUserID;
        Pylon::CStringParameter DeviceVendorName;
        Pylon::CStringParameter DeviceVersion;
        Pylon::CIntegerParameter DigitalShift;
        Pylon::CIntegerParameter EventExposureEnd;
        Pylon::CIntegerParameter EventExposureEndFrameID;
        Pylon::CIntegerParameter EventExposureEndTimestamp;
        Pylon::CIntegerParameter EventFrameStart;
        Pylon::CIntegerParameter EventFrameStartFrameID;
        Pylon::CIntegerParameter EventFrameStartTimestamp;
        Pylon::CIntegerParameter EventFrameTriggerMissed;
        Pylon::CIntegerParameter EventFrameTriggerMissedTimestamp;
        EnumParameterClasses::EventNotificationEnumParameter EventNotification;
        Pylon::CIntegerParameter EventOverrun;
        Pylon::CIntegerParameter EventOverrunTimestamp;
        EnumParameterClasses::EventSelectorEnumParameter EventSelector;
        Pylon::CIntegerParameter EventTemperatureStatusChanged;
        EnumParameterClasses::EventTemperatureStatusChangedStatusEnumParameter EventTemperatureStatusChangedStatus;
        Pylon::CIntegerParameter EventTemperatureStatusChangedTimestamp;
        Pylon::CIntegerParameter EventTest;
        Pylon::CIntegerParameter EventTestTimestamp;
        EnumParameterClasses::ExposureAutoEnumParameter ExposureAuto;
        EnumParameterClasses::ExposureModeEnumParameter ExposureMode;
        Pylon::CFloatParameter ExposureTime;
        Pylon::CArrayParameter FileAccessBuffer;
        Pylon::CIntegerParameter FileAccessLength;
        Pylon::CIntegerParameter FileAccessOffset;
        EnumParameterClasses::FileOpenModeEnumParameter FileOpenMode;
        Pylon::CCommandParameter FileOperationExecute;
        Pylon::CIntegerParameter FileOperationResult;
        EnumParameterClasses::FileOperationSelectorEnumParameter FileOperationSelector;
        EnumParameterClasses::FileOperationStatusEnumParameter FileOperationStatus;
        EnumParameterClasses::FileSelectorEnumParameter FileSelector;
        Pylon::CFloatParameter Gain;
        EnumParameterClasses::GainAutoEnumParameter GainAuto;
        Pylon::CFloatParameter Gamma;
        Pylon::CIntegerParameter Height;
        Pylon::CIntegerParameter HeightMax;
        EnumParameterClasses::LineFormatEnumParameter LineFormat;
        Pylon::CBooleanParameter LineInverter;
        EnumParameterClasses::LineModeEnumParameter LineMode;
        EnumParameterClasses::LineSelectorEnumParameter LineSelector;
        EnumParameterClasses::LineSourceEnumParameter LineSource;
        Pylon::CBooleanParameter LineStatus;
        Pylon::CIntegerParameter LineStatusAll;
        Pylon::CIntegerParameter OffsetX;
        Pylon::CIntegerParameter OffsetY;
        Pylon::CIntegerParameter PayloadSize;
        Pylon::CIntegerParameter PixelDynamicRangeMax;
        Pylon::CIntegerParameter PixelDynamicRangeMin;
        EnumParameterClasses::PixelFormatEnumParameter PixelFormat;
        EnumParameterClasses::PixelSizeEnumParameter PixelSize;
        Pylon::CBooleanParameter ReverseX;
        Pylon::CBooleanParameter ReverseY;
        Pylon::CIntegerParameter SIPayloadFinalTransfer1Size;
        Pylon::CIntegerParameter SIPayloadFinalTransfer2Size;
        Pylon::CIntegerParameter SIPayloadTransferCount;
        Pylon::CIntegerParameter SIPayloadTransferSize;
        Pylon::CIntegerParameter SensorHeight;
        Pylon::CFloatParameter SensorReadoutTime;
        Pylon::CIntegerParameter SensorWidth;
        Pylon::CCommandParameter SoftwareSignalPulse;
        EnumParameterClasses::SoftwareSignalSelectorEnumParameter SoftwareSignalSelector;
        Pylon::CCommandParameter TestEventGenerate;
        EnumParameterClasses::TestPatternEnumParameter TestPattern;
        Pylon::CIntegerParameter TestPendingAck;
        Pylon::CFloatParameter TimerDelay;
        Pylon::CFloatParameter TimerDuration;
        Pylon::CCommandParameter TimerReset;
        EnumParameterClasses::TimerSelectorEnumParameter TimerSelector;
        EnumParameterClasses::TimerStatusEnumParameter TimerStatus;
        EnumParameterClasses::TimerTriggerActivationEnumParameter TimerTriggerActivation;
        Pylon::CFloatParameter TimerTriggerArmDelay;
        EnumParameterClasses::TimerTriggerSourceEnumParameter TimerTriggerSource;
        Pylon::CCommandParameter TimestampLatch;
        Pylon::CIntegerParameter TimestampLatchValue;
        EnumParameterClasses::TriggerActivationEnumParameter TriggerActivation;
        Pylon::CFloatParameter TriggerDelay;
        EnumParameterClasses::TriggerModeEnumParameter TriggerMode;
        EnumParameterClasses::TriggerSelectorEnumParameter TriggerSelector;
        Pylon::CCommandParameter TriggerSoftware;
        EnumParameterClasses::TriggerSourceEnumParameter TriggerSource;
        Pylon::CIntegerParameter UserDefinedValue;
        EnumParameterClasses::UserDefinedValueSelectorEnumParameter UserDefinedValueSelector;
        EnumParameterClasses::UserOutputSelectorEnumParameter UserOutputSelector;
        Pylon::CBooleanParameter UserOutputValue;
        Pylon::CIntegerParameter UserOutputValueAll;
        EnumParameterClasses::UserSetDefaultEnumParameter UserSetDefault;
        Pylon::CCommandParameter UserSetLoad;
        Pylon::CCommandParameter UserSetSave;
        EnumParameterClasses::UserSetSelectorEnumParameter UserSetSelector;
        Pylon::CIntegerParameter Width;
        Pylon::CIntegerParameter WidthMax;
    };


    ///////////////////////////////////////////////////////////////////////////
    //
    BaslerCameraCameraParams::BaslerCameraCameraParams(void)
        : m_pData(new BaslerCameraCameraParams_Data())
        , AcquisitionAbort(m_pData->AcquisitionAbort)
        , AcquisitionBurstFrameCount(m_pData->AcquisitionBurstFrameCount)
        , AcquisitionFrameRate(m_pData->AcquisitionFrameRate)
        , AcquisitionFrameRateEnable(m_pData->AcquisitionFrameRateEnable)
        , AcquisitionMode(m_pData->AcquisitionMode)
        , AcquisitionStart(m_pData->AcquisitionStart)
        , AcquisitionStatus(m_pData->AcquisitionStatus)
        , AcquisitionStatusSelector(m_pData->AcquisitionStatusSelector)
        , AcquisitionStop(m_pData->AcquisitionStop)
        , AutoExposureTimeLowerLimit(m_pData->AutoExposureTimeLowerLimit)
        , AutoExposureTimeUpperLimit(m_pData->AutoExposureTimeUpperLimit)
        , AutoFunctionProfile(m_pData->AutoFunctionProfile)
        , AutoFunctionROIHeight(m_pData->AutoFunctionROIHeight)
        , AutoFunctionROIHighlight(m_pData->AutoFunctionROIHighlight)
        , AutoFunctionROIOffsetX(m_pData->AutoFunctionROIOffsetX)
        , AutoFunctionROIOffsetY(m_pData->AutoFunctionROIOffsetY)
        , AutoFunctionROISelector(m_pData->AutoFunctionROISelector)
        , AutoFunctionROIUseBrightness(m_pData->AutoFunctionROIUseBrightness)
        , AutoFunctionROIUseWhiteBalance(m_pData->AutoFunctionROIUseWhiteBalance)
        , AutoFunctionROIWidth(m_pData->AutoFunctionROIWidth)
        , AutoGainLowerLimit(m_pData->AutoGainLowerLimit)
        , AutoGainUpperLimit(m_pData->AutoGainUpperLimit)
        , AutoTargetBrightness(m_pData->AutoTargetBrightness)
        , BalanceRatio(m_pData->BalanceRatio)
        , BalanceRatioSelector(m_pData->BalanceRatioSelector)
        , BalanceWhiteAuto(m_pData->BalanceWhiteAuto)
        , BlackLevel(m_pData->BlackLevel)
        , BslAcquisitionBurstMode(m_pData->BslAcquisitionBurstMode)
        , BslAcquisitionStopMode(m_pData->BslAcquisitionStopMode)
        , BslBrightness(m_pData->BslBrightness)
        , BslCenterX(m_pData->BslCenterX)
        , BslCenterY(m_pData->BslCenterY)
        , BslChunkAutoBrightnessStatus(m_pData->BslChunkAutoBrightnessStatus)
        , BslChunkTimestampSelector(m_pData->BslChunkTimestampSelector)
        , BslChunkTimestampValue(m_pData->BslChunkTimestampValue)
        , BslColorSpace(m_pData->BslColorSpace)
        , BslContrast(m_pData->BslContrast)
        , BslContrastMode(m_pData->BslContrastMode)
        , BslDefectPixelCorrectionMode(m_pData->BslDefectPixelCorrectionMode)
        , BslDeviceLinkCurrentThroughput(m_pData->BslDeviceLinkCurrentThroughput)
        , BslEffectiveExposureTime(m_pData->BslEffectiveExposureTime)
        , BslErrorPresent(m_pData->BslErrorPresent)
        , BslErrorReportNext(m_pData->BslErrorReportNext)
        , BslErrorReportValue(m_pData->BslErrorReportValue)
        , BslExposureStartDelay(m_pData->BslExposureStartDelay)
        , BslHue(m_pData->BslHue)
        , BslInputFilterTime(m_pData->BslInputFilterTime)
        , BslInputHoldOffTime(m_pData->BslInputHoldOffTime)
        , BslLightSourcePreset(m_pData->BslLightSourcePreset)
        , BslLightSourcePresetFeatureEnable(m_pData->BslLightSourcePresetFeatureEnable)
        , BslLightSourcePresetFeatureSelector(m_pData->BslLightSourcePresetFeatureSelector)
        , BslLineConnection(m_pData->BslLineConnection)
        , BslNoiseReduction(m_pData->BslNoiseReduction)
        , BslResultingAcquisitionFrameRate(m_pData->BslResultingAcquisitionFrameRate)
        , BslResultingFrameBurstRate(m_pData->BslResultingFrameBurstRate)
        , BslResultingTransferFrameRate(m_pData->BslResultingTransferFrameRate)
        , BslSaturation(m_pData->BslSaturation)
        , BslScalingFactor(m_pData->BslScalingFactor)
        , BslSensorBitDepth(m_pData->BslSensorBitDepth)
        , BslSensorBitDepthMode(m_pData->BslSensorBitDepthMode)
        , BslSensorOff(m_pData->BslSensorOff)
        , BslSensorOn(m_pData->BslSensorOn)
        , BslSensorStandby(m_pData->BslSensorStandby)
        , BslSensorState(m_pData->BslSensorState)
        , BslSharpnessEnhancement(m_pData->BslSharpnessEnhancement)
        , BslTemperatureMax(m_pData->BslTemperatureMax)
        , BslTemperatureStatus(m_pData->BslTemperatureStatus)
        , BslTemperatureStatusErrorCount(m_pData->BslTemperatureStatusErrorCount)
        , BslTwiBitrate(m_pData->BslTwiBitrate)
        , BslTwiPullSclLow(m_pData->BslTwiPullSclLow)
        , BslTwiPullSdaLow(m_pData->BslTwiPullSdaLow)
        , BslTwiRead(m_pData->BslTwiRead)
        , BslTwiTargetAddress(m_pData->BslTwiTargetAddress)
        , BslTwiTransferBuffer(m_pData->BslTwiTransferBuffer)
        , BslTwiTransferLength(m_pData->BslTwiTransferLength)
        , BslTwiTransferStatus(m_pData->BslTwiTransferStatus)
        , BslTwiUpdateTransferStatus(m_pData->BslTwiUpdateTransferStatus)
        , BslTwiWrite(m_pData->BslTwiWrite)
        , BslUSBPowerSource(m_pData->BslUSBPowerSource)
        , BslUSBSpeedMode(m_pData->BslUSBSpeedMode)
        , ChunkCounterSelector(m_pData->ChunkCounterSelector)
        , ChunkCounterValue(m_pData->ChunkCounterValue)
        , ChunkEnable(m_pData->ChunkEnable)
        , ChunkExposureTime(m_pData->ChunkExposureTime)
        , ChunkFrameID(m_pData->ChunkFrameID)
        , ChunkGain(m_pData->ChunkGain)
        , ChunkLineStatusAll(m_pData->ChunkLineStatusAll)
        , ChunkModeActive(m_pData->ChunkModeActive)
        , ChunkPayloadCRC16(m_pData->ChunkPayloadCRC16)
        , ChunkSelector(m_pData->ChunkSelector)
        , CounterDuration(m_pData->CounterDuration)
        , CounterEventActivation(m_pData->CounterEventActivation)
        , CounterEventSource(m_pData->CounterEventSource)
        , CounterReset(m_pData->CounterReset)
        , CounterResetActivation(m_pData->CounterResetActivation)
        , CounterResetSource(m_pData->CounterResetSource)
        , CounterSelector(m_pData->CounterSelector)
        , CounterStatus(m_pData->CounterStatus)
        , CounterTriggerActivation(m_pData->CounterTriggerActivation)
        , CounterTriggerSource(m_pData->CounterTriggerSource)
        , CounterValue(m_pData->CounterValue)
        , DeviceCharacterSet(m_pData->DeviceCharacterSet)
        , DeviceFamilyName(m_pData->DeviceFamilyName)
        , DeviceFeaturePersistenceEnd(m_pData->DeviceFeaturePersistenceEnd)
        , DeviceFeaturePersistenceStart(m_pData->DeviceFeaturePersistenceStart)
        , DeviceFirmwareVersion(m_pData->DeviceFirmwareVersion)
        , DeviceGenCPVersionMajor(m_pData->DeviceGenCPVersionMajor)
        , DeviceGenCPVersionMinor(m_pData->DeviceGenCPVersionMinor)
        , DeviceIndicatorMode(m_pData->DeviceIndicatorMode)
        , DeviceLinkSpeed(m_pData->DeviceLinkSpeed)
        , DeviceLinkThroughputLimit(m_pData->DeviceLinkThroughputLimit)
        , DeviceLinkThroughputLimitMode(m_pData->DeviceLinkThroughputLimitMode)
        , DeviceManifestSchemaMajorVersion(m_pData->DeviceManifestSchemaMajorVersion)
        , DeviceManifestSchemaMinorVersion(m_pData->DeviceManifestSchemaMinorVersion)
        , DeviceManifestXMLMajorVersion(m_pData->DeviceManifestXMLMajorVersion)
        , DeviceManifestXMLMinorVersion(m_pData->DeviceManifestXMLMinorVersion)
        , DeviceManifestXMLSubMinorVersion(m_pData->DeviceManifestXMLSubMinorVersion)
        , DeviceManufacturerInfo(m_pData->DeviceManufacturerInfo)
        , DeviceModelName(m_pData->DeviceModelName)
        , DeviceRegistersEndianness(m_pData->DeviceRegistersEndianness)
        , DeviceRegistersStreamingEnd(m_pData->DeviceRegistersStreamingEnd)
        , DeviceRegistersStreamingStart(m_pData->DeviceRegistersStreamingStart)
        , DeviceReset(m_pData->DeviceReset)
        , DeviceSFNCVersionMajor(m_pData->DeviceSFNCVersionMajor)
        , DeviceSFNCVersionMinor(m_pData->DeviceSFNCVersionMinor)
        , DeviceSFNCVersionSubMinor(m_pData->DeviceSFNCVersionSubMinor)
        , DeviceScanType(m_pData->DeviceScanType)
        , DeviceSerialNumber(m_pData->DeviceSerialNumber)
        , DeviceTLType(m_pData->DeviceTLType)
        , DeviceTLVersionMajor(m_pData->DeviceTLVersionMajor)
        , DeviceTLVersionMinor(m_pData->DeviceTLVersionMinor)
        , DeviceTLVersionSubMinor(m_pData->DeviceTLVersionSubMinor)
        , DeviceTemperature(m_pData->DeviceTemperature)
        , DeviceTemperatureSelector(m_pData->DeviceTemperatureSelector)
        , DeviceUserID(m_pData->DeviceUserID)
        , DeviceVendorName(m_pData->DeviceVendorName)
        , DeviceVersion(m_pData->DeviceVersion)
        , DigitalShift(m_pData->DigitalShift)
        , EventExposureEnd(m_pData->EventExposureEnd)
        , EventExposureEndFrameID(m_pData->EventExposureEndFrameID)
        , EventExposureEndTimestamp(m_pData->EventExposureEndTimestamp)
        , EventFrameStart(m_pData->EventFrameStart)
        , EventFrameStartFrameID(m_pData->EventFrameStartFrameID)
        , EventFrameStartTimestamp(m_pData->EventFrameStartTimestamp)
        , EventFrameTriggerMissed(m_pData->EventFrameTriggerMissed)
        , EventFrameTriggerMissedTimestamp(m_pData->EventFrameTriggerMissedTimestamp)
        , EventNotification(m_pData->EventNotification)
        , EventOverrun(m_pData->EventOverrun)
        , EventOverrunTimestamp(m_pData->EventOverrunTimestamp)
        , EventSelector(m_pData->EventSelector)
        , EventTemperatureStatusChanged(m_pData->EventTemperatureStatusChanged)
        , EventTemperatureStatusChangedStatus(m_pData->EventTemperatureStatusChangedStatus)
        , EventTemperatureStatusChangedTimestamp(m_pData->EventTemperatureStatusChangedTimestamp)
        , EventTest(m_pData->EventTest)
        , EventTestTimestamp(m_pData->EventTestTimestamp)
        , ExposureAuto(m_pData->ExposureAuto)
        , ExposureMode(m_pData->ExposureMode)
        , ExposureTime(m_pData->ExposureTime)
        , FileAccessBuffer(m_pData->FileAccessBuffer)
        , FileAccessLength(m_pData->FileAccessLength)
        , FileAccessOffset(m_pData->FileAccessOffset)
        , FileOpenMode(m_pData->FileOpenMode)
        , FileOperationExecute(m_pData->FileOperationExecute)
        , FileOperationResult(m_pData->FileOperationResult)
        , FileOperationSelector(m_pData->FileOperationSelector)
        , FileOperationStatus(m_pData->FileOperationStatus)
        , FileSelector(m_pData->FileSelector)
        , Gain(m_pData->Gain)
        , GainAuto(m_pData->GainAuto)
        , Gamma(m_pData->Gamma)
        , Height(m_pData->Height)
        , HeightMax(m_pData->HeightMax)
        , LineFormat(m_pData->LineFormat)
        , LineInverter(m_pData->LineInverter)
        , LineMode(m_pData->LineMode)
        , LineSelector(m_pData->LineSelector)
        , LineSource(m_pData->LineSource)
        , LineStatus(m_pData->LineStatus)
        , LineStatusAll(m_pData->LineStatusAll)
        , OffsetX(m_pData->OffsetX)
        , OffsetY(m_pData->OffsetY)
        , PayloadSize(m_pData->PayloadSize)
        , PixelDynamicRangeMax(m_pData->PixelDynamicRangeMax)
        , PixelDynamicRangeMin(m_pData->PixelDynamicRangeMin)
        , PixelFormat(m_pData->PixelFormat)
        , PixelSize(m_pData->PixelSize)
        , ReverseX(m_pData->ReverseX)
        , ReverseY(m_pData->ReverseY)
        , SIPayloadFinalTransfer1Size(m_pData->SIPayloadFinalTransfer1Size)
        , SIPayloadFinalTransfer2Size(m_pData->SIPayloadFinalTransfer2Size)
        , SIPayloadTransferCount(m_pData->SIPayloadTransferCount)
        , SIPayloadTransferSize(m_pData->SIPayloadTransferSize)
        , SensorHeight(m_pData->SensorHeight)
        , SensorReadoutTime(m_pData->SensorReadoutTime)
        , SensorWidth(m_pData->SensorWidth)
        , SoftwareSignalPulse(m_pData->SoftwareSignalPulse)
        , SoftwareSignalSelector(m_pData->SoftwareSignalSelector)
        , TestEventGenerate(m_pData->TestEventGenerate)
        , TestPattern(m_pData->TestPattern)
        , TestPendingAck(m_pData->TestPendingAck)
        , TimerDelay(m_pData->TimerDelay)
        , TimerDuration(m_pData->TimerDuration)
        , TimerReset(m_pData->TimerReset)
        , TimerSelector(m_pData->TimerSelector)
        , TimerStatus(m_pData->TimerStatus)
        , TimerTriggerActivation(m_pData->TimerTriggerActivation)
        , TimerTriggerArmDelay(m_pData->TimerTriggerArmDelay)
        , TimerTriggerSource(m_pData->TimerTriggerSource)
        , TimestampLatch(m_pData->TimestampLatch)
        , TimestampLatchValue(m_pData->TimestampLatchValue)
        , TriggerActivation(m_pData->TriggerActivation)
        , TriggerDelay(m_pData->TriggerDelay)
        , TriggerMode(m_pData->TriggerMode)
        , TriggerSelector(m_pData->TriggerSelector)
        , TriggerSoftware(m_pData->TriggerSoftware)
        , TriggerSource(m_pData->TriggerSource)
        , UserDefinedValue(m_pData->UserDefinedValue)
        , UserDefinedValueSelector(m_pData->UserDefinedValueSelector)
        , UserOutputSelector(m_pData->UserOutputSelector)
        , UserOutputValue(m_pData->UserOutputValue)
        , UserOutputValueAll(m_pData->UserOutputValueAll)
        , UserSetDefault(m_pData->UserSetDefault)
        , UserSetLoad(m_pData->UserSetLoad)
        , UserSetSave(m_pData->UserSetSave)
        , UserSetSelector(m_pData->UserSetSelector)
        , Width(m_pData->Width)
        , WidthMax(m_pData->WidthMax)
    {
    }


    ///////////////////////////////////////////////////////////////////////////
    //
    BaslerCameraCameraParams::~BaslerCameraCameraParams(void)
    {
        delete m_pData;
    }


    ///////////////////////////////////////////////////////////////////////////
    //
    void BaslerCameraCameraParams::_Initialize(GENAPI_NAMESPACE::INodeMap* pNodeMap)
    {
        m_pData->AcquisitionAbort.Attach(pNodeMap, "AcquisitionAbort");
        m_pData->AcquisitionBurstFrameCount.Attach(pNodeMap, "AcquisitionBurstFrameCount");
        m_pData->AcquisitionFrameRate.Attach(pNodeMap, "AcquisitionFrameRate");
        m_pData->AcquisitionFrameRateEnable.Attach(pNodeMap, "AcquisitionFrameRateEnable");
        m_pData->AcquisitionMode.Attach(pNodeMap, "AcquisitionMode");
        m_pData->AcquisitionStart.Attach(pNodeMap, "AcquisitionStart");
        m_pData->AcquisitionStatus.Attach(pNodeMap, "AcquisitionStatus");
        m_pData->AcquisitionStatusSelector.Attach(pNodeMap, "AcquisitionStatusSelector");
        m_pData->AcquisitionStop.Attach(pNodeMap, "AcquisitionStop");
        m_pData->AutoExposureTimeLowerLimit.Attach(pNodeMap, "AutoExposureTimeLowerLimit");
        m_pData->AutoExposureTimeUpperLimit.Attach(pNodeMap, "AutoExposureTimeUpperLimit");
        m_pData->AutoFunctionProfile.Attach(pNodeMap, "AutoFunctionProfile");
        m_pData->AutoFunctionROIHeight.Attach(pNodeMap, "AutoFunctionROIHeight");
        m_pData->AutoFunctionROIHighlight.Attach(pNodeMap, "AutoFunctionROIHighlight");
        m_pData->AutoFunctionROIOffsetX.Attach(pNodeMap, "AutoFunctionROIOffsetX");
        m_pData->AutoFunctionROIOffsetY.Attach(pNodeMap, "AutoFunctionROIOffsetY");
        m_pData->AutoFunctionROISelector.Attach(pNodeMap, "AutoFunctionROISelector");
        m_pData->AutoFunctionROIUseBrightness.Attach(pNodeMap, "AutoFunctionROIUseBrightness");
        m_pData->AutoFunctionROIUseWhiteBalance.Attach(pNodeMap, "AutoFunctionROIUseWhiteBalance");
        m_pData->AutoFunctionROIWidth.Attach(pNodeMap, "AutoFunctionROIWidth");
        m_pData->AutoGainLowerLimit.Attach(pNodeMap, "AutoGainLowerLimit");
        m_pData->AutoGainUpperLimit.Attach(pNodeMap, "AutoGainUpperLimit");
        m_pData->AutoTargetBrightness.Attach(pNodeMap, "AutoTargetBrightness");
        m_pData->BalanceRatio.Attach(pNodeMap, "BalanceRatio");
        m_pData->BalanceRatioSelector.Attach(pNodeMap, "BalanceRatioSelector");
        m_pData->BalanceWhiteAuto.Attach(pNodeMap, "BalanceWhiteAuto");
        m_pData->BlackLevel.Attach(pNodeMap, "BlackLevel");
        m_pData->BslAcquisitionBurstMode.Attach(pNodeMap, "BslAcquisitionBurstMode");
        m_pData->BslAcquisitionStopMode.Attach(pNodeMap, "BslAcquisitionStopMode");
        m_pData->BslBrightness.Attach(pNodeMap, "BslBrightness");
        m_pData->BslCenterX.Attach(pNodeMap, "BslCenterX");
        m_pData->BslCenterY.Attach(pNodeMap, "BslCenterY");
        m_pData->BslChunkAutoBrightnessStatus.Attach(pNodeMap, "BslChunkAutoBrightnessStatus");
        m_pData->BslChunkTimestampSelector.Attach(pNodeMap, "BslChunkTimestampSelector");
        m_pData->BslChunkTimestampValue.Attach(pNodeMap, "BslChunkTimestampValue");
        m_pData->BslColorSpace.Attach(pNodeMap, "BslColorSpace");
        m_pData->BslContrast.Attach(pNodeMap, "BslContrast");
        m_pData->BslContrastMode.Attach(pNodeMap, "BslContrastMode");
        m_pData->BslDefectPixelCorrectionMode.Attach(pNodeMap, "BslDefectPixelCorrectionMode");
        m_pData->BslDeviceLinkCurrentThroughput.Attach(pNodeMap, "BslDeviceLinkCurrentThroughput");
        m_pData->BslEffectiveExposureTime.Attach(pNodeMap, "BslEffectiveExposureTime");
        m_pData->BslErrorPresent.Attach(pNodeMap, "BslErrorPresent");
        m_pData->BslErrorReportNext.Attach(pNodeMap, "BslErrorReportNext");
        m_pData->BslErrorReportValue.Attach(pNodeMap, "BslErrorReportValue");
        m_pData->BslExposureStartDelay.Attach(pNodeMap, "BslExposureStartDelay");
        m_pData->BslHue.Attach(pNodeMap, "BslHue");
        m_pData->BslInputFilterTime.Attach(pNodeMap, "BslInputFilterTime");
        m_pData->BslInputHoldOffTime.Attach(pNodeMap, "BslInputHoldOffTime");
        m_pData->BslLightSourcePreset.Attach(pNodeMap, "BslLightSourcePreset");
        m_pData->BslLightSourcePresetFeatureEnable.Attach(pNodeMap, "BslLightSourcePresetFeatureEnable");
        m_pData->BslLightSourcePresetFeatureSelector.Attach(pNodeMap, "BslLightSourcePresetFeatureSelector");
        m_pData->BslLineConnection.Attach(pNodeMap, "BslLineConnection");
        m_pData->BslNoiseReduction.Attach(pNodeMap, "BslNoiseReduction");
        m_pData->BslResultingAcquisitionFrameRate.Attach(pNodeMap, "BslResultingAcquisitionFrameRate");
        m_pData->BslResultingFrameBurstRate.Attach(pNodeMap, "BslResultingFrameBurstRate");
        m_pData->BslResultingTransferFrameRate.Attach(pNodeMap, "BslResultingTransferFrameRate");
        m_pData->BslSaturation.Attach(pNodeMap, "BslSaturation");
        m_pData->BslScalingFactor.Attach(pNodeMap, "BslScalingFactor");
        m_pData->BslSensorBitDepth.Attach(pNodeMap, "BslSensorBitDepth");
        m_pData->BslSensorBitDepthMode.Attach(pNodeMap, "BslSensorBitDepthMode");
        m_pData->BslSensorOff.Attach(pNodeMap, "BslSensorOff");
        m_pData->BslSensorOn.Attach(pNodeMap, "BslSensorOn");
        m_pData->BslSensorStandby.Attach(pNodeMap, "BslSensorStandby");
        m_pData->BslSensorState.Attach(pNodeMap, "BslSensorState");
        m_pData->BslSharpnessEnhancement.Attach(pNodeMap, "BslSharpnessEnhancement");
        m_pData->BslTemperatureMax.Attach(pNodeMap, "BslTemperatureMax");
        m_pData->BslTemperatureStatus.Attach(pNodeMap, "BslTemperatureStatus");
        m_pData->BslTemperatureStatusErrorCount.Attach(pNodeMap, "BslTemperatureStatusErrorCount");
        m_pData->BslTwiBitrate.Attach(pNodeMap, "BslTwiBitrate");
        m_pData->BslTwiPullSclLow.Attach(pNodeMap, "BslTwiPullSclLow");
        m_pData->BslTwiPullSdaLow.Attach(pNodeMap, "BslTwiPullSdaLow");
        m_pData->BslTwiRead.Attach(pNodeMap, "BslTwiRead");
        m_pData->BslTwiTargetAddress.Attach(pNodeMap, "BslTwiTargetAddress");
        m_pData->BslTwiTransferBuffer.Attach(pNodeMap, "BslTwiTransferBuffer");
        m_pData->BslTwiTransferLength.Attach(pNodeMap, "BslTwiTransferLength");
        m_pData->BslTwiTransferStatus.Attach(pNodeMap, "BslTwiTransferStatus");
        m_pData->BslTwiUpdateTransferStatus.Attach(pNodeMap, "BslTwiUpdateTransferStatus");
        m_pData->BslTwiWrite.Attach(pNodeMap, "BslTwiWrite");
        m_pData->BslUSBPowerSource.Attach(pNodeMap, "BslUSBPowerSource");
        m_pData->BslUSBSpeedMode.Attach(pNodeMap, "BslUSBSpeedMode");
        m_pData->ChunkCounterSelector.Attach(pNodeMap, "ChunkCounterSelector");
        m_pData->ChunkCounterValue.Attach(pNodeMap, "ChunkCounterValue");
        m_pData->ChunkEnable.Attach(pNodeMap, "ChunkEnable");
        m_pData->ChunkExposureTime.Attach(pNodeMap, "ChunkExposureTime");
        m_pData->ChunkFrameID.Attach(pNodeMap, "ChunkFrameID");
        m_pData->ChunkGain.Attach(pNodeMap, "ChunkGain");
        m_pData->ChunkLineStatusAll.Attach(pNodeMap, "ChunkLineStatusAll");
        m_pData->ChunkModeActive.Attach(pNodeMap, "ChunkModeActive");
        m_pData->ChunkPayloadCRC16.Attach(pNodeMap, "ChunkPayloadCRC16");
        m_pData->ChunkSelector.Attach(pNodeMap, "ChunkSelector");
        m_pData->CounterDuration.Attach(pNodeMap, "CounterDuration");
        m_pData->CounterEventActivation.Attach(pNodeMap, "CounterEventActivation");
        m_pData->CounterEventSource.Attach(pNodeMap, "CounterEventSource");
        m_pData->CounterReset.Attach(pNodeMap, "CounterReset");
        m_pData->CounterResetActivation.Attach(pNodeMap, "CounterResetActivation");
        m_pData->CounterResetSource.Attach(pNodeMap, "CounterResetSource");
        m_pData->CounterSelector.Attach(pNodeMap, "CounterSelector");
        m_pData->CounterStatus.Attach(pNodeMap, "CounterStatus");
        m_pData->CounterTriggerActivation.Attach(pNodeMap, "CounterTriggerActivation");
        m_pData->CounterTriggerSource.Attach(pNodeMap, "CounterTriggerSource");
        m_pData->CounterValue.Attach(pNodeMap, "CounterValue");
        m_pData->DeviceCharacterSet.Attach(pNodeMap, "DeviceCharacterSet");
        m_pData->DeviceFamilyName.Attach(pNodeMap, "DeviceFamilyName");
        m_pData->DeviceFeaturePersistenceEnd.Attach(pNodeMap, "DeviceFeaturePersistenceEnd");
        m_pData->DeviceFeaturePersistenceStart.Attach(pNodeMap, "DeviceFeaturePersistenceStart");
        m_pData->DeviceFirmwareVersion.Attach(pNodeMap, "DeviceFirmwareVersion");
        m_pData->DeviceGenCPVersionMajor.Attach(pNodeMap, "DeviceGenCPVersionMajor");
        m_pData->DeviceGenCPVersionMinor.Attach(pNodeMap, "DeviceGenCPVersionMinor");
        m_pData->DeviceIndicatorMode.Attach(pNodeMap, "DeviceIndicatorMode");
        m_pData->DeviceLinkSpeed.Attach(pNodeMap, "DeviceLinkSpeed");
        m_pData->DeviceLinkThroughputLimit.Attach(pNodeMap, "DeviceLinkThroughputLimit");
        m_pData->DeviceLinkThroughputLimitMode.Attach(pNodeMap, "DeviceLinkThroughputLimitMode");
        m_pData->DeviceManifestSchemaMajorVersion.Attach(pNodeMap, "DeviceManifestSchemaMajorVersion");
        m_pData->DeviceManifestSchemaMinorVersion.Attach(pNodeMap, "DeviceManifestSchemaMinorVersion");
        m_pData->DeviceManifestXMLMajorVersion.Attach(pNodeMap, "DeviceManifestXMLMajorVersion");
        m_pData->DeviceManifestXMLMinorVersion.Attach(pNodeMap, "DeviceManifestXMLMinorVersion");
        m_pData->DeviceManifestXMLSubMinorVersion.Attach(pNodeMap, "DeviceManifestXMLSubMinorVersion");
        m_pData->DeviceManufacturerInfo.Attach(pNodeMap, "DeviceManufacturerInfo");
        m_pData->DeviceModelName.Attach(pNodeMap, "DeviceModelName");
        m_pData->DeviceRegistersEndianness.Attach(pNodeMap, "DeviceRegistersEndianness");
        m_pData->DeviceRegistersStreamingEnd.Attach(pNodeMap, "DeviceRegistersStreamingEnd");
        m_pData->DeviceRegistersStreamingStart.Attach(pNodeMap, "DeviceRegistersStreamingStart");
        m_pData->DeviceReset.Attach(pNodeMap, "DeviceReset");
        m_pData->DeviceSFNCVersionMajor.Attach(pNodeMap, "DeviceSFNCVersionMajor");
        m_pData->DeviceSFNCVersionMinor.Attach(pNodeMap, "DeviceSFNCVersionMinor");
        m_pData->DeviceSFNCVersionSubMinor.Attach(pNodeMap, "DeviceSFNCVersionSubMinor");
        m_pData->DeviceScanType.Attach(pNodeMap, "DeviceScanType");
        m_pData->DeviceSerialNumber.Attach(pNodeMap, "DeviceSerialNumber");
        m_pData->DeviceTLType.Attach(pNodeMap, "DeviceTLType");
        m_pData->DeviceTLVersionMajor.Attach(pNodeMap, "DeviceTLVersionMajor");
        m_pData->DeviceTLVersionMinor.Attach(pNodeMap, "DeviceTLVersionMinor");
        m_pData->DeviceTLVersionSubMinor.Attach(pNodeMap, "DeviceTLVersionSubMinor");
        m_pData->DeviceTemperature.Attach(pNodeMap, "DeviceTemperature");
        m_pData->DeviceTemperatureSelector.Attach(pNodeMap, "DeviceTemperatureSelector");
        m_pData->DeviceUserID.Attach(pNodeMap, "DeviceUserID");
        m_pData->DeviceVendorName.Attach(pNodeMap, "DeviceVendorName");
        m_pData->DeviceVersion.Attach(pNodeMap, "DeviceVersion");
        m_pData->DigitalShift.Attach(pNodeMap, "DigitalShift");
        m_pData->EventExposureEnd.Attach(pNodeMap, "EventExposureEnd");
        m_pData->EventExposureEndFrameID.Attach(pNodeMap, "EventExposureEndFrameID");
        m_pData->EventExposureEndTimestamp.Attach(pNodeMap, "EventExposureEndTimestamp");
        m_pData->EventFrameStart.Attach(pNodeMap, "EventFrameStart");
        m_pData->EventFrameStartFrameID.Attach(pNodeMap, "EventFrameStartFrameID");
        m_pData->EventFrameStartTimestamp.Attach(pNodeMap, "EventFrameStartTimestamp");
        m_pData->EventFrameTriggerMissed.Attach(pNodeMap, "EventFrameTriggerMissed");
        m_pData->EventFrameTriggerMissedTimestamp.Attach(pNodeMap, "EventFrameTriggerMissedTimestamp");
        m_pData->EventNotification.Attach(pNodeMap, "EventNotification");
        m_pData->EventOverrun.Attach(pNodeMap, "EventOverrun");
        m_pData->EventOverrunTimestamp.Attach(pNodeMap, "EventOverrunTimestamp");
        m_pData->EventSelector.Attach(pNodeMap, "EventSelector");
        m_pData->EventTemperatureStatusChanged.Attach(pNodeMap, "EventTemperatureStatusChanged");
        m_pData->EventTemperatureStatusChangedStatus.Attach(pNodeMap, "EventTemperatureStatusChangedStatus");
        m_pData->EventTemperatureStatusChangedTimestamp.Attach(pNodeMap, "EventTemperatureStatusChangedTimestamp");
        m_pData->EventTest.Attach(pNodeMap, "EventTest");
        m_pData->EventTestTimestamp.Attach(pNodeMap, "EventTestTimestamp");
        m_pData->ExposureAuto.Attach(pNodeMap, "ExposureAuto");
        m_pData->ExposureMode.Attach(pNodeMap, "ExposureMode");
        m_pData->ExposureTime.Attach(pNodeMap, "ExposureTime");
        m_pData->FileAccessBuffer.Attach(pNodeMap, "FileAccessBuffer");
        m_pData->FileAccessLength.Attach(pNodeMap, "FileAccessLength");
        m_pData->FileAccessOffset.Attach(pNodeMap, "FileAccessOffset");
        m_pData->FileOpenMode.Attach(pNodeMap, "FileOpenMode");
        m_pData->FileOperationExecute.Attach(pNodeMap, "FileOperationExecute");
        m_pData->FileOperationResult.Attach(pNodeMap, "FileOperationResult");
        m_pData->FileOperationSelector.Attach(pNodeMap, "FileOperationSelector");
        m_pData->FileOperationStatus.Attach(pNodeMap, "FileOperationStatus");
        m_pData->FileSelector.Attach(pNodeMap, "FileSelector");
        m_pData->Gain.Attach(pNodeMap, "Gain");
        m_pData->GainAuto.Attach(pNodeMap, "GainAuto");
        m_pData->Gamma.Attach(pNodeMap, "Gamma");
        m_pData->Height.Attach(pNodeMap, "Height");
        m_pData->HeightMax.Attach(pNodeMap, "HeightMax");
        m_pData->LineFormat.Attach(pNodeMap, "LineFormat");
        m_pData->LineInverter.Attach(pNodeMap, "LineInverter");
        m_pData->LineMode.Attach(pNodeMap, "LineMode");
        m_pData->LineSelector.Attach(pNodeMap, "LineSelector");
        m_pData->LineSource.Attach(pNodeMap, "LineSource");
        m_pData->LineStatus.Attach(pNodeMap, "LineStatus");
        m_pData->LineStatusAll.Attach(pNodeMap, "LineStatusAll");
        m_pData->OffsetX.Attach(pNodeMap, "OffsetX");
        m_pData->OffsetY.Attach(pNodeMap, "OffsetY");
        m_pData->PayloadSize.Attach(pNodeMap, "PayloadSize");
        m_pData->PixelDynamicRangeMax.Attach(pNodeMap, "PixelDynamicRangeMax");
        m_pData->PixelDynamicRangeMin.Attach(pNodeMap, "PixelDynamicRangeMin");
        m_pData->PixelFormat.Attach(pNodeMap, "PixelFormat");
        m_pData->PixelSize.Attach(pNodeMap, "PixelSize");
        m_pData->ReverseX.Attach(pNodeMap, "ReverseX");
        m_pData->ReverseY.Attach(pNodeMap, "ReverseY");
        m_pData->SIPayloadFinalTransfer1Size.Attach(pNodeMap, "SIPayloadFinalTransfer1Size");
        m_pData->SIPayloadFinalTransfer2Size.Attach(pNodeMap, "SIPayloadFinalTransfer2Size");
        m_pData->SIPayloadTransferCount.Attach(pNodeMap, "SIPayloadTransferCount");
        m_pData->SIPayloadTransferSize.Attach(pNodeMap, "SIPayloadTransferSize");
        m_pData->SensorHeight.Attach(pNodeMap, "SensorHeight");
        m_pData->SensorReadoutTime.Attach(pNodeMap, "SensorReadoutTime");
        m_pData->SensorWidth.Attach(pNodeMap, "SensorWidth");
        m_pData->SoftwareSignalPulse.Attach(pNodeMap, "SoftwareSignalPulse");
        m_pData->SoftwareSignalSelector.Attach(pNodeMap, "SoftwareSignalSelector");
        m_pData->TestEventGenerate.Attach(pNodeMap, "TestEventGenerate");
        m_pData->TestPattern.Attach(pNodeMap, "TestPattern");
        m_pData->TestPendingAck.Attach(pNodeMap, "TestPendingAck");
        m_pData->TimerDelay.Attach(pNodeMap, "TimerDelay");
        m_pData->TimerDuration.Attach(pNodeMap, "TimerDuration");
        m_pData->TimerReset.Attach(pNodeMap, "TimerReset");
        m_pData->TimerSelector.Attach(pNodeMap, "TimerSelector");
        m_pData->TimerStatus.Attach(pNodeMap, "TimerStatus");
        m_pData->TimerTriggerActivation.Attach(pNodeMap, "TimerTriggerActivation");
        m_pData->TimerTriggerArmDelay.Attach(pNodeMap, "TimerTriggerArmDelay");
        m_pData->TimerTriggerSource.Attach(pNodeMap, "TimerTriggerSource");
        m_pData->TimestampLatch.Attach(pNodeMap, "TimestampLatch");
        m_pData->TimestampLatchValue.Attach(pNodeMap, "TimestampLatchValue");
        m_pData->TriggerActivation.Attach(pNodeMap, "TriggerActivation");
        m_pData->TriggerDelay.Attach(pNodeMap, "TriggerDelay");
        m_pData->TriggerMode.Attach(pNodeMap, "TriggerMode");
        m_pData->TriggerSelector.Attach(pNodeMap, "TriggerSelector");
        m_pData->TriggerSoftware.Attach(pNodeMap, "TriggerSoftware");
        m_pData->TriggerSource.Attach(pNodeMap, "TriggerSource");
        m_pData->UserDefinedValue.Attach(pNodeMap, "UserDefinedValue");
        m_pData->UserDefinedValueSelector.Attach(pNodeMap, "UserDefinedValueSelector");
        m_pData->UserOutputSelector.Attach(pNodeMap, "UserOutputSelector");
        m_pData->UserOutputValue.Attach(pNodeMap, "UserOutputValue");
        m_pData->UserOutputValueAll.Attach(pNodeMap, "UserOutputValueAll");
        m_pData->UserSetDefault.Attach(pNodeMap, "UserSetDefault");
        m_pData->UserSetLoad.Attach(pNodeMap, "UserSetLoad");
        m_pData->UserSetSave.Attach(pNodeMap, "UserSetSave");
        m_pData->UserSetSelector.Attach(pNodeMap, "UserSetSelector");
        m_pData->Width.Attach(pNodeMap, "Width");
        m_pData->WidthMax.Attach(pNodeMap, "WidthMax");
    }

    //! \endcond

} // namespace Pylon
} // namespace BaslerCameraCameraParams_Params

#ifdef _MSC_VER
#pragma warning( pop )
#endif