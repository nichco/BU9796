#ifndef lcd_h
#define lcd_h

#include <Arduino.h>
#include <Wire.h>

#define LCD_ADDR 0x3e


class LCD_BU9796 {
public:
  LCD_BU9796(void);
  bool begin(void);
  void show(void);
  void fill(bool on);

  bool auto_write = true;

protected:
  void _write(const uint8_t *buffer, size_t len);
  void _write_cmd(uint8_t cmd);
  void _set_buffer(uint8_t pos, uint8_t value);
  uint8_t _get_buffer(uint8_t pos);
  uint8_t _buffer[7];
};

class LCD_LCD : public LCD_BU9796 {
public:
  LCD_LCD(void) {};
  void print(char *s);
protected:
  void _update_byte_0();
};

#endif