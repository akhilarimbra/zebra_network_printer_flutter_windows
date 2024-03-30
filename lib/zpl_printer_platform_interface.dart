import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'zpl_printer_method_channel.dart';

abstract class ZplPrinterPlatform extends PlatformInterface {
  /// Constructs a ZplPrinterPlatform.
  ZplPrinterPlatform() : super(token: _token);

  static final Object _token = Object();

  static ZplPrinterPlatform _instance = MethodChannelZplPrinter();

  /// The default instance of [ZplPrinterPlatform] to use.
  ///
  /// Defaults to [MethodChannelZplPrinter].
  static ZplPrinterPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [ZplPrinterPlatform] when
  /// they register themselves.
  static set instance(ZplPrinterPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}
