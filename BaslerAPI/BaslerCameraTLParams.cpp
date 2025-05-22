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
#include "BaslerCameraTLParams.h"

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4250 ) // warning C4250: 'Pylon::CXYZParameter': inherits 'Pylon::CParameter::Pylon::CParameter::ZYX' via dominance
#endif

//! The namespace containing the a control interface and related enumeration types for daA2448-70uc
namespace Pylon
{
namespace BaslerCameraTLParams_Params
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
    // Parameter class BaslerCameraTLParams implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS
    
    ///////////////////////////////////////////////////////////////////////////
    //
    class BaslerCameraTLParams::BaslerCameraTLParams_Data
    {
    public:
        Pylon::CBooleanParameter MigrationModeEnable;
        Pylon::CIntegerParameter Statistic_Last_Error_Status;
        Pylon::CStringParameter Statistic_Last_Error_Status_Text;
        Pylon::CIntegerParameter Statistic_Read_Operations_Failed_Count;
        Pylon::CIntegerParameter Statistic_Read_Pipe_Reset_Count;
        Pylon::CIntegerParameter Statistic_Write_Operations_Failed_Count;
        Pylon::CIntegerParameter Statistic_Write_Pipe_Reset_Count;
    };


    ///////////////////////////////////////////////////////////////////////////
    //
    BaslerCameraTLParams::BaslerCameraTLParams(void)
        : m_pData(new BaslerCameraTLParams_Data())
        , MigrationModeEnable(m_pData->MigrationModeEnable)
        , Statistic_Last_Error_Status(m_pData->Statistic_Last_Error_Status)
        , Statistic_Last_Error_Status_Text(m_pData->Statistic_Last_Error_Status_Text)
        , Statistic_Read_Operations_Failed_Count(m_pData->Statistic_Read_Operations_Failed_Count)
        , Statistic_Read_Pipe_Reset_Count(m_pData->Statistic_Read_Pipe_Reset_Count)
        , Statistic_Write_Operations_Failed_Count(m_pData->Statistic_Write_Operations_Failed_Count)
        , Statistic_Write_Pipe_Reset_Count(m_pData->Statistic_Write_Pipe_Reset_Count)
    {
    }


    ///////////////////////////////////////////////////////////////////////////
    //
    BaslerCameraTLParams::~BaslerCameraTLParams(void)
    {
        delete m_pData;
    }


    ///////////////////////////////////////////////////////////////////////////
    //
    void BaslerCameraTLParams::_Initialize(GENAPI_NAMESPACE::INodeMap* pNodeMap)
    {
        m_pData->MigrationModeEnable.Attach(pNodeMap, "MigrationModeEnable");
        m_pData->Statistic_Last_Error_Status.Attach(pNodeMap, "Statistic_Last_Error_Status");
        m_pData->Statistic_Last_Error_Status_Text.Attach(pNodeMap, "Statistic_Last_Error_Status_Text");
        m_pData->Statistic_Read_Operations_Failed_Count.Attach(pNodeMap, "Statistic_Read_Operations_Failed_Count");
        m_pData->Statistic_Read_Pipe_Reset_Count.Attach(pNodeMap, "Statistic_Read_Pipe_Reset_Count");
        m_pData->Statistic_Write_Operations_Failed_Count.Attach(pNodeMap, "Statistic_Write_Operations_Failed_Count");
        m_pData->Statistic_Write_Pipe_Reset_Count.Attach(pNodeMap, "Statistic_Write_Pipe_Reset_Count");
    }

    //! \endcond

} // namespace Pylon
} // namespace BaslerCameraTLParams_Params

#ifdef _MSC_VER
#pragma warning( pop )
#endif