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
#include "BaslerCameraChunkDataParams.h"

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4250 ) // warning C4250: 'Pylon::CXYZParameter': inherits 'Pylon::CParameter::Pylon::CParameter::ZYX' via dominance
#endif

//! The namespace containing the a control interface and related enumeration types for daA2448-70uc
namespace Pylon
{
namespace BaslerCameraChunkDataParams_Params
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


    }

    //! \endcond
    //**************************************************************************************************
    // Parameter class BaslerCameraChunkDataParams implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS
    
    ///////////////////////////////////////////////////////////////////////////
    //
    class BaslerCameraChunkDataParams::BaslerCameraChunkDataParams_Data
    {
    public:
        EnumParameterClasses::BslChunkAutoBrightnessStatusEnumParameter BslChunkAutoBrightnessStatus;
        EnumParameterClasses::BslChunkTimestampSelectorEnumParameter BslChunkTimestampSelector;
        Pylon::CIntegerParameter BslChunkTimestampValue;
        EnumParameterClasses::ChunkCounterSelectorEnumParameter ChunkCounterSelector;
        Pylon::CIntegerParameter ChunkCounterValue;
        Pylon::CFloatParameter ChunkExposureTime;
        Pylon::CIntegerParameter ChunkFrameID;
        Pylon::CFloatParameter ChunkGain;
        Pylon::CIntegerParameter ChunkLineStatusAll;
        Pylon::CIntegerParameter ChunkPayloadCRC16;
    };


    ///////////////////////////////////////////////////////////////////////////
    //
    BaslerCameraChunkDataParams::BaslerCameraChunkDataParams(void)
        : m_pData(new BaslerCameraChunkDataParams_Data())
        , BslChunkAutoBrightnessStatus(m_pData->BslChunkAutoBrightnessStatus)
        , BslChunkTimestampSelector(m_pData->BslChunkTimestampSelector)
        , BslChunkTimestampValue(m_pData->BslChunkTimestampValue)
        , ChunkCounterSelector(m_pData->ChunkCounterSelector)
        , ChunkCounterValue(m_pData->ChunkCounterValue)
        , ChunkExposureTime(m_pData->ChunkExposureTime)
        , ChunkFrameID(m_pData->ChunkFrameID)
        , ChunkGain(m_pData->ChunkGain)
        , ChunkLineStatusAll(m_pData->ChunkLineStatusAll)
        , ChunkPayloadCRC16(m_pData->ChunkPayloadCRC16)
    {
    }


    ///////////////////////////////////////////////////////////////////////////
    //
    BaslerCameraChunkDataParams::~BaslerCameraChunkDataParams(void)
    {
        delete m_pData;
    }


    ///////////////////////////////////////////////////////////////////////////
    //
    void BaslerCameraChunkDataParams::_Initialize(GENAPI_NAMESPACE::INodeMap* pNodeMap)
    {
        m_pData->BslChunkAutoBrightnessStatus.Attach(pNodeMap, "BslChunkAutoBrightnessStatus");
        m_pData->BslChunkTimestampSelector.Attach(pNodeMap, "BslChunkTimestampSelector");
        m_pData->BslChunkTimestampValue.Attach(pNodeMap, "BslChunkTimestampValue");
        m_pData->ChunkCounterSelector.Attach(pNodeMap, "ChunkCounterSelector");
        m_pData->ChunkCounterValue.Attach(pNodeMap, "ChunkCounterValue");
        m_pData->ChunkExposureTime.Attach(pNodeMap, "ChunkExposureTime");
        m_pData->ChunkFrameID.Attach(pNodeMap, "ChunkFrameID");
        m_pData->ChunkGain.Attach(pNodeMap, "ChunkGain");
        m_pData->ChunkLineStatusAll.Attach(pNodeMap, "ChunkLineStatusAll");
        m_pData->ChunkPayloadCRC16.Attach(pNodeMap, "ChunkPayloadCRC16");
    }

    //! \endcond

} // namespace Pylon
} // namespace BaslerCameraChunkDataParams_Params

#ifdef _MSC_VER
#pragma warning( pop )
#endif