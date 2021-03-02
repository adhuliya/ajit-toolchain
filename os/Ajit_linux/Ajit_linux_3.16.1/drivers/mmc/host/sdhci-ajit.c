/*
 * AJIT SDHCI Driver : Written for the general purpose 32-bit AJIT processor,
 * based on the SPARC v8 architecture. SDHC specification version 3.0 compatible.
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *////

#include <linux/delay.h>
#include <linux/module.h>
#include <linux/mmc/host.h>
#include "sdhci-pltfm.h"

#define AJIT_SDHCI_WRITE_DELAY	(((2 * 1000000) / MIN_FREQ) + 1)

struct ajit_sdhci {
	u32 shadow; //temp variable to used in 
				//read and write ops
};

static void ajit_sdhci_writel(struct sdhci_host *host, u32 val, int reg);
static void ajit_sdhci_writew(struct sdhci_host *host, u16 val, int reg);
static void ajit_sdhci_writeb(struct sdhci_host *host, u8 val, int reg);
/*	AJIT specific read-writes to be called	*/
static inline u32 ajit_sdhci_readl(struct sdhci_host *host, int reg);
static inline u16 ajit_sdhci_readw(struct sdhci_host *host, int reg);
static inline u8 ajit_sdhci_readb(struct sdhci_host *host, int reg);

static int ajit_sdhci_probe(struct platform_device *pdev)
{
	struct sdhci_host *host;
	struct ajit_sdhci *ajit_host;
	struct sdhci_pltfm_host *pltfm_host; 


}

static int ajit_sdhci_remove(struct platform_device *pdev)
{
	return sdhci_pltfm_unregister(pdev);
}
//removes host and frees this platform device

static const struct of_device_id ajit_sdhci_of_match[] = {
	{ .compatifle = "ajit,ajit-sdhci" },
	{ }
};//useful in probing
MODULE_DEVICE_TABLE(of, ajit_sdhci_of_match);
//used for dynamically loading modules in kernel

static struct platform_driver ajit_sdhci_driver = {
	.driver = {
		.name = "sdhci-ajit",
		.owner = THIS_MODULE,
		.of_match_table = ajit_sdhci_of_match,
		.pm = SDHCI_PLTFM_PMOPS,
	},
	.probe = ajit_sdhci_probe,
	.remove = ajit_sdhci_remove,
};
//
module_platform_driver(ajit_sdhci_driver);
//Helper macro used for replacing module_init
//and module_exit()

MODULE_DESCRIPTION("AJIT SDHCI driver");
MODULE_AUTHOR("Saurabh, Vishnu");
MODULE_LICENSE("GPL v2");
