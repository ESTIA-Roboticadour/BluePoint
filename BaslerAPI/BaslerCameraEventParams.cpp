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
#include "BaslerCameraEventParams.h"

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4250 ) // warning C4250: 'Pylon::CXYZParameter': inherits 'Pylon::CParameter::Pylon::CParameter::ZYX' via dominance
#endif

//! The namespace containing the a control interface and related enumeration types for daA2448-70uc
namespace Pylon
{
namespace BaslerCameraEventParams_Params
{
    //**************************************************************************************************
    // Enumeration support classes
    //**************************************************************************************************
    //! \cond HIDE_CLASS_METHODS

    ///////////////////////////////////////////////////////////////////////////
    //
    namespace EnumParameterClasses
    {
    }

    //! \endcond
    //**************************************************************************************************
    // Parameter class BaslerCameraEventParams implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS
    
    ///////////////////////////////////////////////////////////////////////////
    //
    class BaslerCameraEventParams::BaslerCameraEventParams_Data
    {
    public:
        Pylon::CIntegerParameter NumBuffer;
        Pylon::CIntegerParameter NumMaxQueuedUrbs;
        Pylon::CIntegerParameter Statistic_Failed_Event_Count;
        Pylon::CIntegerParameter Statistic_Last_Failed_Event_Buffer_Status;
        Pylon::CIntegerParameter Statistic_Total_Event_Count;
        Pylon::CIntegerParameter TransferLoopThreadPriority;
    };


    ///////////////////////////////////////////////////////////////////////////
    //
    BaslerCameraEventParams::BaslerCameraEventParams(void)
        : m_pData(new BaslerCameraEventParams_Data())
        , NumBuffer(m_pData->NumBuffer)
        , NumMaxQueuedUrbs(m_pData->NumMaxQueuedUrbs)
        , Statistic_Failed_Event_Count(m_pData->Statistic_Failed_Event_Count)
        , Statistic_Last_Failed_Event_Buffer_Status(m_pData->Statistic_Last_Failed_Event_Buffer_Status)
        , Statistic_Total_Event_Count(m_pData->Statistic_Total_Event_Count)
        , TransferLoopThreadPriority(m_pData->TransferLoopThreadPriority)
    {
    }


    ///////////////////////////////////////////////////////////////////////////
    //
    BaslerCameraEventParams::~BaslerCameraEventParams(void)
    {
        delete m_pData;
    }


    ///////////////////////////////////////////////////////////////////////////
    //
    void BaslerCameraEventParams::_Initialize(GENAPI_NAMESPACE::INodeMap* pNodeMap)
    {
        m_pData->NumBuffer.Attach(pNodeMap, "NumBuffer");
        m_pData->NumMaxQueuedUrbs.Attach(pNodeMap, "NumMaxQueuedUrbs");
        m_pData->Statistic_Failed_Event_Count.Attach(pNodeMap, "Statistic_Failed_Event_Count");
        m_pData->Statistic_Last_Failed_Event_Buffer_Status.Attach(pNodeMap, "Statistic_Last_Failed_Event_Buffer_Status");
        m_pData->Statistic_Total_Event_Count.Attach(pNodeMap, "Statistic_Total_Event_Count");
        m_pData->TransferLoopThreadPriority.Attach(pNodeMap, "TransferLoopThreadPriority");
    }

    //! \endcond

} // namespace Pylon
} // namespace BaslerCameraEventParams_Params

#ifdef _MSC_VER
#pragma warning( pop )
#endif