#ifndef CLIENTSERVERPROTOCOL_H
#define CLIENTSERVERPROTOCOL_H

enum clientDataTypes{ GET_IMAGE          = 0x00,
                      GET_FULL_XML       = 0x01,
                      SET_PARAMETER      = 0x20,
                      STOP_ALL_STREAMS   = 0x30,
                      REQUEST_LOGIN_USER = 0x40,
                      RETURN_USER        = 0x41,
                      IMAGE_DATA         = 0x50,
                      XML_FULL_CLIENT    = 0x60
                    };

enum imageTypes{ JPEG  = 0x00,
                 RAW   = 0x01,
                 DEPTH = 0x02
               };

enum userRights{ VIEWER = 0x00,
                 ADMIN  = 0x01
               };

// GET_IMAGE
// <clientDataType> <imageType> <camera (0x01->0x07)> <stream ( true | false = 0x00 | 0x01 )>


#endif // CLIENTSERVERPROTOCOL_H
