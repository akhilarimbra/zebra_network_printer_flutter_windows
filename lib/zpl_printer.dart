import 'package:flutter/services.dart';

class ZplPrinter {
  static const MethodChannel _channel = MethodChannel('zpl_printer');

  static Future<void> sendZPLToNetworkPrinter(
    String ipAddress,
    int port,
    String zplString,
  ) async {
    try {
      await _channel.invokeMethod(
        'sendZpl',
        {
          'ipAddress': ipAddress,
          'port': port,
          'zplString': zplString,
        },
      );
    } on PlatformException catch (e) {
      // Handle errors appropriately
      print("Failed to send ZPL: ${e.message}");
    }
  }
}
