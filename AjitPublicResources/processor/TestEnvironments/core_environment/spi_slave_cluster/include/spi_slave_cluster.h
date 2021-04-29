#ifndef spi_slave_cluster__
#define spi_slave_cluster__

#define SPI_SLAVE_CLUSTER_NORMAL_MODE      0
#define SPI_SLAVE_CLUSTER_SOCKET_MODE      0x1

void setSpiSlaveClusterMode(uint8_t spi_slave_cluster_mode);
void setSpiSlaveClusterInSocketMode();
void startSpiSlaveClusterThreads();

#endif

