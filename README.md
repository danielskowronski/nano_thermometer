# nano_thermometer
nano_thermometer is arduino nano based simple thermometer which displays current temperature, delta and plot (13..36°C) from approx last minute

may become part of [zegar-beta](http://github.com/danielskowronski/zegar-beta)

## hardware
- arduino nano
- LM35 thermometer
- 128x64 monochromatic OLED with SSD1306 driver (similiar but not same as adafruit's one)

## SSD1306 library - IIC_without_ACK 
you can find original author info in comments (in Chinese) - I added only PROGMEM macro so huge font tables are stored in flash instead of SRAM (currently there are fixes pending so I may rebuild it in future)

## ideas - todo
- plot scaling
- sampling time adjusting
- better delta calculation conditions 