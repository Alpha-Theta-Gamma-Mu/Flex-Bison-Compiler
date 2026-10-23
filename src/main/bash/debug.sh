#! /bin/bash

set -euo pipefail

BASE_PATH="$(dirname "$0")/../../.."
cd "$BASE_PATH"

INPUT="$1"
shift 1
cat "$INPUT" \
	| ASAN_OPTIONS="abort_on_error=1:detect_leaks=0" \
		gdbserver :2345 ".build/Flex-Bison-Compiler" "$@"
