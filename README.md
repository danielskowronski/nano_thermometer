# nano_thermometer
nano_thermometer is arduino nano based simple thermometer which displays current temperature and plot (13..36°C) from approx last minute

may become part of [zegar-beta](http://github.com/danielskowronski/zegar-beta)

## hardware
- arduino nano
- LM35 thermometer
- 128x64 monochromatic OLED with SSD1306 driver (similiar but not same as adafruit's one)

## SSD1306 library - IIC_without_ACK 
you can find orginal author info in comments (in Chinese) - I added only PROGMEM macro so huge font tables are stored in flash instead of SRAM

## ideas - todo
- better (quicker) plot redraw
- plot scaling
- sampling time scaling