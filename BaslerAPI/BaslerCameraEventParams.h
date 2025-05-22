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

#ifndef BASLER_PYLON_BASLERCAMERAEVENTPARAMS_H
#define BASLER_PYLON_BASLERCAMERAEVENTPARAMS_H

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
namespace BaslerCameraEventParams_Params
{
    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************

    
    
    //**************************************************************************************************
    // Parameter class BaslerCameraEventParams
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for daA2448-70uc

    Sources:
    daA2448-70uc p=du1_imx548c/s=r/v=1.0.2/i=6515.14/h=61c0643
    */
    class BaslerCameraEventParams
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
            //! Constructor
            BaslerCameraEventParams(void);

            //! Destructor
            ~BaslerCameraEventParams(void);

            //! Initializes the references
            void _Initialize(GENAPI_NAMESPACE::INodeMap*);

    //! \endcond

    private:
        class BaslerCameraEventParams_Data;
        BaslerCameraEventParams_Data* m_pData;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
    //! \name Categories: Root
    //@{
    /*!
        \brief Number of buffers to be used - Applies to: daA2448-70uc

        Number of Buffers that are going to be used receiving events.
    
        Visibility: Expert

    */
    Pylon::IIntegerEx& NumBuffer;

    //@}


    //! \name Categories: Root
    //@{
    /*!
        \brief Maximum number of USB request blocks (URBs) to be enqueued simultaneously - Applies to: daA2448-70uc

    
        Visibility: Guru

    */
    Pylon::IIntegerEx& NumMaxQueuedUrbs;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief Count of processed events with an error status - Applies to: daA2448-70uc

    
        Visibility: Expert

    */
    Pylon::IIntegerEx& Statistic_Failed_Event_Count;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief Status code of the last failed event buffer - Applies to: daA2448-70uc

    
        Visibility: Expert

    */
    Pylon::IIntegerEx& Statistic_Last_Failed_Event_Buffer_Status;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief Total count of processed events - Applies to: daA2448-70uc

    
        Visibility: Expert

    */
    Pylon::IIntegerEx& Statistic_Total_Event_Count;

    //@}


    //! \name Categories: Root
    //@{
    /*!
        \brief Priority of the thread that handles USB requests from the stream interface - Applies to: daA2448-70uc

    
        Visibility: Guru

    */
    Pylon::IIntegerEx& TransferLoopThreadPriority;

    //@}


        private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
            BaslerCameraEventParams(BaslerCameraEventParams&);

            //! not implemented assignment operator
            BaslerCameraEventParams& operator=(BaslerCameraEventParams&);

        //! \endcond
    };

} // namespace Pylon
} // namespace BaslerCameraEventParams_Params

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // BASLER_PYLON_BASLERCAMERAEVENTPARAMS_H