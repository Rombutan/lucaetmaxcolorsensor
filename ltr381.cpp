#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "pico/stdlib.h"
#include "hardware/i2c.h"


static const uint8_t REG_DEVID = 0x53;

class ltr3810 {
  public:
    ltr3810(){
      Write8(0x04, 0x40);
      Write8(0x00, 0x06);
    }

    uint32_t red(){
      uint32_t Rnorm = Read8(0x11) << 8;
      uint32_t Rmsb = Read8(0x12) << 16;
      uint32_t Rlsb = Read8(0x10);
      return Rmsb | Rnorm | Rlsb;
      //return (Rmsb << 16) + (Rnorm << 8) + Rlsb;
    }
    uint32_t blue(){
      uint32_t Bnorm = Read8(0x14) << 8;
      uint32_t Bmsb = Read8(0x15) << 16;
      uint32_t Blsb = Read8(0x13);
      return Bmsb | Bnorm | Blsb;
      //return (Bmsb << 16) + (Bnorm << 8) + Blsb;
    }
    uint32_t green(){
      uint32_t Gnorm = Read8(0x0E) << 8;
      uint32_t Gmsb = Read8(0x0F) << 16;
      uint32_t Glsb = Read8(0x0D);
      return Gmsb | Gnorm | Glsb;
      //return (Gmsb << 16) + (Gnorm << 8) + Glsb;
      return Gmsb;
    }
  private:
    int Write8(uint8_t reg, uint8_t msg) {
      uint8_t buf = msg;
      reg_write( REG_DEVID, reg, &buf, 1);
      return reg_write( REG_DEVID, reg, &buf, 1);
    }

    uint8_t Read8(const uint8_t reg){
      uint8_t buf;
      reg_read( REG_DEVID, reg, &buf, 1);
      return buf;
    }

    int reg_write(
                const uint addr,
                const uint8_t reg,
                uint8_t *buf,
                const uint8_t nbytes) {

        int num_bytes_read = 0;
        uint8_t msg[nbytes + 1];

        // Check to make sure caller is sending 1 or more bytes
        if (nbytes < 1) {
          return 0;
        }

        // Append register address to front of data packet
        msg[0] = reg;
        for (int i = 0; i < nbytes; i++) {
          msg[i + 1] = buf[i];
        }
        return i2c_write_blocking(i2c0, addr, msg, (nbytes + 1), false);

      }

      int reg_read(
                  const uint addr,
                  const uint8_t reg,
                  uint8_t *buf,
                  const uint8_t nbytes) {

      int num_bytes_read = 0;

      // Check to make sure caller is asking for 1 or more bytes
      if (nbytes < 1) {
          return 0;
      }

      // Read data from register(s) over I2C
      i2c_write_blocking(i2c0, addr, &reg, 1, true);
      num_bytes_read = i2c_read_blocking(i2c0, addr, buf, nbytes, false);

      return num_bytes_read;
    }
};

class ltr3811 {
  public:
    ltr3811(){
      Write8(0x04, 0x40);
      Write8(0x00, 0x06);
    }

    uint32_t red(){
      uint32_t Rnorm = Read8(0x11) << 8;
      uint32_t Rmsb = Read8(0x12) << 16;
      uint32_t Rlsb = Read8(0x10);
      return Rmsb | Rnorm | Rlsb;
      //return (Rmsb << 16) + (Rnorm << 8) + Rlsb;
    }
    uint32_t blue(){
      uint32_t Bnorm = Read8(0x14) << 8;
      uint32_t Bmsb = Read8(0x15) << 16;
      uint32_t Blsb = Read8(0x13);
      return Bmsb | Bnorm | Blsb;
      //return (Bmsb << 16) + (Bnorm << 8) + Blsb;
    }
    uint32_t green(){
      uint32_t Gnorm = Read8(0x0E) << 8;
      uint32_t Gmsb = Read8(0x0F) << 16;
      uint32_t Glsb = Read8(0x0D);
      return Gmsb | Gnorm | Glsb;
      //return (Gmsb << 16) + (Gnorm << 8) + Glsb;
      return Gmsb;
    }
  private:
    int Write8(uint8_t reg, uint8_t msg) {
      uint8_t buf = msg;
      reg_write( REG_DEVID, reg, &buf, 1);
      return reg_write( REG_DEVID, reg, &buf, 1);
    }

    uint8_t Read8(const uint8_t reg){
      uint8_t buf;
      reg_read( REG_DEVID, reg, &buf, 1);
      return buf;
    }

    int reg_write(
                const uint addr,
                const uint8_t reg,
                uint8_t *buf,
                const uint8_t nbytes) {

        int num_bytes_read = 0;
        uint8_t msg[nbytes + 1];

        // Check to make sure caller is sending 1 or more bytes
        if (nbytes < 1) {
          return 0;
        }

        // Append register address to front of data packet
        msg[0] = reg;
        for (int i = 0; i < nbytes; i++) {
          msg[i + 1] = buf[i];
        }
        return i2c_write_blocking(i2c1, addr, msg, (nbytes + 1), false);

      }

      int reg_read(
                  const uint addr,
                  const uint8_t reg,
                  uint8_t *buf,
                  const uint8_t nbytes) {

      int num_bytes_read = 0;

      // Check to make sure caller is asking for 1 or more bytes
      if (nbytes < 1) {
          return 0;
      }

      // Read data from register(s) over I2C
      i2c_write_blocking(i2c1, addr, &reg, 1, true);
      num_bytes_read = i2c_read_blocking(i2c1, addr, buf, nbytes, false);

      return num_bytes_read;
    }
};