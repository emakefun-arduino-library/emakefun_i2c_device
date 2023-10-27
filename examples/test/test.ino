#include "i2c_device.h"

#define CHECK(x) CHECK_WITH_LINE(x, __LINE__)

#define CHECK_WITH_LINE(x, line)     \
  do {                               \
    Serial.print(F("check line: ")); \
    Serial.print(line);              \
    Serial.print(", ");              \
    Serial.print(F(#x));             \
    Serial.print(": ");              \
    if ((x)) {                       \
      Serial.println(F("pass"));     \
    } else {                         \
      Serial.println(F("failed"));   \
    }                                \
  } while (0)

emakefun::I2cDevice g_i2c_dev(0x30);

void setup() {
  Serial.begin(115200);
  g_i2c_dev.Initialize();
}

void loop() {
  uint8_t test_address = 0x01;
  const int8_t int8_value = 0x11;
  const uint8_t uint8_value = 0x22;
  const int16_t int16_value = 0x1122;
  const uint16_t uint16_value = 0x1122;
  const int32_t int32_value = 0x11223344;
  const uint32_t uint32_value = 0x11223344;
  const int64_t int64_value = 0x1122334455667788;
  const uint64_t uint64_value = 0x1122334455667788;

  g_i2c_dev.WriteByte(test_address, uint8_value);
  CHECK(g_i2c_dev.ReadByte(test_address) == uint8_value);

  test_address++;
  g_i2c_dev.WriteInt8(test_address, int8_value);
  CHECK(g_i2c_dev.ReadByte(test_address) == int8_value);
  CHECK(g_i2c_dev.ReadInt8(test_address) == int8_value);

  g_i2c_dev.WriteUint8(test_address, uint8_value);
  CHECK(g_i2c_dev.ReadByte(test_address) == uint8_value);
  CHECK(g_i2c_dev.ReadUint8(test_address) == uint8_value);

  test_address++;
  g_i2c_dev.WriteInt16LE(test_address, int16_value);
  for (uint8_t i = 0; i < sizeof(int16_value); i++) {
    CHECK(g_i2c_dev.ReadByte(test_address + i) == reinterpret_cast<const uint8_t*>(&int16_value)[i]);
  }
  CHECK(g_i2c_dev.ReadInt16LE(test_address) == int16_value);

  test_address++;
  g_i2c_dev.WriteUint16LE(test_address, uint16_value);
  for (uint8_t i = 0; i < sizeof(uint16_value); i++) {
    CHECK(g_i2c_dev.ReadByte(test_address + i) == reinterpret_cast<const uint8_t*>(&uint16_value)[i]);
  }
  CHECK(g_i2c_dev.ReadUint16LE(test_address) == uint16_value);

  test_address++;
  g_i2c_dev.WriteInt32LE(test_address, int32_value);
  for (uint8_t i = 0; i < sizeof(int32_value); i++) {
    CHECK(g_i2c_dev.ReadByte(test_address + i) == reinterpret_cast<const uint8_t*>(&int32_value)[i]);
  }
  CHECK(g_i2c_dev.ReadInt32LE(test_address) == int32_value);

  test_address++;
  g_i2c_dev.WriteUint32LE(test_address, uint32_value);
  for (uint8_t i = 0; i < sizeof(uint32_value); i++) {
    CHECK(g_i2c_dev.ReadByte(test_address + i) == reinterpret_cast<const uint8_t*>(&uint32_value)[i]);
  }
  CHECK(g_i2c_dev.ReadUint32LE(test_address) == uint32_value);

  test_address++;
  g_i2c_dev.WriteInt64LE(test_address, int64_value);

  for (uint8_t i = 0; i < sizeof(int64_value); i++) {
    CHECK(g_i2c_dev.ReadByte(test_address + i) == reinterpret_cast<const uint8_t*>(&int64_value)[i]);
  }
  CHECK(g_i2c_dev.ReadInt64LE(test_address) == int64_value);

  test_address++;
  g_i2c_dev.WriteUint64LE(test_address, uint64_value);

  for (uint8_t i = 0; i < sizeof(uint64_value); i++) {
    CHECK(g_i2c_dev.ReadByte(test_address + i) == reinterpret_cast<const uint8_t*>(&uint64_value)[i]);
  }
  CHECK(g_i2c_dev.ReadUint64LE(test_address) == uint64_value);

  g_i2c_dev.WriteInt16BE(test_address, int16_value);
  for (uint8_t i = 0; i < sizeof(int16_value); i++) {
    CHECK(g_i2c_dev.ReadByte(test_address + i) == reinterpret_cast<const uint8_t*>(&int16_value)[sizeof(int16_value) - i - 1]);
  }
  CHECK(g_i2c_dev.ReadInt16BE(test_address) == int16_value);

  test_address++;
  g_i2c_dev.WriteUint16BE(test_address, uint16_value);
  for (uint8_t i = 0; i < sizeof(uint16_value); i++) {
    CHECK(g_i2c_dev.ReadByte(test_address + i) ==
          reinterpret_cast<const uint8_t*>(&uint16_value)[sizeof(uint16_value) - i - 1]);
  }
  CHECK(g_i2c_dev.ReadUint16BE(test_address) == uint16_value);

  g_i2c_dev.WriteInt32BE(test_address, int32_value);
  for (uint8_t i = 0; i < sizeof(int32_value); i++) {
    CHECK(g_i2c_dev.ReadByte(test_address + i) == reinterpret_cast<const uint8_t*>(&int32_value)[sizeof(int32_value) - i - 1]);
  }
  CHECK(g_i2c_dev.ReadInt32BE(test_address) == int32_value);

  test_address++;
  g_i2c_dev.WriteUint32BE(test_address, uint32_value);
  for (uint8_t i = 0; i < sizeof(uint32_value); i++) {
    CHECK(g_i2c_dev.ReadByte(test_address + i) ==
          reinterpret_cast<const uint8_t*>(&uint32_value)[sizeof(uint32_value) - i - 1]);
  }
  CHECK(g_i2c_dev.ReadUint32BE(test_address) == uint32_value);

  test_address++;
  g_i2c_dev.WriteInt64BE(test_address, int64_value);

  for (uint8_t i = 0; i < sizeof(int64_value); i++) {
    CHECK(g_i2c_dev.ReadByte(test_address + i) == reinterpret_cast<const uint8_t*>(&int64_value)[sizeof(int64_value) - i - 1]);
  }
  CHECK(g_i2c_dev.ReadInt64BE(test_address) == int64_value);

  test_address++;
  g_i2c_dev.WriteUint64BE(test_address, uint64_value);

  for (uint8_t i = 0; i < sizeof(uint64_value); i++) {
    CHECK(g_i2c_dev.ReadByte(test_address + i) ==
          reinterpret_cast<const uint8_t*>(&uint64_value)[sizeof(uint64_value) - i - 1]);
  }
  CHECK(g_i2c_dev.ReadUint64BE(test_address) == uint64_value);

  Serial.println(F("test done"));
  delay(2000);
}