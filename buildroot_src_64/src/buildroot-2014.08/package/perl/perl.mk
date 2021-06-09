################################################################################
#
# perl
#
################################################################################

PERL_VERSION_MAJOR = 18
PERL_VERSION = 5.$(PERL_VERSION_MAJOR).2
PERL_SITE = http://www.cpan.org/src/5.0
PERL_SOURCE = perl-$(PERL_VERSION).tar.bz2
PERL_LICENSE = Artistic or GPLv1+
PERL_LICENSE_FILES = Artistic Copying README
PERL_INSTALL_STAGING = YES

PERL_CROSS_VERSION = 0.8.5
PERL_CROSS_BASE_VERSION = 5.$(PERL_VERSION_MAJOR).2
# DO NOT refactor with the github helper (the result is not the same)
PERL_CROSS_SITE    = http://raw.github.com/arsv/perl-cross/releases
PERL_CROSS_SOURCE  = perl-$(PERL_CROSS_BASE_VERSION)-cross-$(PERL_CROSS_VERSION).tar.gz
PERL_CROSS_OLD_POD = perl$(subst .,,$(PERL_CROSS_BASE_VERSION))delta.pod
PERL_CROSS_NEW_POD = perl$(subst .,,$(PERL_VERSION))delta.pod

# We use the perlcross hack to cross-compile perl. It should
# be extracted over the perl sources, so we don't define that
# as a separate package. Instead, it is downloaded and extracted
# together with perl

define PERL_CROSS_DOWNLOAD
	$(call DOWNLOAD,$(PERL_CROSS_SITE:/=)/$(PERL_CROSS_SOURCE))
endef
PERL_POST_DOWNLOAD_HOOKS += PERL_CROSS_DOWNLOAD

define PERL_CROSS_EXTRACT
	$(call suitable-extractor,$(PERL_CROSS_SOURCE)) $(DL_DIR)/$(PERL_CROSS_SOURCE) | \
	$(TAR) $(TAR_STRIP_COMPONENTS)=1 -C $(@D) $(TAR_OPTIONS) -
endef
PERL_POST_EXTRACT_HOOKS += PERL_CROSS_EXTRACT

define PERL_CROSS_SET_POD
	$(SED) s/$(PERL_CROSS_OLD_POD)/$(PERL_CROSS_NEW_POD)/g $(@D)/Makefile
endef
PERL_POST_PATCH_HOOKS += PERL_CROSS_SET_POD

ifeq ($(BR2_PACKAGE_BERKELEYDB),y)
    PERL_DEPENDENCIES += berkeleydb
endif
ifeq ($(BR2_PACKAGE_GDBM),y)
    PERL_DEPENDENCIES += gdbm
endif

# We have to override LD, because an external multilib toolchain ld is not
# wrapped to provide the required sysroot options.  We also can't use ccache
# because the configure script doesn't support it.
PERL_CONF_OPT = \
	--target=$(GNU_TARGET_NAME) \
	--target-tools-prefix=$(TARGET_CROSS) \
	--prefix=/usr \
	-Dld="$(TARGET_CC_NOCCACHE)" \
	-Dccflags="$(TARGET_CFLAGS)" \
	-Dldflags="$(TARGET_LDFLAGS) -lm" \
	-Dmydomain="" \
	-Dmyhostname="$(BR2_TARGET_GENERIC_HOSTNAME)" \
	-Dmyuname="Buildroot $(BR2_VERSION_FULL)" \
	-Dosname=linux \
	-Dosvers=$(LINUX_VERSION) \
	-Dperladmin=root

ifeq ($(shell expr $(PERL_VERSION_MAJOR) % 2), 1)
    PERL_CONF_OPT += -Dusedevel
endif

ifeq ($(BR2_PREFER_STATIC_LIB),y)
    PERL_CONF_OPT += --all-static --no-dynaloader
endif

ifneq ($(BR2_LARGEFILE),y)
    PERL_CONF_OPT += -Uuselargefiles
endif

PERL_MODULES = $(call qstrip,$(BR2_PACKAGE_PERL_MODULES))
ifneq ($(PERL_MODULES),)
PERL_CONF_OPT += --only-mod=$(subst $(space),$(comma),$(PERL_MODULES))
endif

define PERL_CONFIGURE_CMDS
	(cd $(@D); HOSTCC='$(HOSTCC_NOCACHE)' ./configure $(PERL_CONF_OPT))
	$(SED) 's/UNKNOWN-/Buildroot $(BR2_VERSION_FULL) /' $(@D)/patchlevel.h
endef

define PERL_BUILD_CMDS
	$(MAKE1) -C $(@D) all
endef

define PERL_INSTALL_STAGING_CMDS
	$(MAKE1) -C $(@D) DESTDIR="$(STAGING_DIR)" install.perl
endef

define PERL_INSTALL_TARGET_CMDS
	$(MAKE1) -C $(@D) DESTDIR="$(TARGET_DIR)" install.perl
endef

# perl infra: fix for Perl XS packages configured by Makefile.PL
#
# ExtUtils::MakeMaker adds all the header files used by the perl as
# dependencies to the generated Makefile. This means that the generated
# Makefile will depend on the system's header files.
#
# Usually this is not a problem, because when building the target package,
# these header files will indeed be found in $(STAGING_DIR). However, some
# distro's add an extra header file to the system's perl. This header is
# also included in the generated Makefile, which makes the build fail
# because it doesn't exist in $(STAGING_DIR).
#
# As a work-around, explicitly create this header file in $(STAGING_DIR).
# It doesn't hurt to create it even if the system perl doesn't need it.
#
define PERL_ADD_CORE_H
	touch $(STAGING_DIR)/usr/lib/perl5/$(PERL_VERSION)/$(PERL_ARCHNAME)/CORE/patchlevel-debian.h
	touch $(STAGING_DIR)/usr/lib/perl5/$(PERL_VERSION)/$(PERL_ARCHNAME)/CORE/cc_runtime.h
endef

PERL_POST_INSTALL_STAGING_HOOKS += PERL_ADD_CORE_H

$(eval $(generic-package))

define PERL_FINALIZE_TARGET
	rm -rf $(TARGET_DIR)/usr/lib/perl5/$(PERL_VERSION)/pod
	rm -rf $(TARGET_DIR)/usr/lib/perl5/$(PERL_VERSION)/$(PERL_ARCHNAME)/CORE
	find $(TARGET_DIR)/usr/lib/perl5/ -name 'extralibs.ld' -print0 | xargs -0 rm -f
	find $(TARGET_DIR)/usr/lib/perl5/ -name '*.bs' -print0 | xargs -0 rm -f
	find $(TARGET_DIR)/usr/lib/perl5/ -name '.packlist' -print0 | xargs -0 rm -f
endef

TARGET_FINALIZE_HOOKS += PERL_FINALIZE_TARGET

