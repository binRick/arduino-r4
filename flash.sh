#!/usr/bin/env bash
#
# flash.sh — compile and upload an Arduino sketch to the UNO R4 WiFi.
#
# Convention: each sketch lives in its own folder whose name matches the
# .ino file, e.g.  jp-is-ironman/jp-is-ironman.ino
#
# This is the shared engine. Normally you run a per-sketch wrapper instead,
# e.g.  ./flash-jp-is-ironman.sh  (which just calls this with the right name).
#
# Usage:
#   ./flash.sh <SketchDir>     # compile + upload that sketch
#   ./flash.sh -c <SketchDir>  # compile only (no upload)
#
# The serial port is auto-detected, so you don't need to know it.
set -euo pipefail

FQBN="arduino:renesas_uno:unor4wifi"
COMPILE_ONLY=0

# --- parse args ---------------------------------------------------------
# Accept -c (compile only) in any position; first non-flag arg is the sketch.
SKETCH=""
for arg in "$@"; do
  case "$arg" in
    -c) COMPILE_ONLY=1 ;;
    *)  [[ -z "$SKETCH" ]] && SKETCH="$arg" ;;
  esac
done
SKETCH="${SKETCH%/}"          # strip a trailing slash if tab-completed
if [[ -z "$SKETCH" ]]; then
  echo "usage: $(basename "$0") [-c] <SketchDir>" >&2
  exit 1
fi

# Run from the repo root (where this script lives) so paths are stable.
cd "$(dirname "$0")"

if [[ ! -f "$SKETCH/$SKETCH.ino" ]]; then
  echo "error: '$SKETCH/$SKETCH.ino' not found." >&2
  echo "Sketches must be in a folder matching the .ino name, e.g. JP_Matrix/JP_Matrix.ino" >&2
  exit 1
fi

# --- detect the board's serial port ------------------------------------
# Ask arduino-cli which port has the R4 attached; fall back to globbing.
detect_port() {
  local p
  p="$(arduino-cli board list 2>/dev/null | awk -v fqbn="$FQBN" '$0 ~ fqbn {print $1; exit}')"
  if [[ -z "$p" ]]; then
    p="$(ls /dev/cu.usbmodem* 2>/dev/null | head -n1 || true)"
  fi
  printf '%s' "$p"
}

# --- compile ------------------------------------------------------------
echo ">> Compiling $SKETCH ..."
arduino-cli compile --fqbn "$FQBN" "$SKETCH"

if [[ "$COMPILE_ONLY" == "1" ]]; then
  echo ">> Compile-only: done."
  exit 0
fi

# --- upload -------------------------------------------------------------
PORT="$(detect_port)"
if [[ -z "$PORT" ]]; then
  echo "error: no Arduino serial port found. Is the board plugged in?" >&2
  exit 1
fi

echo ">> Uploading to $PORT ..."
arduino-cli upload -p "$PORT" --fqbn "$FQBN" "$SKETCH"
echo ">> Done."
