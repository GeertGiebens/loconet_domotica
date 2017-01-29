/**
 * @file loconet_cv.h
 * @brief Process Loconet CV messages
 *
 * \copyright Copyright 2017 /Dev. All rights reserved.
 * \license This project is released under MIT license.
 *
 * @author Ferdi van der Werf <ferdi@slashdev.nl>
 * @author Jan Martijn van der Werf <janmartijn@slashdev.nl>
 */

#ifndef _LOCONET_LOCONET_CV_H_
#define _LOCONET_LOCONET_CV_H_

#include <stdint.h>

#define LOCONET_CV_SRC_MASTER       0x00
#define LOCONET_CV_SRC_KPU          0x01 // KPU is, e.g., an IntelliBox
#define LOCONET_CV_SRC_UNDEFINED    0x02 // Unknown source
#define LOCONET_CV_SRC_TWINBOX_FRED 0x03
#define LOCONET_CV_SRC_IBSWITCH     0x04
#define LOCONET_CV_SRC_MODULE       0x05

typedef struct {
  uint8_t source;
  __attribute__((packed)) uint16_t destination;
  uint8_t request_id;
  uint8_t most_significant_bits;
  __attribute__((packed)) uint16_t device_class;
  __attribute__((packed)) uint16_t lncv_number;
  __attribute__((packed)) uint16_t lncv_value;
  uint8_t flags;
} LOCONET_CV_MSG_Type;

//-----------------------------------------------------------------------------
extern void loconet_cv_process(LOCONET_CV_MSG_Type*, uint8_t);

#endif // _LOCONET_LOCONET_CV_H_
