'use strict';

var clientFromConnectionString = require('azure-iot-device-mqtt').clientFromConnectionString;
var Message = require('azure-iot-device').Message;
var ConnectionString = require('azure-iot-device').ConnectionString;

var connectionString = '{device connection string}';
var targetTemperature = 0;
var client = clientFromConnectionString(connectionString);

