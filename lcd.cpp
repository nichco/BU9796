#include "lcd.h"
#include <Wire.h>


LCD_BU9796::LCD_BU9796(void) {
  memset(this->_buffer, 0, 7); // creates a 7-byte memory _buffer of zeros
}

bool LCD_BU9796::begin() {
  Wire.begin();

  this->_write_cmd(0b00111100); // set the lowest power consumption
  this->_write_cmd(0b01001000); // turn the display on using 1/3 bias
  return true;
}


void LCD_BU9796::show(void) {
  _write(this->_buffer, 7);
}



void LCD_BU9796::fill(bool on) {
  for (int i = 0; i < 6; i++) {
    this->_buffer[i + 1] = on ? 0xFF : 0x00;
  }
  if (this->auto_write) this->show();
}


void LCD_BU9796::_write_cmd(uint8_t cmd) {
  _write(&cmd, 1); // write the address of the cmd variable
}


void LCD_BU9796::_write(const uint8_t *buffer, size_t len) {
  Wire.beginTransmission(LCD_ADDR);
  Wire.write(buffer, len);
  Wire.endTransmission(true);
}


void LCD_BU9796::_set_buffer(uint8_t pos, uint8_t value) {
  this->_buffer[pos + 1] = value;
}


uint8_t LCD_BU9796::_get_buffer(uint8_t pos) {
  return this->_buffer[pos + 1]; // necessary for colon
}


void LCD_LCD::print(char *s) {
  
  char val[4];
  for(int i = 0; i < strlen(s); i++) val[i] = toupper(s[i]);

  for(int i = 0; i < strlen(s); i++) {
    int b = 0;
    char c = val[i];

    switch (c) {
      case '0': b = 0b11010111; break;
      case '1': b = 0b00000110; break;
      case '2': b = 0b11100011; break;
      case '3': b = 0b10100111; break;
      case '4': b = 0b00110110; break;
      case '5': b = 0b10110101; break;
      case '6': b = 0b11110101; break;
      case '7': b = 0b00000111; break;
      case '8': b = 0b11110111; break;
      case '9': b = 0b00110111; break;
      default: b = 0b00000000; break; // blank space
    }
    
    this->_set_buffer(i, b);

    this->_set_buffer(3, this->_get_buffer(3) | 0b00001000); // turn on the colon
  }

  if (this->auto_write) {
    this->show();
  }
}






