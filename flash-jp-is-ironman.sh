#!/usr/bin/env bash
#
# flash-jp-is-ironman.sh — flash the jp-is-ironman sketch to the UNO R4 WiFi.
#
# Thin wrapper around the shared engine flash.sh. Pass -c to compile only.
#   ./flash-jp-is-ironman.sh        # compile + upload
#   ./flash-jp-is-ironman.sh -c     # compile only
exec "$(dirname "$0")/flash.sh" jp-is-ironman "$@"
