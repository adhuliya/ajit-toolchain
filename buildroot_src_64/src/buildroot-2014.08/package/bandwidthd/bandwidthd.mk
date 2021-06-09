################################################################################
#
# bandwidthd
#
################################################################################

BANDWIDTHD_VERSION = v2.0.1-auto-r08
BANDWIDTHD_SITE = $(call github,nroach44,bandwidthd,$(BANDWIDTHD_VERSION))

# Specified as "any version of the GPL that is current as of your
# download" by upstream.
BANDWIDTHD_LICENSE = GPL

BANDWIDTHD_DEPENDENCIES = gd libpng libpcap

BANDWIDTHD_AUTORECONF = YES

BANDWIDTHD_CONF_OPT += --without-x

ifeq ($(BR2_PACKAGE_BANDWIDTHD_POSTGRESQL),y)
BANDWIDTHD_DEPENDENCIES += postgresql
BANDWIDTHD_CONF_OPT += --with-postgresql-logging=true
else
BANDWIDTHD_CONF_OPT += --with-postgresql-logging=false
endif

ifeq ($(BR2_PACKAGE_BANDWIDTHD_SQLITE3),y)
BANDWIDTHD_DEPENDENCIES += sqlite
BANDWIDTHD_CONF_OPT += --with-sqlite-storage=true
else
BANDWIDTHD_CONF_OPT += --with-sqlite-storage=false
endif

$(eval $(autotools-package))
