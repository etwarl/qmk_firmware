#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

// place overrides here
#undef BLE_NUS_MAX_INTERVAL
#undef BLE_NUS_MIN_INTERVAL

#define BLE_NUS_MIN_INTERVAL 20
#define BLE_NUS_MAX_INTERVAL 40
#define BLE_HID_MAX_INTERVAL 80
#define BLE_HID_SLAVE_LATENCY 10

#endif /* CONFIG_USER_H */
