/*
 * ltrace.c
 *
 *  Created on: 24.02.2019
 *      Author: badi
 */
#include <stdint.h>
#include <string.h>
#include "ltrace.h"

/*
 * Local typedef and #defines
 */
typedef struct ltrace_t_
{
    lt_init_t init;
} ltrace_t;

/*
 * Local reference to log infrastructure
 */
static ltrace_t ltrace;

/**
 * \brief Initilize Lean tracer
 *
 * \param init Pointer to structure with elements to work with
 *
 * \return Message on success/fail of call
 */
ltrace_msg_e lt_init(lt_init_t *init)
{
    ltrace_msg_e res = LT_ERROR;

    if ((NULL != init) && (NULL != init->write))
    {
        ltrace.init = *init;
        res = LT_OK;
    }
    return res;
}

/**
 * \brief Format and send message
 *
 * \param
 */
ltrace_msg_e lt_log(uint16_t filename_hash, int line_nr, log_t log_level, uint16_t comp_id, uint32_t message_hash, ...)
{
    ltrace_msg_e msg = LT_OK;

    return msg;
}

