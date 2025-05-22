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

#ifndef BASLER_PYLON_BASLERCAMERASTREAMPARAMS_H
#define BASLER_PYLON_BASLERCAMERASTREAMPARAMS_H

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
namespace BaslerCameraStreamParams_Params
{
    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************

    
    
    //**************************************************************************************************
    // Parameter class BaslerCameraStreamParams
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for daA2448-70uc

    Sources:
    daA2448-70uc p=du1_imx548c/s=r/v=1.0.2/i=6515.14/h=61c0643
    */
    class BaslerCameraStreamParams
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
            //! Constructor
            BaslerCameraStreamParams(void);

            //! Destructor
            ~BaslerCameraStreamParams(void);

            //! Initializes the references
            void _Initialize(GENAPI_NAMESPACE::INodeMap*);

    //! \endcond

    private:
        class BaslerCameraStreamParams_Data;
        BaslerCameraStreamParams_Data* m_pData;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
    //! \name Categories: Root
    //@{
    /*!
        \brief Maximum size (in bytes) of a buffer used for grabbing images - Applies to: daA2448-70uc

        Maximum size (in bytes) of a buffer used for grabbing images. A grab application must set this parameter before grabbing starts.
    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MaxBufferSize" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& MaxBufferSize;

    //@}


    //! \name Categories: Root
    //@{
    /*!
        \brief Maximum number of buffers that can be used simultaneously for grabbing images - Applies to: daA2448-70uc

    
        Visibility: Beginner

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MaxNumBuffer" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& MaxNumBuffer;

    //@}


    //! \name Categories: Root
    //@{
    /*!
        \brief Maximum USB data transfer size in bytes - Applies to: daA2448-70uc

        
            
            Maximum USB data transfer size in bytes. 
            The default value is appropriate for most applications. 
            Decreasing the value may increase the CPU load. 
            USB host adapter drivers may require decreasing the value 
            if the application fails to receive the image stream. 
            The maximum value also depends on the operating system.
            
        
    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MaxTransferSize" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& MaxTransferSize;

    //@}


    //! \name Categories: Root
    //@{
    /*!
        \brief Maximum number of USB request blocks (URBs) to be enqueued simultaneously - Applies to: daA2448-70uc

        Maximum number of USB request blocks (URBs) to be enqueued simultaneously. Increasing this value may improve stability and reduce jitter, but requires more resources on the host computer.
    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=NumMaxQueuedUrbs" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& NumMaxQueuedUrbs;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief GigE cameras: Number of buffers with at least one failed packet  A packet is considered failed if its status is not 'success'  Other cameras: Number of buffers that returned with an error status   - Applies to: daA2448-70uc

        GigE cameras: Number of buffers with at least one failed packet. A packet is considered failed if its status is not 'success'. Other cameras: Number of buffers that returned an error. 
    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Failed_Buffer_Count" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& Statistic_Failed_Buffer_Count;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief Last grabbed block ID - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Last_Block_Id" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& Statistic_Last_Block_Id;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief Status code of the last failed buffer - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Last_Failed_Buffer_Status" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& Statistic_Last_Failed_Buffer_Status;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief Status code of the last failed buffer - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Last_Failed_Buffer_Status_Text" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IStringEx& Statistic_Last_Failed_Buffer_Status_Text;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief Number of corrupt or lost frames between successfully grabbed images - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Missed_Frame_Count" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& Statistic_Missed_Frame_Count;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief Number of out-of-memory errors - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Out_Of_Memory_Error_Count" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& Statistic_Out_Of_Memory_Error_Count;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief Number of stream resynchronizations - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Resynchronization_Count" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& Statistic_Resynchronization_Count;

    //@}


    //! \name Categories: Statistic
    //@{
    /*!
        \brief GigE cameras: Number of frames received  Other cameras: Number of buffers processed - Applies to: daA2448-70uc

    
        Visibility: Expert

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Total_Buffer_Count" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& Statistic_Total_Buffer_Count;

    //@}


    //! \name Categories: Root
    //@{
    /*!
        \brief Priority of the thread that handles USB requests from the stream interface - Applies to: daA2448-70uc

    
        Visibility: Guru

        The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TransferLoopThreadPriority" target="_blank">Basler Product Documentation</a> may provide more information.
    */
    Pylon::IIntegerEx& TransferLoopThreadPriority;

    //@}


        private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
            BaslerCameraStreamParams(BaslerCameraStreamParams&);

            //! not implemented assignment operator
            BaslerCameraStreamParams& operator=(BaslerCameraStreamParams&);

        //! \endcond
    };

} // namespace Pylon
} // namespace BaslerCameraStreamParams_Params

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // BASLER_PYLON_BASLERCAMERASTREAMPARAMS_H