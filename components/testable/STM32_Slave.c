#include "STM32_comm.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "hal/spi_types.h"
#include "portmacro.h"
#include "stdio.h"
#include <string.h>

const char tag[] = "slave stm32";

typedef struct STM32_Slave_Context_t {
  SPI_config cfg;
  SemaphoreHandle_t ready_sem;    // Smeaphore readyy for signal
  spi_device_handle_t spi_handle; ///< SPI device handle
} STM32_Slave_Context_t;

static void cs_high(STM32_Slave_handle_t *ctx) {

  // ESP_LOGI(tag, "CS High %d", ((*ctx)->cfg.CS));
  gpio_set_level(((*ctx)->cfg.CS), 1);
}
static void cs_low(STM32_Slave_handle_t *ctx) {
  //  ESP_LOGI(tag, "CS Low %d", ((*ctx)->cfg.CS));
  gpio_set_level(((*ctx)->cfg.CS), 0);
}

esp_err_t STM32_Slave_Init(STM32_Slave_handle_t *ctx, SPI_config *cfg) {
  esp_err_t err = ESP_OK;

  *ctx = malloc(sizeof(STM32_Slave_Context_t));
  ESP_LOGE(tag,"###\n INIT SLAVE PIN ###\n");
  ESP_LOGE(tag,"SCLK Pin: %d\n",(*ctx)->cfg.SCK);
  ESP_LOGE(tag,"MOSI Pin: %d\n",(*ctx)->cfg.MOSI);
  ESP_LOGE(tag,"MISO Pin: %d\n",(*ctx)->cfg.MISO);
  ESP_LOGE(tag,"CS Pin: %d\n",(*ctx)->cfg.CS);
  ESP_LOGE(tag,"###\n END INIT SLAVE PIN ###\n");
  if (*ctx == NULL) {
    ESP_LOGE(tag, "khong the cap phat bo nho\n");
    return ESP_ERR_NO_MEM;
  }
  memcpy(&(*ctx)->cfg, cfg, sizeof(SPI_config));

  err = SPI_init_bus(&((*ctx)->cfg));

  if (err != ESP_OK){
    ESP_LOGE(tag, "Failed to initialize SPI bus: %s", esp_err_to_name(err));
    free(*ctx);
    return err;
  }
  ESP_LOGI(tag, "SPI bus initialized successfully\n"); 
  err = SPI_add_device(ctx);
  if (err != ESP_OK) {
    ESP_LOGE(tag, "Failed to add SPI device: %s", esp_err_to_name(err));
    spi_bus_free((*ctx)->cfg.host);
    free(*ctx);
    return err;
  }
  ESP_LOGI(tag, "SPI device added successfully\n");
  cs_high(ctx);
  return err;
}
esp_err_t SPI_init_bus(SPI_config *cfg, uint8_t max_transfer) {

  esp_err_t ret;
  ESP_LOGI(tag, "Initializing bus SPI...");
  gpio_config_t io_conf = {
      .mode = GPIO_MODE_OUTPUT,
      .pin_bit_mask = (1ULL << cfg->CS),
  };
  gpio_config(&io_conf);

  spi_bus_config_t buscfg = {.miso_io_num = cfg->MISO,
                             .mosi_io_num = cfg->MOSI,
                             .sclk_io_num = cfg->SCK,
                             .quadwp_io_num = -1,
                             .quadhd_io_num = -1};

  ret = spi_bus_initialize(cfg->host, &buscfg, SPI_DMA_CH_AUTO);
  return ret;
}
esp_err_t spi_add_device(STM32_Slave_handle_t *ctx, SPI_config *cfg) {
  esp_err_t err;
  spi_device_interface_config_t devcfg = {
      .command_bits = 0,
      .queue_size = 7,
      .spics_io_num = -1,
      .dummy_bits = 0,
      .clock_speed_hz = SPI_Frequency,
      .mode = 0,
  };
  err = spi_bus_add_device(cfg->host, &devcfg, &((*ctx)->spi_handle));
  return err;
}
void STM32_Begin_Get_Info(STM32_Slave_handle_t *ctx) {
  uint8_t tx[2] = {0x37, 0x80};
  uint8_t rx[2] = {0};
  spi_transaction_t trans = {
      .length = 8 * 2,
      .tx_buffer = tx,
      .rx_buffer = rx,
  };

  cs_low(&(*ctx));
  spi_device_transmit((*ctx)->spi_handle, &trans);
  cs_high(&(*ctx));
  ESP_LOGI(tag, "RX: %02X %02X", rx[0], rx[1]);
}
