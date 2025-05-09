#include <stdlib.h>

#include "err.h"
#include "jerryscript.h"
#include "jerryxx.h"
#include "lcd_magic_strings.h"
#include "lcd.h"

/**
 * LCD() constructor
 */
JERRYXX_FUN(lcd_ctor_fn) {
  return jerry_create_undefined();
}

/**
 * LCD.prototype.fillRect(x, y, width, height, color) function
 */
JERRYXX_FUN(lcd_fill_rect_fn) {
  JERRYXX_CHECK_ARG_NUMBER(0, "x");
  JERRYXX_CHECK_ARG_NUMBER(1, "y");
  JERRYXX_CHECK_ARG_NUMBER(2, "width");
  JERRYXX_CHECK_ARG_NUMBER(3, "height");
  JERRYXX_CHECK_ARG_NUMBER(4, "color");

  // uint16_t x = (int16_t)JERRYXX_GET_ARG_NUMBER(0);
  // uint16_t y = (int16_t)JERRYXX_GET_ARG_NUMBER(1);
  // uint16_t width = (int16_t)JERRYXX_GET_ARG_NUMBER(2);
  // uint16_t height = (int16_t)JERRYXX_GET_ARG_NUMBER(3);
  // uint16_t color = (uint16_t)JERRYXX_GET_ARG_NUMBER(4);

  // pc_display_fill_rect(x, y, width, height, color);
  pc_display_fill_rect(20, 20, 50, 50, PC_COLOR_WHITE);
  return jerry_create_undefined();
}

/**
 * Initialize 'lcd' module
 */
jerry_value_t module_lcd_init() {
  jerry_value_t lcd_ctor = jerry_create_external_function(lcd_ctor_fn);
  jerry_value_t lcd_prototype = jerry_create_object();
  jerryxx_set_property(lcd_ctor, "prototype", lcd_prototype);

  jerryxx_set_property_function(lcd_prototype, "fillRect", lcd_fill_rect_fn);
  
  jerry_release_value(lcd_prototype);

  jerry_value_t exports = jerry_create_object();
  
  jerryxx_set_property(exports, "LCD", lcd_ctor);
  jerry_release_value(lcd_ctor);

  return exports;
}
