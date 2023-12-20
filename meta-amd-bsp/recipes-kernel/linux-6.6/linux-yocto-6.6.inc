KBRANCH ?= "linux-6.6.y"
SECTION = "kernel"
LICENSE = "GPL-2.0-only"
FILESEXTRAPATHS:prepend := "${THISDIR}/linux-yocto-6.6:"

#LIC_FILES_CHKSUM ?= "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

UPSTREAM_CHECK_GITTAGREGEX = "(?P<pver>\d+\.\d+(\.\d+)*)"

RECIPE_NO_UPDATE_REASON = "Recipe is updated through a separate process"

# Skip processing of this recipe if it is not explicitly specified as the
# PREFERRED_PROVIDER for virtual/kernel. This avoids network access required
# by the use of AUTOREV SRCREVs, which are the default for this recipe.
python () {
    if d.getVar("KERNEL_PACKAGE_NAME") == "kernel" and d.getVar("PREFERRED_PROVIDER_virtual/kernel") != d.getVar("PN"):
        d.delVar("BB_DONT_CACHE")
        raise bb.parse.SkipRecipe("Set PREFERRED_PROVIDER_virtual/kernel to %s to enable it" % (d.getVar("PN")))
}

DEPENDS += "xz-native bc-native"
DEPENDS:append:aarch64 = " libgcc"
KERNEL_CC:append:aarch64 = " ${TOOLCHAIN_OPTIONS}"
KERNEL_LD:append:aarch64 = " ${TOOLCHAIN_OPTIONS}"

DEPENDS:append:nios2 = " libgcc"
KERNEL_CC:append:nios2 = " ${TOOLCHAIN_OPTIONS}"
KERNEL_LD:append:nios2 = " ${TOOLCHAIN_OPTIONS}"

DEPENDS:append:arc = " libgcc"
KERNEL_CC:append:arc = " ${TOOLCHAIN_OPTIONS}"
KERNEL_LD:append:arc = " ${TOOLCHAIN_OPTIONS}"

KERNEL_FEATURES:append:qemuall=" features/debug/printk.scc"

KERNEL_FEATURES:append = " ${@bb.utils.contains('MACHINE_FEATURES', 'numa', 'features/numa/numa.scc', '', d)}"
KERNEL_FEATURES:append = " ${@bb.utils.contains('MACHINE_FEATURES', 'vfat', 'cfg/fs/vfat.scc', '', d)}"


# A KMACHINE is the mapping of a yocto $MACHINE to what is built
# by the kernel. This is typically the branch that should be built,
# and it can be specific to the machine or shared
# KMACHINE = "UNDEFINED"

LINUX_VERSION_EXTENSION ??= "-yocto-${LINUX_KERNEL_TYPE}"

# Pick up shared functions
#inherit kernel
#inherit kernel-yocto

B = "${WORKDIR}/linux-${PACKAGE_ARCH}-${LINUX_KERNEL_TYPE}-build"


# enable kernel-sample for oeqa/runtime/cases's ksample.py test
KERNEL_FEATURES:append:qemuall=" features/kernel-sample/kernel-sample.scc"

KERNEL_DEBUG_OPTIONS ?= "stack"
KERNEL_EXTRA_ARGS:append:x86-64 = " ${@bb.utils.contains('KERNEL_DEBUG_OPTIONS', 'stack', 'HOST_LIBELF_LIBS="-L${RECIPE_SYSROOT_NATIVE}/usr/lib/pkgconfig/../../../usr/lib/ -lelf"', '', d)}"

do_devshell:prepend() {
    # setup native pkg-config variables (kconfig scripts call pkg-config directly, cannot generically be overriden to pkg-config-native)
    d.setVar("PKG_CONFIG_DIR", "${STAGING_DIR_NATIVE}${libdir_native}/pkgconfig")
    d.setVar("PKG_CONFIG_PATH", "${PKG_CONFIG_DIR}:${STAGING_DATADIR_NATIVE}/pkgconfig")
    d.setVar("PKG_CONFIG_LIBDIR", "${PKG_CONFIG_DIR}")
    d.setVarFlag("PKG_CONFIG_SYSROOT_DIR", "unexport", "1")
    d.appendVar("OE_TERMINAL_EXPORTS", " PKG_CONFIG_DIR PKG_CONFIG_PATH PKG_CONFIG_LIBDIR PKG_CONFIG_SYSROOT_DIR")
}



# board specific branches
#KBRANCH:qemuarm  ?= "v5.15/standard/arm-versatile-926ejs"
#KBRANCH:qemuarm64 ?= "v5.15/standard/qemuarm64"
#KBRANCH:qemumips ?= "v5.15/standard/mti-malta32"
#KBRANCH:qemuppc  ?= "v5.15/standard/qemuppc"
#KBRANCH:qemuriscv64  ?= "v5.15/standard/base"
#KBRANCH:qemuriscv32  ?= "v5.15/standard/base"
#KBRANCH:qemux86  ?= "v5.15/standard/base"
#KBRANCH:qemux86-64 ?= "v5.15/standard/base"
#KBRANCH:qemumips64 ?= "v5.15/standard/mti-malta64"

