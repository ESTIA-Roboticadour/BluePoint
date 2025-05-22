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
#include "BaslerCameraStreamParams.h"

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4250 ) // warning C4250: 'Pylon::CXYZParameter': inherits 'Pylon::CParameter::Pylon::CParameter::ZYX' via dominance
#endif

//! The namespace containing the a control interface and related enumeration types for daA2448-70uc
namespace Pylon
{
namespace BaslerCameraStreamParams_Params
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
    // Parameter class BaslerCameraStreamParams implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS
    
    ///////////////////////////////////////////////////////////////////////////
    //
    class BaslerCameraStreamParams::BaslerCameraStreamParams_Data
    {
    public:
        Pylon::CIntegerParameter MaxBufferSize;
        Pylon::CIntegerParameter MaxNumBuffer;
        Pylon::CIntegerParameter MaxTransferSize;
        Pylon::CIntegerParameter NumMaxQueuedUrbs;
        Pylon::CIntegerParameter Statistic_Failed_Buffer_Count;
        Pylon::CIntegerParameter Statistic_Last_Block_Id;
        Pylon::CIntegerParameter Statistic_Last_Failed_Buffer_Status;
        Pylon::CStringParameter Statistic_Last_Failed_Buffer_Status_Text;
        Pylon::CIntegerParameter Statistic_Missed_Frame_Count;
        Pylon::CIntegerParameter Statistic_Out_Of_Memory_Error_Count;
        Pylon::CIntegerParameter Statistic_Resynchronization_Count;
        Pylon::CIntegerParameter Statistic_Total_Buffer_Count;
        Pylon::CIntegerParameter TransferLoopThreadPriority;
    };


    ///////////////////////////////////////////////////////////////////////////
    //
    BaslerCameraStreamParams::BaslerCameraStreamParams(void)
        : m_pData(new BaslerCameraStreamParams_Data())
        , MaxBufferSize(m_pData->MaxBufferSize)
        , MaxNumBuffer(m_pData->MaxNumBuffer)
        , MaxTransferSize(m_pData->MaxTransferSize)
        , NumMaxQueuedUrbs(m_pData->NumMaxQueuedUrbs)
        , Statistic_Failed_Buffer_Count(m_pData->Statistic_Failed_Buffer_Count)
        , Statistic_Last_Block_Id(m_pData->Statistic_Last_Block_Id)
        , Statistic_Last_Failed_Buffer_Status(m_pData->Statistic_Last_Failed_Buffer_Status)
        , Statistic_Last_Failed_Buffer_Status_Text(m_pData->Statistic_Last_Failed_Buffer_Status_Text)
        , Statistic_Missed_Frame_Count(m_pData->Statistic_Missed_Frame_Count)
        , Statistic_Out_Of_Memory_Error_Count(m_pData->Statistic_Out_Of_Memory_Error_Count)
        , Statistic_Resynchronization_Count(m_pData->Statistic_Resynchronization_Count)
        , Statistic_Total_Buffer_Count(m_pData->Statistic_Total_Buffer_Count)
        , TransferLoopThreadPriority(m_pData->TransferLoopThreadPriority)
    {
    }


    ///////////////////////////////////////////////////////////////////////////
    //
    BaslerCameraStreamParams::~BaslerCameraStreamParams(void)
    {
        delete m_pData;
    }


    ///////////////////////////////////////////////////////////////////////////
    //
    void BaslerCameraStreamParams::_Initialize(GENAPI_NAMESPACE::INodeMap* pNodeMap)
    {
        m_pData->MaxBufferSize.Attach(pNodeMap, "MaxBufferSize");
        m_pData->MaxNumBuffer.Attach(pNodeMap, "MaxNumBuffer");
        m_pData->MaxTransferSize.Attach(pNodeMap, "MaxTransferSize");
        m_pData->NumMaxQueuedUrbs.Attach(pNodeMap, "NumMaxQueuedUrbs");
        m_pData->Statistic_Failed_Buffer_Count.Attach(pNodeMap, "Statistic_Failed_Buffer_Count");
        m_pData->Statistic_Last_Block_Id.Attach(pNodeMap, "Statistic_Last_Block_Id");
        m_pData->Statistic_Last_Failed_Buffer_Status.Attach(pNodeMap, "Statistic_Last_Failed_Buffer_Status");
        m_pData->Statistic_Last_Failed_Buffer_Status_Text.Attach(pNodeMap, "Statistic_Last_Failed_Buffer_Status_Text");
        m_pData->Statistic_Missed_Frame_Count.Attach(pNodeMap, "Statistic_Missed_Frame_Count");
        m_pData->Statistic_Out_Of_Memory_Error_Count.Attach(pNodeMap, "Statistic_Out_Of_Memory_Error_Count");
        m_pData->Statistic_Resynchronization_Count.Attach(pNodeMap, "Statistic_Resynchronization_Count");
        m_pData->Statistic_Total_Buffer_Count.Attach(pNodeMap, "Statistic_Total_Buffer_Count");
        m_pData->TransferLoopThreadPriority.Attach(pNodeMap, "TransferLoopThreadPriority");
    }

    //! \endcond

} // namespace Pylon
} // namespace BaslerCameraStreamParams_Params

#ifdef _MSC_VER
#pragma warning( pop )
#endif