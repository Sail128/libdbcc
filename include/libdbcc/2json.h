#ifndef _2JSON_H
#define _2JSON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dbc.h"

int dbc2json(dbc_t *dbc, FILE *output, bool use_time_stamps);

#ifdef __cplusplus
}
#endif
#endif
