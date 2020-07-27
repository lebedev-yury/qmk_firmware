# My Ergodox EZ layout

First, you have to install the QMK tool:

```bash
brew install qmk/qmk/qmk
```

To build the hex file, simply run (within the `qmk_firmware` directory):

```bash
qmk compile -kb ergodox_ez -km lebedev
```
