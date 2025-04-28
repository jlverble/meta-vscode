DESCRIPTION = "Packaging for prebuilt versions of vscode"
HOMEPAGE = "https://code.visualstudio.com/download"
LICENSE = "Apache-2.0"

COMPATIBLE_HOST = "(x86_64|aarch64|arm).*-linux"

inherit bin_package

def get_host_arch(d):
    arch = d.getVar('HOST_ARCH')
    if arch == "aarch64":
        return "arm64"
    elif arch == "arm":
        return "armhf"
    elif arch == "x86_64":
        return "x64"
    bb.error("unrecognized HOST_ARCH: %s", arch)

VSCODE_ARCH = "${@get_host_arch(d)}"

SRC_URI = "https://vscode.download.prss.microsoft.com/dbazure/download/stable/${GIT_SHA}/code-stable-${VSCODE_ARCH}-${TIMESTAMP-${VSCODE_ARCH}}.tar.gz;name=vscode-${VSCODE_ARCH}"

do_install() {
    install -d ${D}${datadir}/vscode
    cp -r ${WORKDIR}/VSCode-linux-${VSCODE_ARCH}/* ${D}${datadir}/vscode
}

FILES:${PN} = "${datadir}"
INSANE_SKIP:${PN} += "already-stripped file-rdeps ldflags libdir"
INSANE_SKIP:${PN}-dbg += "libdir"
