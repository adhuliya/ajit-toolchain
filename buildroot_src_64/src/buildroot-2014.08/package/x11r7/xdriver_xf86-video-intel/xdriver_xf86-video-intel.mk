################################################################################
#
# xdriver_xf86-video-intel
#
################################################################################

XDRIVER_XF86_VIDEO_INTEL_VERSION = 2.99.914
XDRIVER_XF86_VIDEO_INTEL_SOURCE = xf86-video-intel-$(XDRIVER_XF86_VIDEO_INTEL_VERSION).tar.bz2
XDRIVER_XF86_VIDEO_INTEL_SITE = http://xorg.freedesktop.org/releases/individual/driver
XDRIVER_XF86_VIDEO_INTEL_LICENSE = MIT
XDRIVER_XF86_VIDEO_INTEL_LICENSE_FILES = COPYING

XDRIVER_XF86_VIDEO_INTEL_CONF_OPT = \
	--disable-xvmc \
	--enable-sna \
	--disable-glamor \
	--disable-xaa \
	--disable-dga \
	--disable-async-swap

XDRIVER_XF86_VIDEO_INTEL_DEPENDENCIES = \
	libdrm \
	xlib_libXrandr \
	xlib_libpciaccess \
	xproto_fontsproto \
	xproto_xproto \
	xserver_xorg-server

# X.org server support for DRI depends on a Mesa3D DRI driver
ifeq ($(BR2_PACKAGE_MESA3D_DRI_DRIVER),y)
XDRIVER_XF86_VIDEO_INTEL_CONF_OPT += --enable-dri --enable-dri1
# quote from configure.ac: "UXA doesn't build without DRI2 headers"
ifeq ($(BR2_PACKAGE_XPROTO_DRI2PROTO),y)
XDRIVER_XF86_VIDEO_INTEL_CONF_OPT += --enable-dri2 --enable-uxa
else
XDRIVER_XF86_VIDEO_INTEL_CONF_OPT += --disable-dri2 --disable-uxa
endif
ifeq ($(BR2_PACKAGE_XPROTO_DRI3PROTO),y)
XDRIVER_XF86_VIDEO_INTEL_CONF_OPT += --enable-dri3
else
XDRIVER_XF86_VIDEO_INTEL_CONF_OPT += --disable-dri3
endif
else
XDRIVER_XF86_VIDEO_INTEL_CONF_OPT += --disable-dri
endif

$(eval $(autotools-package))
