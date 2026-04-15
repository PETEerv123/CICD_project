#include "STM32_Slave.h"
#include "unity.h"

TEST_CASE("STM32 Slave Init  ", "[SPI]") {
    STM32_Slave_handle_t STM32_Handle; 
    // Arrange                                                                                                                                                                                                                                                                                                                                                                                                                                              
    SPI_config cfg = {
        .SCK = GPIO_NUM_18,
        .MOSI = GPIO_NUM_23,
        .MISO = GPIO_NUM_19,
        .CS = GPIO_NUM_5,
        .host = SPI2_HOST
    }
    
    esp_err_t err = STM32_Slave_Init(&STM32_Handle, &cfg);

    // Assert
    TEST_ASSERT_EQUAL_UINT8(ESP_OK, err);
}
TEST_CASE("STM32 Begin Get Info ", "[SPI]") {
    STM32_Slave_handle_t STM32_Handle; 
    esp_err_t err = ESP_OK;
    // Arrange                                                                                                                                                                                                                                                                                                                                                                                                                                              
    SPI_config cfg = {
        .SCK = GPIO_NUM_15,
        .MOSI = GPIO_NUM_23,
        .MISO = GPIO_NUM_19,
        .CS = GPIO_NUM_5,
        .host = SPI2_HOST
    }
    err = STM32_Slave_Init(&STM32_Handle, &cfg);
    err = STM32_Begin_Get_Info(&STM32_Handle);

    // Assert
    TEST_ASSERT_EQUAL_UINT8(ESP_OK, err);
}
TEST_CASE("SPI Add Device ", "[SPI]") {
    STM32_Slave_handle_t STM32_Handle; 
    // Arrange                                                                                                                                                                                                                                                                                                                                                                                                                                              
    SPI_config cfg = {
        .SCK = GPIO_NUM_18,
        .MOSI = GPIO_NUM_23,
        .MISO = GPIO_NUM_19,
        .CS = GPIO_NUM_5,
        .host = SPI2_HOST
    }
    
 
   esp_err_t err = SPI_add_device(&STM32_Handle, &cfg);

    // Assert
    TEST_ASSERT_EQUAL_UINT8(ESP_OK, err);
}