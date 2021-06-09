################################################################################
#
# radvd
#
################################################################################

RADVD_VERSION = 2.5
RADVD_SOURCE = radvd-$(RADVD_VERSION).tar.xz
RADVD_SITE = http://www.litech.org/radvd/dist
RADVD_DEPENDENCIES = host-bison flex host-flex host-pkgconf
RADVD_CONF_ENV = ac_cv_prog_cc_c99='-std=gnu99'
# For radvd-01-drop-check.patch & radvd-02-drop-stack-protector.patch
RADVD_AUTORECONF = YES

define RADVD_INSTALL_INITSCRIPT
	$(INSTALL) -m 0755 package/radvd/S50radvd $(TARGET_DIR)/etc/init.d
endef

RADVD_POST_INSTALL_TARGET_HOOKS += RADVD_INSTALL_INITSCRIPT

$(eval $(autotools-package))
