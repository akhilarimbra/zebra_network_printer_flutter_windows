import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'zpl_printer_platform_interface.dart';

/// An implementation of [ZplPrinterPlatform] that uses method channels.
class MethodChannelZplPrinter extends ZplPrinterPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('zpl_printer');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }
}
