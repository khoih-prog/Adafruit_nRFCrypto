/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Ha Thach (tinyusb.org) for Adafruit Industries
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "Adafruit_nRFCrypto.h"

//--------------------------------------------------------------------+
// MACRO TYPEDEF CONSTANT ENUM DECLARATION
//--------------------------------------------------------------------+


//------------- IMPLEMENTATION -------------//
Adafruit_nRFCrypto_Random::Adafruit_nRFCrypto_Random(void)
{
}

bool Adafruit_nRFCrypto_Random::begin(void)
{
  CRYS_RND_WorkBuff_t* workbuf = (CRYS_RND_WorkBuff_t*) rtos_malloc(sizeof(CRYS_RND_WorkBuff_t));
  VERIFY(workbuf);

  nRFCrypto.enable();

  uint32_t err = CRYS_RndInit(&_state, workbuf);

  nRFCrypto.disable();

  rtos_free(workbuf);

  VERIFY_ERROR(err, false);
  return true;
}

void Adafruit_nRFCrypto_Random::end(void)
{
  nRFCrypto.enable();

  uint32_t err = CRYS_RND_UnInstantiation(&_state);

  nRFCrypto.disable();

  VERIFY_ERROR(err, );
}

bool Adafruit_nRFCrypto_Random::addAdditionalInput(uint8_t* input, uint16_t size)
{
  nRFCrypto.enable();

  uint32_t err = CRYS_RND_AddAdditionalInput(&_state, input, size);

  nRFCrypto.disable();

  VERIFY_ERROR(err, false);
  return true;
}

bool Adafruit_nRFCrypto_Random::reseed(void)
{
  CRYS_RND_WorkBuff_t* workbuf = (CRYS_RND_WorkBuff_t*) rtos_malloc(sizeof(CRYS_RND_WorkBuff_t));
  VERIFY(workbuf);

  nRFCrypto.enable();

  uint32_t err = CRYS_RND_Reseeding(&_state, workbuf);

  nRFCrypto.disable();

  rtos_free(workbuf);

  VERIFY_ERROR(err, false);
  return true;
}

bool Adafruit_nRFCrypto_Random::generate(uint8_t* buf, uint16_t bufsize)
{
  nRFCrypto.enable();

  uint32_t err = CRYS_RND_GenerateVector(&_state, bufsize, buf);

  nRFCrypto.disable();

  VERIFY_ERROR(err, false);
  return true;
}

bool Adafruit_nRFCrypto_Random::generateInRange(uint8_t* buf, uint32_t bitsize, uint8_t* max)
{
  nRFCrypto.enable();

  uint32_t err = CRYS_RND_GenerateVectorInRange(&_state, CRYS_RND_GenerateVector, bitsize, max, buf);

  nRFCrypto.disable();

  VERIFY_ERROR(err, false);
  return true;
}
