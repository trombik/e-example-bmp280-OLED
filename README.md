# e-example-bmp280-OLED

An example `arduino` program to experiment I2C and OLED display.

MCU periodically polls BME280 sensor every one minute, displays the reading
on OLED, and prints to serial port. The default serial baud rate is 115200.
The upload port is `/dev/cuaU0`, which would be not the correct one in most
cases. Change `upload_port` in `[common]` section in `platformio.ini`.

Note that initial result will be shown after one minute from the boot.

## Requirements

* [platformio](http://docs.platformio.org/en/latest/)

### Additional requirements for FreeBSD

Some platformio packages have not been officially provided. You may build
them, or install packages from the links below.

* [toolchain-xtensa32](https://github.com/trombik/toolchain-xtensa32)
* [tool-mkspiffs](https://github.com/trombik/tool-mkspiffs)

## Building and uploading

Build the code by:

```
> pio run
```

Upload the code by:

```
> pio run -t upload -e lolin32
```

Replace `lolin32` with the board name specified in
[`platformio.ini`](platformio.ini).

## Example output

```
bmp280test.ino
BMP280 with OLED display
Initialing...
Found BME280 sensor! Success.
Initialized.
Temperature = 22.47'C
Humidity = 52.83%
Pressure = 1004.75hPa

Temperature = 22.68'C
Humidity = 53.36%
Pressure = 1004.79hPa

...
```

## Supported platforms

### ESP8266

* NodeMCU

No known issues.

### ESP32

* Lolin32 v.1.0.0

It is supposed to work when the following I2C issue in `arduino-esp32` is
fixed. No OLED output, but censor reading and serial port work.

[I2C ReWrite #839](https://github.com/espressif/arduino-esp32/issues/839)

## LICENSE

```
Copyright (c) 2018 Tomoyuki Sakurai <y@trombik.org>

Permission to use, copy, modify, and distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
```
