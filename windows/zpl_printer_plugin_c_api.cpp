#include "include/zpl_printer/zpl_printer_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "zpl_printer_plugin.h"

void ZplPrinterPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  zpl_printer::ZplPrinterPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
