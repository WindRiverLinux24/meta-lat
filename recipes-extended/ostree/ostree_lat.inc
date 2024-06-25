FILESEXTRAPATHS:prepend := "${THISDIR}:${THISDIR}/files:"

SRC_URI += " \
    file://0009-support-no-initramfs-situation.patch \
    file://init-ostree-no-initramfs.sh \
"

RDEPENDS:${PN}:class-target += " \
    ${@bb.utils.contains('DISTRO_FEATURES', 'ostree-no-initramfs', '${PN}-init-no-initramfs', '', d)} \
"

RDEPENDS:${PN}-init-no-initramfs = " \
    tar \
    util-linux-blkid \
    util-linux-fdisk \
    util-linux-lsblk \
    util-linux-sfdisk \
    util-linux-blockdev \
    util-linux-mount \
    e2fsprogs \
    e2fsprogs-resize2fs \
    e2fsprogs-mke2fs \
    e2fsprogs-e2fsck \
"

PACKAGES =+ "${PN}-init-no-initramfs"

FILES:${PN}-init-no-initramfs = " \
    /init-ostree-pre.sh \
"

# Use the given compiler to build ostree-prepare-root statically linked
PACKAGECONFIG[static-ostree-prepare-root] = "--with-static-compiler='${CC}', --without-static-compiler"

PACKAGECONFIG:append = " \
    ${@bb.utils.contains('DISTRO_FEATURES', 'ostree-no-initramfs', 'static-ostree-prepare-root', '', d)} \
"

do_install:append:class-target() {
	install -m 0755 ${WORKDIR}/init-ostree-no-initramfs.sh ${D}/init-ostree-pre.sh
}
