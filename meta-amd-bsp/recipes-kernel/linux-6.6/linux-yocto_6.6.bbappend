require linux-yocto-6.6.inc


PR := "${INC_PR}.0"



SRCREV_machine = "8f34f6b7b6b3260eb6312a19ececcc97908d15b7"

inherit kernel

do_configure() {
   :; 
}

#S = "${WORKDIR}"

do_install() {
    install -d ${D}/lib/modules/${KERNEL_VERSION}/
#    cp -r ${WORKDIR}/lib/modules/* ${D}/lib/modules/${KERNEL_VERSION}/
#install -d ${D}${nonarch_base_libdir}
oe_runmake INSTALL_MOD_PATH=${D}/ modules_install


  rm -rf ${D}/lib/modules/${KERNEL_VERSION}/Module.symvers
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}/modules.builtin.alias.bin
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}/modules.symbols
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}/modules.softdep
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}/modules.dep.bin
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}/modules.alias
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}/modules.alias.bin
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}/modules.devname
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}/modules.symbols.bin
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}/modules.dep
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}/modules.builtin.bin
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}+/Module.symvers
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}+/modules.builtin.alias.bin
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}+/modules.symbols
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}+/modules.softdep
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}+/modules.dep.bin
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}+/modules.alias
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}+/modules.alias.bin
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}+/modules.devname
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}+/modules.symbols.bin
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}+/modules.dep
  rm -rf ${D}/lib/modules/${KERNEL_VERSION}+/modules.builtin.bin

}

PACKAGES =+ "extra-modules"

EXTRA_OEMAKE += "INSTALL_MOD_STRIP=1"
INSANE_SKIP:${PN} += "already-stripped"





