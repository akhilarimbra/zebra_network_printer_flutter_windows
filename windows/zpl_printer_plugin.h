#ifndef FLUTTER_PLUGIN_ZPL_PRINTER_PLUGIN_H_
#define FLUTTER_PLUGIN_ZPL_PRINTER_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace zpl_printer {

class ZplPrinterPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  ZplPrinterPlugin();

  virtual ~ZplPrinterPlugin();

  // Disallow copy and assign.
  ZplPrinterPlugin(const ZplPrinterPlugin&) = delete;
  ZplPrinterPlugin& operator=(const ZplPrinterPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace zpl_printer

#endif  // FLUTTER_PLUGIN_ZPL_PRINTER_PLUGIN_H_
