// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#define SERIAL_VERBOSE_LOGGING_ENABLED 1
#include "src/iotc/iotc.h"
#include "src/iotc/common/string_buffer.h"
#include <EEPROMInterface.h>
#include "AZ3166WiFi.h"

static IOTContext context = NULL;