#pragma once

#include <Wire.h>
#include <inttypes.h>
#include <stddef.h>

namespace emakefun {
class I2cDevice {
 public:
  explicit I2cDevice(const uint8_t i2c_address);

  bool Initialize(TwoWire* const wire = &Wire);
  inline uint8_t I2cAddress() const { return i2c_address_; }
  bool Probe();

  size_t WriteByte(const uint8_t data);
  size_t WriteByte(const uint8_t address, const uint8_t data);
  size_t WriteBytes(const void* const data, const size_t length);
  size_t WriteBytes(const uint8_t address, const void* const data, const size_t length);
  size_t WriteInt8(const uint8_t address, const int8_t data);
  size_t WriteUint8(const uint8_t address, const uint8_t data);
  size_t WriteInt16LE(const uint8_t address, const int16_t data);
  size_t WriteUint16LE(const uint8_t address, const uint16_t data);
  size_t WriteInt32LE(const uint8_t address, const int32_t data);
  size_t WriteUint32LE(const uint8_t address, const uint32_t data);
  size_t WriteInt64LE(const uint8_t address, const int64_t data);
  size_t WriteUint64LE(const uint8_t address, const uint64_t data);
  size_t WriteInt16BE(const uint8_t address, const int16_t data);
  size_t WriteUint16BE(const uint8_t address, const uint16_t data);
  size_t WriteInt32BE(const uint8_t address, const int32_t data);
  size_t WriteUint32BE(const uint8_t address, const uint32_t data);
  size_t WriteInt64BE(const uint8_t address, const int64_t data);
  size_t WriteUint64BE(const uint8_t address, const uint64_t data);

  uint8_t ReadByte();
  uint8_t ReadByte(const uint8_t address);
  size_t ReadBytes(void* const buffer, const size_t length);
  size_t ReadBytes(const uint8_t address, void* const buffer, const size_t length);
  int8_t ReadInt8(const uint8_t address);
  uint8_t ReadUint8(const uint8_t address);
  int16_t ReadInt16LE(const uint8_t address);
  uint16_t ReadUint16LE(const uint8_t address);
  int32_t ReadInt32LE(const uint8_t address);
  uint32_t ReadUint32LE(const uint8_t address);
  int64_t ReadInt64LE(const uint8_t address);
  uint64_t ReadUint64LE(const uint8_t address);
  int16_t ReadInt16BE(const uint8_t address);
  uint16_t ReadUint16BE(const uint8_t address);
  int32_t ReadInt32BE(const uint8_t address);
  uint32_t ReadUint32BE(const uint8_t address);
  int64_t ReadInt64BE(const uint8_t address);
  uint64_t ReadUint64BE(const uint8_t address);

 private:
  TwoWire* wire_ = nullptr;
  const uint8_t i2c_address_ = 0x00;
};
}  // namespace emakefun