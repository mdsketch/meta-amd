#!/bin/bash

YOCTO_BRANCH="kirkstone"
MACHINE='siena'

# Source the environment setup script
source ./oe-init-build-env build-${MACHINE}-${YOCTO_BRANCH}

# Create the auto.conf file with specified configurations
tee conf/auto.conf <<EOF
DL_DIR ?= "\${TOPDIR}/../downloads"
SSTATE_DIR ?= "\${TOPDIR}/../sstate-cache"
MACHINE = "${MACHINE}"
DISTRO = "poky-amd"
EOF

# Add layers using bitbake-layers
bitbake-layers add-layer ../meta-openembedded/meta-oe
bitbake-layers add-layer ../meta-openembedded/meta-python
bitbake-layers add-layer ../meta-openembedded/meta-networking
bitbake-layers add-layer ../meta-dpdk
bitbake-layers add-layer ../meta-amd/meta-amd-distro
bitbake-layers add-layer ../meta-amd/meta-amd-bsp
bitbake-layers add-layer ../meta-openembedded/meta-filesystems
bitbake-layers add-layer ../meta-virtualization

# Build the core-image-sato target
bitbake core-image-sato -k

