#include "i2c_device.h"

#include <Arduino.h>

namespace emakefun {

namespace {
template <typename T>
T SwapEndian(T value) {
  T result = 0;
  unsigned char* src_ptr = reinterpret_cast<unsigned char*>(&value);
  unsigned char* dest_ptr = reinterpret_cast<unsigned char*>(&result);

  for (size_t i = 0; i < sizeof(T); ++i) {
    dest_ptr[i] = src_ptr[sizeof(T) - 1 - i];
  }

  return result;
}
}  // namespace

I2cDevice::I2cDevice(const uint8_t i2c_address) : i2c_address_(i2c_address) {}

bool I2cDevice::Initialize(TwoWire* const wire) {
  if (wire == nullptr) {
    return false;
  }
  wire_ = wire;
  wire_->begin();
  return true;
}

bool I2cDevice::Probe() {
  wire_->beginTransmission(i2c_address_);
  const auto ret = wire_->endTransmission();
  if (ret != 0) {
    Serial.print("Failed to probe i2c device with address 0x");
    Serial.print(i2c_address_, HEX);
    Serial.print(". error code: ");
    Serial.println(ret);
    return false;
  }

  return true;
}

size_t I2cDevice::WriteByte(const uint8_t data) {
  wire_->beginTransmission(i2c_address_);
  wire_->write(data);
  return 0 == wire_->endTransmission() ? 1 : 0;
}

size_t I2cDevice::WriteByte(const uint8_t address, const uint8_t data) {
  wire_->beginTransmission(i2c_address_);
  wire_->write(address);
  wire_->write(data);
  return 0 == wire_->endTransmission() ? 1 : 0;
}

size_t I2cDevice::WriteBytes(const void* const data, const size_t length) {
  wire_->beginTransmission(i2c_address_);
  size_t ret = wire_->write(reinterpret_cast<const uint8_t*>(data), length);
  return 0 == wire_->endTransmission() ? ret : 0;
}

size_t I2cDevice::WriteBytes(const uint8_t address, const void* data, const size_t length) {
  wire_->beginTransmission(i2c_address_);
  wire_->write(address);
  size_t ret = wire_->write(reinterpret_cast<const uint8_t*>(data), length);
  return 0 == wire_->endTransmission() ? ret : 0;
}

size_t I2cDevice::WriteInt8(const uint8_t address, const int8_t data) { return WriteByte(address, static_cast<uint8_t>(data)); }

size_t I2cDevice::WriteUint8(const uint8_t address, const uint8_t data) { return WriteByte(address, data); }

size_t I2cDevice::WriteInt16LE(const uint8_t address, const int16_t data) { return WriteBytes(address, &data, sizeof(data)); }

size_t I2cDevice::WriteUint16LE(const uint8_t address, const uint16_t data) { return WriteBytes(address, &data, sizeof(data)); }

size_t I2cDevice::WriteInt32LE(const uint8_t address, const int32_t data) { return WriteBytes(address, &data, sizeof(data)); }

size_t I2cDevice::WriteUint32LE(const uint8_t address, const uint32_t data) { return WriteBytes(address, &data, sizeof(data)); }

size_t I2cDevice::WriteInt64LE(const uint8_t address, const int64_t data) { return WriteBytes(address, &data, sizeof(data)); }

size_t I2cDevice::WriteUint64LE(const uint8_t address, const uint64_t data) { return WriteBytes(address, &data, sizeof(data)); }

size_t I2cDevice::WriteInt16BE(const uint8_t address, const int16_t data) { return WriteInt16LE(address, SwapEndian(data)); }

size_t I2cDevice::WriteUint16BE(const uint8_t address, const uint16_t data) { return WriteUint16LE(address, SwapEndian(data)); }

size_t I2cDevice::WriteInt32BE(const uint8_t address, const int32_t data) { return WriteInt32LE(address, SwapEndian(data)); }

size_t I2cDevice::WriteUint32BE(const uint8_t address, const uint32_t data) { return WriteUint32LE(address, SwapEndian(data)); }

size_t I2cDevice::WriteInt64BE(const uint8_t address, const int64_t data) { return WriteInt64LE(address, SwapEndian(data)); }

size_t I2cDevice::WriteUint64BE(const uint8_t address, const uint64_t data) { return WriteUint64LE(address, SwapEndian(data)); }

uint8_t I2cDevice::ReadByte() {
  wire_->requestFrom(i2c_address_, static_cast<uint8_t>(1));
  return wire_->available() ? wire_->read() : 0;
}

uint8_t I2cDevice::ReadByte(const uint8_t address) {
  wire_->beginTransmission(i2c_address_);
  wire_->write(address);
  if (0 != wire_->endTransmission()) {
    return 0;
  }

  wire_->requestFrom(i2c_address_, static_cast<uint8_t>(1));
  return wire_->available() ? wire_->read() : 0;
}

size_t I2cDevice::ReadBytes(void* const buffer, const size_t length) {
  wire_->requestFrom(i2c_address_, length);
  if (wire_->available()) {
    return wire_->readBytes(reinterpret_cast<uint8_t*>(buffer), length);
  }

  return 0;
}

size_t I2cDevice::ReadBytes(const uint8_t address, void* const buffer, const size_t length) {
  wire_->beginTransmission(i2c_address_);
  wire_->write(address);
  if (0 != wire_->endTransmission()) {
    return 0;
  }

  wire_->requestFrom(i2c_address_, length);
  if (wire_->available()) {
    return wire_->readBytes(reinterpret_cast<uint8_t*>(buffer), length);
  }

  return 0;
}

int8_t I2cDevice::ReadInt8(const uint8_t address) { return static_cast<int8_t>(ReadByte(address)); }

uint8_t I2cDevice::ReadUint8(const uint8_t address) { return ReadByte(address); }

int16_t I2cDevice::ReadInt16LE(const uint8_t address) {
  int16_t data = 0;
  ReadBytes(address, &data, sizeof(data));
  return data;
}

uint16_t I2cDevice::ReadUint16LE(const uint8_t address) {
  uint16_t data = 0;
  ReadBytes(address, &data, sizeof(data));
  return data;
}

int32_t I2cDevice::ReadInt32LE(const uint8_t address) {
  int32_t data = 0;
  ReadBytes(address, &data, sizeof(data));
  return data;
}

uint32_t I2cDevice::ReadUint32LE(const uint8_t address) {
  uint32_t data = 0;
  ReadBytes(address, &data, sizeof(data));
  return data;
}

int64_t I2cDevice::ReadInt64LE(const uint8_t address) {
  int64_t data = 0;
  ReadBytes(address, &data, sizeof(data));
  return data;
}

uint64_t I2cDevice::ReadUint64LE(const uint8_t address) {
  uint64_t data = 0;
  ReadBytes(address, &data, sizeof(data));
  return data;
}

int16_t I2cDevice::ReadInt16BE(const uint8_t address) { return SwapEndian(ReadInt16LE(address)); }

uint16_t I2cDevice::ReadUint16BE(const uint8_t address) { return SwapEndian(ReadUint16LE(address)); }

int32_t I2cDevice::ReadInt32BE(const uint8_t address) { return SwapEndian(ReadInt32LE(address)); }

uint32_t I2cDevice::ReadUint32BE(const uint8_t address) { return SwapEndian(ReadUint32LE(address)); }

int64_t I2cDevice::ReadInt64BE(const uint8_t address) { return SwapEndian(ReadInt64LE(address)); }

uint64_t I2cDevice::ReadUint64BE(const uint8_t address) { return SwapEndian(ReadUint64LE(address)); }

}  // namespace emakefun