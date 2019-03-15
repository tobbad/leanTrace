/*
 * ltrace.c
 *
 *  Created on: 24.02.2019
 *      Author: badi
 */
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

