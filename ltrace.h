/*
 * ltrace.h
 *
 *  Created on: 24.02.2019
 *      Author: badi
 */

#ifndef LIB_LTRACE_LTRACE_H_
#define LIB_LTRACE_LTRACE_H_

#include <stdint.h>
#include "lt_conf.h"
#ifdef __cplusplus
extern "C" {
#endif
/*
 * From http://lolengine.net/blog/2011/12/20/cpp-constant-string-hash
 */

#define H1(s,i,x)   (x*65599u+(uint8_t)s[(i)<strlen(s)?strlen(s)-1-(i):strlen(s)])
#define H4(s,i,x)   H1(s,i,H1(s,i+1,H1(s,i+2,H1(s,i+3,x))))
#define H16(s,i,x)  H4(s,i,H4(s,i+4,H4(s,i+8,H4(s,i+12,x))))
#define H64(s,i,x)  H16(s,i,H16(s,i+16,H16(s,i+32,H16(s,i+48,x))))
#define H256(s,i,x) H64(s,i,H64(s,i+64,H64(s,i+128,H64(s,i+192,x))))

#define HASH32(s)    ((uint32_t)(H256(s,0,0)^(H256(s,0,0)>>16)))
#define HASH16(s)    ((uint16_t)((uint32_t)(H256(s,0,0)^(H256(s,0,0)>>16))))
/*
 * Needed typedefs
 */
typedef enum {
    LOG_ALL,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERR,
    LOG_FATAL,
    LOG_OFF,
} log_t;

typedef enum {
    LT_ERROR = -1,  //! General Error */
    LT_OK,          //! General "Everything is OK" return message
} ltrace_msg_e;

#define COMP_TYPE LT_UNKNOWN -1

typedef struct lt_init_t_
{
    /**
     * Write buffer to logging device.
     * \param buf Buffer keeping the data to be send
     * \param cnt Count of bytes to be transfered on input, returns the count of bytes really transfered.
     *
     * \return message code as described in the enum
     */
    ltrace_msg_e (*write)(uint8_t *buf, uint16_t *cnt);
} lt_init_t;

#define PRINTF(fmt, ...) lt_log(HASH16(__FILE__), __LINE__, LOG_DEBUG, LT_UNKNOWN, HASH32(fmt), ##__VA_ARGS__)


ltrace_msg_e lt_init(lt_init_t *init);
ltrace_msg_e lt_log(uint16_t filename_hash, int line_nr, log_t log_level, uint16_t comp_id, uint32_t message_hash, ...);

#ifdef __cplusplus
}
#endif

#endif /* LIB_LTRACE_LTRACE_H_ */
