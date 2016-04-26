#deltask do_configure 
#deltask do_compile 
#deltask do_package 
#deltask do_package_write_rpm 
#deltask do_package_write_ipk 
#deltask do_package_write_deb
#deltask do_install 
#deltask do_populate_sysroot
#deltask do_populate_lic 
#deltask do_package_qa
#deltask do_packagedata
#deltask do_rm_work
do_configure[noexec] = "1"
do_compile[noexec] = "1"
do_package[noexec] = "1"
do_package_write_rpm[noexec] = "1"
do_package_write_ipk[noexec] = "1"
do_package_write_deb[noexec] = "1"
do_install[noexec] = "1"
do_populate_sysroot[noexec] = "1"
do_populate_lic[noexec] = "1"
do_package_qa[noexec] = "1"
do_packagedata[noexec] = "1"
do_rm_work[noexec] = "1"

PN = "gcc-source-${PV}"
WORKDIR = "${TMPDIR}/work-shared/gcc-${PV}-${PR}"
SSTATE_SWSPEC = "sstate:gcc::${PV}:${PR}::${SSTATE_VERSION}:"

STAMP = "${STAMPS_DIR}/work-shared/gcc-${PV}-${PR}"
STAMPCLEAN = "${STAMPS_DIR}/work-shared/gcc-${PV}-*"

INHIBIT_DEFAULT_DEPS = "1"
DEPENDS = ""
PACKAGES = ""

python do_preconfigure () {
    import subprocess
    cmd = d.expand('cd ${S} && PATH=${PATH} gnu-configize')
    subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True)
    # See 0044-gengtypes.patch, we need to regenerate this file
    bb.utils.remove(d.expand("${S}/gcc/gengtype-lex.c"))
    cmd = d.expand("sed -i 's/BUILD_INFO=info/BUILD_INFO=/' ${S}/gcc/configure")
    subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True)
}
addtask do_preconfigure after do_patch
do_preconfigure[depends] += "gnu-config-native:do_populate_sysroot autoconf-native:do_populate_sysroot"
