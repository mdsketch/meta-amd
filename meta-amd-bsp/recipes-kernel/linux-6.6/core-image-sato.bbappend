IMAGE_INSTALL:append= "linux-firmware"
IMAGE_INSTALL:append= " nvme-cli"

CORE_IMAGE_EXTRA_INSTALL += " kernel-modules"
IMAGE_INSTALL:append = " kernel-modules"

# In your image recipe (.bb file)
CORE_IMAGE_EXTRA_INSTALL += " kernel-modules"

# Optionally, you can specify the specific kernel-modules package
IMAGE_INSTALL:append = " kernel-modules"

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


