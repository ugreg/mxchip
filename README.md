# Environment

Make sure you have an Azure IoT SDK to compile successfully. For example I used an [Arduino](https://www.arduino.cc/en/main/software#download) development environment with the following Arduino Libraries: [AzureIoTUtility](https://github.com/Azure/azure-iot-arduino-utility), [AzureIoTProtocol_MQTT](https://github.com/Azure/azure-iot-arduino-protocol-mqtt), [AzureIoTProtocol_HTTP](https://github.com/Azure/azure-iot-arduino-protocol-http) all at version `1.0.45`.

It's recomened you use [Visual Studio Code extension for Arduino](https://github.com/Microsoft/vscode-arduino), install it from [here](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino). You can also use [Azure IoT Workbench](https://microsoft.github.io/azure-iot-developer-kit/docs/get-started/#install-development-environment)
or [iotz](https://github.com/Azure/iotz) to compile this sample.

# Run

Select the MXCHIP board type

VS Code by `ctrl + shift + p`

Then choose task `Arduino: Upload`

# References
- [Graphics API](https://github.com/tobybrad/mxchip_iotdevkit_gfx)
