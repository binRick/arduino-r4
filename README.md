# arduino-r4

Sketches for the **Arduino UNO R4 WiFi** (Renesas RA4M1), built and flashed
with [`arduino-cli`](https://arduino.github.io/arduino-cli/).

## Naming convention (follow this for every new sketch)

Use lowercase, hyphenated names. Each sketch gets:

1. A folder + `.ino` matching the name:  `<sketch-name>/<sketch-name>.ino`
2. A dedicated flash script:             `flash-<sketch-name>.sh`

Example:

```
jp-is-ironman/jp-is-ironman.ino
flash-jp-is-ironman.sh
```

`flash.sh` is the shared engine that does the actual compile + upload and
auto-detects the serial port. Each `flash-<name>.sh` is a one-line wrapper
that calls it with the right sketch name — so you run the per-sketch script,
never `flash.sh` directly.

### Adding a new sketch

```bash
mkdir my-sketch
$EDITOR my-sketch/my-sketch.ino
cp flash-jp-is-ironman.sh flash-my-sketch.sh
# edit the last line of flash-my-sketch.sh to pass "my-sketch"
chmod +x flash-my-sketch.sh
./flash-my-sketch.sh
```

## Flashing

Plug in the board over USB, then run the sketch's script:

```bash
./flash-jp-is-ironman.sh        # compile + upload
./flash-jp-is-ironman.sh -c     # compile only, no upload
```

The serial port is auto-detected, so you don't need to pass it.

## One-time setup

```bash
brew install arduino-cli
arduino-cli core update-index
arduino-cli core install arduino:renesas_uno
arduino-cli lib install ArduinoGraphics
```

- **FQBN:** `arduino:renesas_uno:unor4wifi`
- The R4 WiFi has a built-in **12×8 LED matrix**
  (`Arduino_LED_Matrix`, ships with the core).

## Sketches

- **jp-is-ironman** — holds a static "JP" splash for 3 s, then scrolls
  "JP IS IRONMAN" across the LED matrix forever.
