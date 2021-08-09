/* Housecarl
 * Open Source home security IP cam
 */
#define VERSION "1.0"

// Personal configuration
#include "configuration.h"

// EEPROM for resolution configuration save
#include <EEPROM.h>

// Select camera model
//#define CAMERA_MODEL_WROVER_KIT
#define CAMERA_MODEL_AI_THINKER

// Camera pins for selected camera model
#include "camera_pins.h"

// ESP32 Camera + Wifi
#include "esp_camera.h"
#include <WiFi.h>

// Include for brownout detector deactivation
// #include "soc/soc.h"
// #include "soc/rtc_cntl_reg.h"

void startCameraServer();

void setup() {
  // Disable brownout detector
  // WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  
  /*
   * FRAMESIZE_QVGA (320 x 240)
   * FRAMESIZE_CIF (352 x 288)
   * FRAMESIZE_VGA (640 x 480)
   * FRAMESIZE_SVGA (800 x 600)
   * FRAMESIZE_XGA (1024 x 768)
   * FRAMESIZE_SXGA (1280 x 1024)
   * FRAMESIZE_UXGA (1600 x 1200)
   */
  
  //init with high specs to pre-allocate larger buffers
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  
  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();

  // restore resolution and flip
  byte framesize, fliph, flipv;
  EEPROM.begin(8);
  framesize = EEPROM.read(0);
  fliph = EEPROM.read(1);
  flipv = EEPROM.read(2);
  s->set_framesize(s, (framesize_t)framesize);
  s->set_hmirror(s, (int)fliph);
  s->set_vflip(s, (int)flipv);
  s->set_dcw(s, 0);
  
  WiFi.config(ip, gateway, subnet, primaryDNS, secondaryDNS);
  WiFi.begin(ssid, password);
  WiFi.setHostname(hostname);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
  Serial.print("Hostname ");
  Serial.println(WiFi.getHostname());
}

void loop() {
  delay(1000);

  // restart after 24h
  static int i = 0;
  if(++i > 86400)
    ESP.restart();
}
