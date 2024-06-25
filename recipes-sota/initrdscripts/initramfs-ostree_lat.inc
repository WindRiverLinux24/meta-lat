FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
	file://init-ostree-install.lat.sh \
	file://lat-installer.sh \
	file://lat-installer.hook \
"

# For LAT usage
do_export_yocto_vars() {
    mkdir -p ${PKGDATA_DIR}
    echo "[yocto]" > ${PKGDATA_DIR}/.yocto_vars.env
    echo "MULTIMACH_TARGET_SYS=${MULTIMACH_TARGET_SYS}" >> ${PKGDATA_DIR}/.yocto_vars.env
    echo "PACKAGE_ARCHS=${PACKAGE_ARCHS}" >> ${PKGDATA_DIR}/.yocto_vars.env
}
addtask export_yocto_vars

do_install:append() {
	rm -f ${D}/install
	install -m 0755 ${WORKDIR}/init-ostree-install.lat.sh ${D}/install
	sed -i -e 's#@OSTREE_OSNAME@#${OSTREE_OSNAME}#g' ${D}/install
	if [ "${OSTREE_FDISK_BLM}" != "" ] ; then
		sed -i -e 's/^BLM=.*/BLM=${OSTREE_FDISK_BLM}/' ${D}/install
	fi
	if [ "${OSTREE_FDISK_FSZ}" != "" ] ; then
		sed -i -e 's/^FSZ=.*/FSZ=${OSTREE_FDISK_FSZ}/' ${D}/install
	fi
	if [ "${OSTREE_FDISK_BSZ}" != "" ] ; then
		sed -i -e 's/^BSZ=.*/BSZ=${OSTREE_FDISK_BSZ}/' ${D}/install
	fi
	if [ "${OSTREE_FDISK_RSZ}" != "" ] ; then
		sed -i -e 's/^RSZ=.*/RSZ=${OSTREE_FDISK_RSZ}/' ${D}/install
	fi
	if [ "${OSTREE_FDISK_VSZ}" != "" ] ; then
		sed -i -e 's/^VSZ=.*/VSZ=${OSTREE_FDISK_VSZ}/' ${D}/install
	fi
	install -m 0755 ${WORKDIR}/lat-installer.sh ${D}/lat-installer.sh
	install -m 0755 ${WORKDIR}/lat-installer.hook ${D}/lat-installer.hook
}

FILES:${PN}-installer += " \
    /lat-installer.sh \
    /lat-installer.hook \
"
