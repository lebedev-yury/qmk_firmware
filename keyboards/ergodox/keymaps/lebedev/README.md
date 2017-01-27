# My Ergodox EZ layout

To build the hex file, simply run (within the `qmk_firmware` directory):

```
docker run -e keymap=lebedev -e keyboard=ergodox --rm -v $('pwd'):/qmk:rw edasque/qmk_firmware
```
