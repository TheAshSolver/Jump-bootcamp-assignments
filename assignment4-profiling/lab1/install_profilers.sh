#!/usr/bin/env bash
set -euo pipefail

FLAMEGRAPH_DIR="${HOME}/FlameGraph"
SYSCTL_CONF="/etc/sysctl.d/99-perf-lab.conf"

echo "Updating package index..."
sudo dnf check-update || true 

echo "Installing compiler and profiling tools..."
# FIX: Using the lowercase group ID for DNF5 compatibility
sudo dnf install -y @development-tools

# Installs the rest of your profiling utilities
sudo dnf install -y \
    binutils \
    git \
    kcachegrind \
    perf \
    perl \
    valgrind

echo "Installing FlameGraph into ${FLAMEGRAPH_DIR}..."
if [ -d "${FLAMEGRAPH_DIR}/.git" ]; then
    git -C "${FLAMEGRAPH_DIR}" pull --ff-only
elif [ -e "${FLAMEGRAPH_DIR}" ]; then
    echo "ERROR: ${FLAMEGRAPH_DIR} already exists but is not a git repository."
    echo "Move it aside and rerun this script, or install FlameGraph there manually."
    exit 1
else
    git clone https://github.com/brendangregg/FlameGraph.git "${FLAMEGRAPH_DIR}"
fi

echo "Configuring perf permissions..."
sudo tee "${SYSCTL_CONF}" >/dev/null <<'EOF'
# Settings for the educational profiling lab.
kernel.perf_event_paranoid = -1
kernel.kptr_restrict = 0
EOF

sudo sysctl --system >/dev/null

echo "Checking installed tools..."
if command -v gprof >/dev/null 2>&1; then
    gprof --version | head -n 1
else
    echo "gprof: Not found (compiled binaries can still be profiled via perf/valgrind)"
fi

perf --version
valgrind --version
command -v kcachegrind >/dev/null && echo "kcachegrind: Available"
test -x "${FLAMEGRAPH_DIR}/flamegraph.pl" && echo "flamegraph.pl: Ready"
test -x "${FLAMEGRAPH_DIR}/stackcollapse-perf.pl" && echo "stackcollapse-perf.pl: Ready"

echo "---"
echo "Done."