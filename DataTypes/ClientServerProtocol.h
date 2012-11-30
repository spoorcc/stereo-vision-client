#ifndef CLIENTSERVERPROTOCOL_H
#define CLIENTSERVERPROTOCOL_H

#define DEFAULT_SERVER_IP   "127.0.0.1"
#define DEFAULT_SERVER_PORT 49679

#define DATAGRAMSIZE 500

namespace clientServerProtocol
{
    enum clientDataTypes{ GET_IMAGE          = 0x00,
                          GET_FULL_XML       = 0x01,                          
                          UNFORMATTED_COMMAND = 0x02,

                          SET_PARAMETER      = 0x20,

                          STOP_ALL_STREAMS   = 0x30,

                          REQUEST_LOGIN_USER = 0x40,                          
                          RETURN_USER        = 0x41,

                          IMAGE_DATA         = 0x50,

                          XML_FULL_CLIENT    = 0x60
                        };


    enum userRights{ VIEWER = 0x00,
                     ADMIN  = 0x01
                   };

    enum imageTypes{ JPEG  = 0x00,
                     RAW   = 0x01,
                     DEPTH = 0x02
                   };

    enum streamID{ TEST_STREAM = 0x00,
                   CAMERA_1 = 0x01,
                   CAMERA_2 = 0x02,
                   CAMERA_3 = 0x03,
                   CAMERA_4 = 0x04,
                   CAMERA_5 = 0x05,
                   CAMERA_6 = 0x06,
                   CAMERA_7 = 0x07,
                   CAMERA_8 = 0x08
                  };

    //---------------------------------------------------------------
    //Datatype - GET_IMAGE

    namespace getImage{

        enum get_image_bytes{ IMAGETYPE = 0x01,
                              STREAMID  = 0x02,
                              STREAM    = 0x03
                             };

        // GET IMAGE - stream
        enum stream{ SINGLE_SHOT = 0x00,
                     CONTINOUS  = 0x01
                   };
    }

    //---------------------------------------------------------------
    //Datatype - GET_FULL_XML


    //---------------------------------------------------------------
    //Datatype - SET_PARAMETER

    namespace setParameter{

        enum set_parameter_bytes{
                                    STRINGLENGTH_MSB = 0x01,
                                    STRINGLENGTH_LSB = 0x02,

                                    FIRST_DATA_BYTE = 0x03,
                                    LAST_DATA_BYTE = 0x01F3
                                 };
        // SET_PARAMETER - Data_byte
        enum stringlength{
                            MAXSTRINGLENGTH = 0x01F1
                        };
    }

    //---------------------------------------------------------------
    //Datatype - IMAGE DATA

    namespace imageData{

        enum image_data_bytes{ DATATYPE = 0x00,
                               IMAGETYPE = 0x01,
                               STREAMID = 0x02,
                               FRAMEID = 0x03,
                               SLICEINDEX_MSB = 0x04,
                               SLICEINDEX_LSB = 0x05,
                               TOTALSLICES_MSB =0x06,
                               TOTALSLICES_LSB =0x07,
                               SLICELENGTH_MSB = 0x08,
                               SLICELENGTH_LSB = 0x09
                             };

        //IMAGE DATA - Image type
        //Uses clientServerProtocol::imageTypes

        //IMAGE DATA - Stream ID
        //Uses clientServerProtocol::streamID

        //IMAGE DATA - Frame
        enum frameID{ SINGLE_SHOT = 0x00,
                      FIRST_FRAME = 0x01,
                      LAST_FRAME = 0xFF
                    };

        //IMAGE DATA - SliceIndex

        //IMAGE DATA - TotalSlices

        //IMAGE DATA - SliceLength
        enum sliceLength{ MAX_SLICE_LENGTH = 0x01EA
                        };

        //IMAGE DATA - Data bytes
    }


}
#endif // CLIENTSERVERPROTOCOL_H
