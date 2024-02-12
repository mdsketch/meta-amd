This is the release notes document for the AMD BSP. This document contains
information about the Yocto layers' git repos, their branches and commit
hashes, software versions, and known/fixed issues/limitations.

## Bitbake layers
| Layer             | Git Repo                                     | Branch    | Commit Hash/Tag                          |
|:------------------|:---------------------------------------------|:----------|:-----------------------------------------|
| poky              | git://git.yoctoproject.org/poky              | kirkstone | tags/yocto-4.0.9                         |
| meta-openembedded | git://git.openembedded.org/meta-openembedded | kirkstone | 402affcc073db39f782c1ebfd718edd5f11eed4c |
| meta-dpdk         | git://git.yoctoproject.org/meta-dpdk         | kirkstone | 12cd9701455f17ff86681dba86e5c10f7b0deb7c |
| meta-amd          | git://git.yoctoproject.org/meta-amd          | kirkstone | tags/kirkstone-amd-epg-siena-202402      |

## Software versions
| Software        | Version  |
|:----------------|:---------|
| Yocto Poky base | 4.0.9    |
| grub            | 2.06     |
| linux-yocto     | 6.6.9    |
| gdb             | 11.2     |

## Fixed issues

## Known issues

* Siena:
##iso image is not booting in xen
##tpm lshw mokutil tools not supporting
