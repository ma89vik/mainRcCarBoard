/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.9.3 at Wed Apr 10 11:45:02 2019. */

#ifndef PB_STATE_PB_H_INCLUDED
#define PB_STATE_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _CarState {
    CarState_IDLE = 1,
    CarState_ARM = 2,
    CarState_AUTO = 3,
    CarState_MANUAL = 4
} CarState;
#define _CarState_MIN CarState_IDLE
#define _CarState_MAX CarState_MANUAL
#define _CarState_ARRAYSIZE ((CarState)(CarState_MANUAL+1))

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif