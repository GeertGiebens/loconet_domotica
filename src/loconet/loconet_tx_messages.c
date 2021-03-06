/**
 * @file loconet_tx_messages.c
 * @brief Functions to send Loconet messages
 *
 * \copyright Copyright 2017 /Dev. All rights reserved.
 * \license This project is released under MIT license.
 *
 * @author Ferdi van der Werf <ferdi@slashdev.nl>
 * @author Jan Martijn van der Werf <janmartijn@slashdev.nl>
 */

#include "loconet_tx_messages.h"

// 2 byte messages
void loconet_tx_busy(void)
{
  loconet_tx_queue_2(0x81, 1);
}

void loconet_tx_gpoff(void)
{
  loconet_tx_queue_2(0x82, 5);
}

void loconet_tx_gpon(void)
{
  loconet_tx_queue_2(0x83, 5);
}

void loconet_tx_idle(void)
{
  loconet_tx_queue_2(0x85, 1);
}

// 4 byte messages
void loconet_tx_sq_req(uint16_t address, bool dir, bool state)
{
  uint8_t byte1 = address & 0x7F;
  uint8_t byte2 = ((address >> 7) & 0x0F)
    | (state << 5)
    | (dir << 6);

  loconet_tx_queue_4(0xB0, 5, byte1, byte2);
}

void loconet_tx_sw_rep(uint16_t address, bool state)
{
  uint8_t byte1 = address & 0x7F;
  uint8_t byte2 = ((address >> 7) & 0x0F)
    | (state << 5)
    | (0 << 6)
    | 0x40;

  loconet_tx_queue_4(0xB1, 5, byte1, byte2);
}

// For 4K sensor address space we need to 'code' the address
void loconet_tx_input_rep(uint16_t address, bool state)
{
  // I is used as odd/even bit
  uint8_t odd = address & 0x01;

  // Subtract one and then bit shift right to divide by two
  address--;
  address >>= 1;

  // Set low bits of the address
  uint8_t byte1 = address & 0x7F;
  // Set high bits of the address, add odd/even bit and add state
  uint8_t byte2 = ((address >> 7) & 0x0F)
    | (((odd + 1) % 2) << 5)
    | (state << 4)
    | 0x40;

  // Queue a 0xB2
  loconet_tx_queue_4(0xB2, 5, byte1, byte2);
}

void loconet_tx_long_ack(uint8_t lopc, uint8_t ack1)
{
  loconet_tx_queue_4(0xB4, 1, lopc & 0x7F, ack1 & 0x7F);
}

// ----------------------------------------------------------------------------
void loconet_tx_fast_clock(uint8_t clk_rate, uint8_t frac_minsl, uint8_t frac_minsh, uint8_t minutes, uint8_t hours, uint8_t days, uint8_t id1, uint8_t id2)
{
  uint8_t length = 11;
  uint8_t data[length];

  data[0] = 0x7B; // address of the clock
  data[1] = clk_rate;
  data[2] = frac_minsl;
  data[3] = frac_minsh;

  data[4] = minutes + (128-60);
  data[5] = 0x06; // trk
  data[6] = hours + (128-24);
  data[7] = days;
  data[8] = 0x01; // it is a valid clock setting!
  data[9] = id1;
  data[10] = id2;

  loconet_tx_queue_n(0xEF, 10, data, length);
}
