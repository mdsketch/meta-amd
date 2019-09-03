FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${MACHINE}:"

DESCRIPTION = "These binaries provide kernel support for newer AMD GPUs"
SECTION = "kernel"
LICENSE = "Firmware-amd"

SRC_URI_r1000 = "file://raven2_asd.bin \
		 file://raven2_ce.bin \
		 file://raven2_gpu_info.bin \
		 file://raven2_me.bin \
		 file://raven2_mec2.bin \
		 file://raven2_mec.bin \
		 file://raven2_pfp.bin \
		 file://raven2_rlc.bin \
		 file://raven2_sdma.bin \
		 file://raven2_vcn.bin \
		 file://LICENSE \
"

SRC_URI_v1000 = "file://raven_me.bin file://raven_pfp.bin file://raven_vcn.bin \
		 file://raven_ce.bin file://raven_mec2.bin file://raven_rlc.bin \
		 file://raven_gpu_info.bin file://raven_mec.bin file://raven_sdma.bin \
		 file://raven_asd.bin file://LICENSE \
"

LIC_FILES_CHKSUM = "file://LICENSE;md5=07b0c31777bd686d8e1609c6940b5e74"

S = "${WORKDIR}"

# Since, no binaries are generated for a specific target,
# inherit allarch to simply populate prebuilt binaries
inherit allarch

do_compile() {
	:
}

do_install() {
	install -v -m 444 -D ${S}/LICENSE ${D}/lib/firmware/amdgpu/LICENSE
	install -v -m 0644 ${S}/*.bin ${D}/lib/firmware/amdgpu
}

FILES_${PN} = "/lib/firmware/*"