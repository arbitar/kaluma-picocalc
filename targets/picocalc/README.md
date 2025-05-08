# Target: PicoCalc (Raspberry Pi Pico with some other hardware)

## Build

```sh
$ node build
# or, node build --target=rpi-pico
```

The `picocalc-pico.uf2` will be created in the `/build` folder.

## Flash

1. Push and hold BOOTSEL button and plug into USB (recognized as a USB Mass Storage named `RPI-RP2`)
2. Drag and drop the `picocalc-pico.uf2` on the `RPI-RP2` volume.
3. Automatically reboot.
