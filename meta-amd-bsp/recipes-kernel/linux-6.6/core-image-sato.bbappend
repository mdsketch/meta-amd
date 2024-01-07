CORE_IMAGE_EXTRA_INSTALL += " kernel-modules"


# Optionally, you can specify the specific kernel-modules package
IMAGE_INSTALL:append = " kernel-modules nvme-cli kernel-module-ntb  spitools linux-firmware"
IMAGE_INSTALL:append = " spidev-test rpm opkg"
#KERNEL_MODULE_AUTOLOAD += "spidev"
KERNEL_MODULE_AUTOLOAD += "ntb_netdev"


inherit core-image

# Conditionally add packages for Siena
do_siena[prefunc] = "siena_prefunc"
siena_prefunc() {
    # Only add these packages for the 'siena' machine
    if test "${MACHINE}" = "siena"; then
        IMAGE_INSTALL:append = " lscpuinfo git"
    fi
}

# Conditionally add packages for V1000
do_v1000[prefunc] = "v1000_prefunc"
v1000_prefunc() {
    # Only add these packages for the 'v1000' machine
    if test "${MACHINE}" = "v1000"; then
        KERNEL_MODULE_AUTOLOAD_amdgpu += "amdgpu"
    fi
}

DEPENDS += "lib64-setup"
IMAGE_INSTALL:append = " lib64-setup"
