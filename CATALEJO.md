#   CLONAR E INSTALAR

Nodemcu build firmware from git

```bash
git clone git@github.com:johnnycubides/catalejo-nodemcu-firmware.git
git submodule init
git submodule update --recursive
```

BUILD INIT

BUILD OPCTIONS
https://nodemcu.readthedocs.io/en/release/build/#build-options

```bash
make
```


FLASH

esptool version 4
```bash
esptool.py write_flash 0x00000 bin/0x00000.bin 0x10000 bin/0x10000.bin
```

SERIAL COM
```bash
picocom /dev/ttyUSB0 -b 115200
```

## CROSS COMPILE LUAC

```bash
ln -sr ./luac.cross ~/.local/bin/
```
