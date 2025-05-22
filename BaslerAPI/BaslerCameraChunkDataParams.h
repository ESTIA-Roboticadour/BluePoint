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

#ifndef BASLER_PYLON_BASLERCAMERACHUNKDATAPARAMS_H
#define BASLER_PYLON_BASLERCAMERACHUNKDATAPARAMS_H

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
namespace BaslerCameraChunkDataParams_Params
{
    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
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

    //! Valid values for ChunkCounterSelector
    enum ChunkCounterSelectorEnums
    {
        ChunkCounterSelector_Counter1,  //!< Chunk data can be retrieved from counter 1 - Applies to: daA2448-70uc
        ChunkCounterSelector_Counter2  //!< Chunk data can be retrieved from counter 2 - Applies to: daA2448-70uc
    };


    
    
    //**************************************************************************************************
    // Parameter class BaslerCameraChunkDataParams
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for daA2448-70uc

    Sources:
    daA2448-70uc p=du1_imx548c/s=r/v=1.0.2/i=6515.14/h=61c0643
    */
    class BaslerCameraChunkDataParams
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
            //! Constructor
            BaslerCameraChunkDataParams(void);

            //! Destructor
            ~BaslerCameraChunkDataParams(void);

            //! Initializes the references
            void _Initialize(GENAPI_NAMESPACE::INodeMap*);

    //! \endcond

    private:
        class BaslerCameraChunkDataParams_Data;
        BaslerCameraChunkDataParams_Data* m_pData;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
    //! \name Categories: ChunkData
    //@{
    /*!
        \brief Indicates the status of the target brightness adjustments performed by the Exposure Auto and Gain Auto auto functions - Applies to: daA2448-70uc

    
        Visibility: Expert

    */
    Pylon::IEnumParameterT<BslChunkAutoBrightnessStatusEnums>& BslChunkAutoBrightnessStatus;

    //@}


    //! \name Categories: ChunkData
    //@{
    /*!
        \brief Sets which information should be included in the Chunk Timestamp Value chunk - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selecting Parameters: BslChunkTimestampValue

    */
    Pylon::IEnumParameterT<BslChunkTimestampSelectorEnums>& BslChunkTimestampSelector;

    //@}


    //! \name Categories: ChunkData
    //@{
    /*!
        \brief Value of the timestamp when the image was acquired - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: BslChunkTimestampSelector

    */
    Pylon::IIntegerEx& BslChunkTimestampValue;

    //@}


    //! \name Categories: ChunkData
    //@{
    /*!
        \brief Sets which counter to retrieve chunk data from - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selecting Parameters: ChunkCounterValue

    */
    Pylon::IEnumParameterT<ChunkCounterSelectorEnums>& ChunkCounterSelector;

    //@}


    //! \name Categories: ChunkData
    //@{
    /*!
        \brief Value of the selected chunk counter - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: ChunkCounterSelector

    */
    Pylon::IIntegerEx& ChunkCounterValue;

    //@}


    //! \name Categories: ChunkData
    //@{
    /*!
        \brief Exposure time used to acquire the image - Applies to: daA2448-70uc

    
        Visibility: Expert

    */
    Pylon::IFloatEx& ChunkExposureTime;

    //@}


    //! \name Categories: ChunkData
    //@{
    /*!
        \brief Unique identifier of the current frame - Applies to: daA2448-70uc

        Unique identifier of the current frame. The frame ID starts at 0 and keeps incrementing by 1 for each exposed image until the camera is powered off. The maximum value is 2^48.
    
        Visibility: Expert

    */
    Pylon::IIntegerEx& ChunkFrameID;

    //@}


    //! \name Categories: ChunkData
    //@{
    /*!
        \brief Gain used during image acquisition - Applies to: daA2448-70uc

    
        Visibility: Expert

        Selected by: ChunkGainSelector

    */
    Pylon::IFloatEx& ChunkGain;

    //@}


    //! \name Categories: ChunkData
    //@{
    /*!
        \brief Bit field that indicates the status of all of the camera's input and output lines when the image was acquired - Applies to: daA2448-70uc

    
        Visibility: Expert

    */
    Pylon::IIntegerEx& ChunkLineStatusAll;

    //@}


    //! \name Categories: ChunkData
    //@{
    /*!
        \brief CRC checksum of the acquired image - Applies to: daA2448-70uc

        CRC checksum of the acquired image. The checksum is calculated using all of the image data and all of the appended chunks except for the checksum itself.
    
        Visibility: Expert

    */
    Pylon::IIntegerEx& ChunkPayloadCRC16;

    //@}


        private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
            BaslerCameraChunkDataParams(BaslerCameraChunkDataParams&);

            //! not implemented assignment operator
            BaslerCameraChunkDataParams& operator=(BaslerCameraChunkDataParams&);

        //! \endcond
    };

} // namespace Pylon
} // namespace BaslerCameraChunkDataParams_Params

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // BASLER_PYLON_BASLERCAMERACHUNKDATAPARAMS_H