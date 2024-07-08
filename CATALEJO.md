#   CLONAR E INSTALAR

Nodemcu build firmware from git

```bash
mkdir -p ~/projects && cd ~/projects
git clone git@github.com:johnnycubides/catalejo-nodemcu-firmware.git
cd catalejo-nodemcu-firmware
git submodule init
git submodule update --recursive
```

BUILD INIT

BUILD OPCTIONS
https://nodemcu.readthedocs.io/en/release/build/#build-options

```bash
sudo apt install python3-serial
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

## esptool

Para instalar esptool se recomienda hacer uso de conda
y desde conda instalar esptool, ejemplo:

```
pip install click esptool

```

Observación: crear una variable de entorno en conda llamada nodemcu para mayor
facilidad.
