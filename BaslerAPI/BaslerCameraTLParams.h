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

#ifndef BASLER_PYLON_BASLERCAMERATLPARAMS_H
#define BASLER_PYLON_BASLERCAMERATLPARAMS_H

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
namespace BaslerCameraTLParams_Params
{
    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************

    
    
    //**************************************************************************************************
    // Parameter class BaslerCameraTLParams
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for daA2448-70uc

    Sources:
    daA2448-70uc p=du1_imx548c/s=r/v=1.0.2/i=6515.14/h=61c0643
    */
    class BaslerCameraTLParams
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
            //! Constructor
            BaslerCameraTLParams(void);

            //! Destructor
            ~BaslerCameraTLParams(void);

            //! Initializes the references
            void _Initialize(GENAPI_NAMESPACE::INodeMap*);

    //! \endcond

    private:
        class BaslerCameraTLParams_Data;
        BaslerCameraTLParams_Data* m_pData;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
    //! \name Categories: Root
    //@{
    /*!
        \brief Enables mapping of certain SFNC 1 x node names to SFNC 2 x node names - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MigrationModeEnable" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IBooleanEx& MigrationModeEnable;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief Last error status of a read or write operation - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Last_Error_Status" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& Statistic_Last_Error_Status;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief Last error status of a read or write operation - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Last_Error_Status_Text" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IStringEx& Statistic_Last_Error_Status_Text;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief Number of failed read operations - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Read_Operations_Failed_Count" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& Statistic_Read_Operations_Failed_Count;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief Number of read pipe resets - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Read_Pipe_Reset_Count" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& Statistic_Read_Pipe_Reset_Count;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief Number of failed write operations - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Write_Operations_Failed_Count" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& Statistic_Write_Operations_Failed_Count;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief Number of write pipe resets - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Write_Pipe_Reset_Count" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& Statistic_Write_Pipe_Reset_Count;

    //@}


        private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
            BaslerCameraTLParams(BaslerCameraTLParams&);

            //! not implemented assignment operator
            BaslerCameraTLParams& operator=(BaslerCameraTLParams&);

        //! \endcond
    };

} // namespace Pylon
} // namespace BaslerCameraTLParams_Params

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // BASLER_PYLON_BASLERCAMERATLPARAMS_H