SRCREV_machine:qemuarm ?= "21687086c27bb112f19b0aac455d800961c0b830"
SRCREV_machine:qemuarm64 ?= "7144f86a73fe2ffe4fe57c9e6cf28d8fc8db4b6a"
SRCREV_machine:qemumips ?= "557c06060cb218ade536fccc66f8f3e755537f31"
SRCREV_machine:qemuppc ?= "db19dbdcdf51b9d2a071dcf180ba9e20b8286e9b"
SRCREV_machine:qemuriscv64 ?= "024d08fb706170a9723e9751e505681f9d4c7ab6"
SRCREV_machine:qemuriscv32 ?= "024d08fb706170a9723e9751e505681f9d4c7ab6"
SRCREV_machine:qemux86 ?= "024d08fb706170a9723e9751e505681f9d4c7ab6"
SRCREV_machine:qemux86-64 ?= "024d08fb706170a9723e9751e505681f9d4c7ab6"
SRCREV_machine:qemumips64 ?= "6f1dbe8c258d49f4dba59827124dfe9aa2c151db"
SRCREV_machine ?= "024d08fb706170a9723e9751e505681f9d4c7ab6"
SRCREV_meta ?= "441f5fe00073620cec471166cf6e94c4ef9c69b2"


# set your preferred provider of linux-yocto to 'linux-yocto-upstream', and you'll
# get the <version>/base branch, which is pure upstream -stable, and the same
# meta SRCREV as the linux-yocto-standard builds. Select your version using the
# normal PREFERRED_VERSION settings.
#BBCLASSEXTEND = "devupstream:target"
SRCREV_machine:class-devupstream ?= "8020ae3c051d1c9ec7b7a872e226f9720547649b"
#PN:class-devupstream = "linux-yocto-upstream"
KBRANCH:class-devupstream = "linux-6.6.y"

INC_PR := "r1"
SRCBRANCHARG = "${@['nobranch=1', 'branch=${KBRANCH}'][d.getVar('KBRANCH', True) != '']}"

FILESOVERRIDES:append := ":${@bb.parse.vars_from_file(d.getVar('FILE', False),d)[1] or ''}"

KERNELURI ?= "git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git;protocol=https;name=machine;branch=linux-6.6.y"
YOCTO_META ?= "git://git.yoctoproject.org/yocto-kernel-cache;type=kmeta;name=meta;branch=yocto-6.5;destsuffix=yocto-kmeta"
SRC_URI = "${KERNELURI};${SRCBRANCHARG} ${YOCTO_META} file://ntb.cfg file://pingpong.cfg file://ntb_netdev.cfg file://ntb_tool.cfg file://ntb_perf.cfg file://NVME-Core.cfg file://dmatest.cfg file://nvme.cfg file://ntbtool.cfg file://0002-net-phy-aquantia-Add-10mbps-support.patch file://0009-net-phy-Broadcom-Added-support-for-BCM84892-PHY-devi.patch file://0011-amd-xgbe-need-to-check-KR-training-before-restart-CL.patch file://0012-amd-xgbe-Custom-initialization-of-Marvell-PHY-on-Bil.patch file://0013-amd-xgbe-fix-to-Custom-initialization-of-Marvell-PHY.patch file://0014-amd-xgbe-Start-AN-with-KR-training-auto-start.patch file://0015-amd-xgbe-AN-force-modeset-to-10GKR-for-resetting-HW.patch file://0018-amd-xgbe-WA-patch-to-fix-the-AN-issue.patch file://0019-amd-xgbe-register-has-to-read-twice-to-get-correct-v.patch file://0020-amd-xgbe-v2-add-support-for-ethernet-LEDs.patch file://0021-amd-xgbe-Work-around-patch-for-10G-BCM-link-stabilit.patch file://0022-amd-xgbe-V2-extend-driver-functionality-to-support-1.patch file://0023-mmc-sdhci-acpi-eMMC-5.0-host-controller-fix-for-AMD-.patch file://0024-Bilby-dummy-codec.patch file://amdgpu.cfg file://cpuinfo.cfg file://spi.cfg file://cxl.cfg file://AE4DMA.cfg"


LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"


KMETA = "kernel-meta"
KCONF_BSP_AUDIT_LEVEL = "1"

KERNEL_DEVICETREE:qemuarmv5 = "versatile-pb.dtb"

#COMPATIBLE_MACHINE = "^(qemuarm|qemuarmv5|qemuarm64|qemux86|qemuppc|qemuppc64|qemumips|qemumips64|qemux86-64|qemuriscv64|qemuriscv32)$"
KBRANCH = "linux-6.6.y"

SRCREV_machine = "ac25535242acb0d0042b920e5232b10e76ad169b"

LINUX_VERSION = "6.6.7"


KMACHINE = "common-pc-64"
SRCREV_meta = "8368cc1f9d0a6f8681602a918746df3b3932bad6"

LINUX_VERSION_EXTENSION = "-amd-${LINUX_KERNEL_TYPE}"

COMPATIBLE_MACHINE = "${MACHINE}"



