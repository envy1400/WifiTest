/********************
 * Author: Nick Vinyard
 *
 */

#ifndef APP_H
#define APP_H

typedef enum{
    APP_INIT,
    APP_SEND_OK,
    APP_GET_RESPONSE,
    APP_IDLE,
    APP_CONNECT,
    APP_SET_MODE,
} eAppStates;

#endif  // #define APP_H