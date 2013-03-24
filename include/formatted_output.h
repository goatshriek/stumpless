#ifndef STUMPLESS_FORMATTED_OUTPUT_H
#define STUMPLESS_FORMATTED_OUTPUT_H

#include <types.h>

StumplessStatusCode
StumplessAppendFormattedOutputs( StumplessFormattedOutput *,
                                 StumplessFormattedOutput * );

StumplessStatusCode
StumplessAppendStringToFormattedOutput( StumplessFormattedOutput *, char * );

StumplessStatusCode
StumplessAppendUnsignedIntToFormattedOutput( StumplessFormattedOutput *,
                                             unsigned );

#endif
