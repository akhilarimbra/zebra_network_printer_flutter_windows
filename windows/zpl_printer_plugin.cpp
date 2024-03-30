#include "include/flutter/method_channel.h"
#include "include/flutter/plugin_registrar_windows.h"
#include "include/flutter/standard_method_codec.h"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

namespace zpl_printer
{

  // Error Handling (you can expand on this)
  inline bool handleSocketError()
  {
    int error = WSAGetLastError();
    std::cerr << "Socket error: " << error << std::endl;
    return false;
  }

  // Method to establish a raw TCP connection and send ZPL code
  void SendZPL(flutter::MethodCall<> const &call, std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result)
  {
    // ... (Argument extraction - same as in previous example)

    // Winsock initialization
    WSADATA wsaData;
    int winsockResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (winsockResult != 0)
    {
      result->Error("WSAStartup failed", "Winsock initialization error");
      return;
    }

    // Create a socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
      handleSocketError();
      result->Error("Socket creation failed", "Error creating socket");
      return;
    }

    // Create address structure
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(portNum);
    inet_pton(AF_INET, ipAddrStr.c_str(), &addr.sin_addr);

    // Connect to the printer
    int connectResult = connect(sock, (sockaddr *)&addr, sizeof(addr));
    if (connectResult == SOCKET_ERROR)
    {
      handleSocketError();
      closesocket(sock);
      result->Error("Connection failed", "Error connecting to printer");
      return;
    }

    // Send the ZPL data
    int sendResult = send(sock, zplStr.c_str(), zplStr.length(), 0);
    if (sendResult == SOCKET_ERROR)
    {
      handleSocketError();
      closesocket(sock);
      result->Error("Send failed", "Error sending ZPL data");
      return;
    }

    // Close the socket
    closesocket(sock);
    WSACleanup();

    // Indicate success
    result->Success();
  }

  class ZplPrinterPlugin : public flutter::Plugin
  {
  public:
    static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

    ZplPrinterPlugin();

    virtual ~ZplPrinterPlugin();

  private:
    void HandleMethodCall(
        const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
  };

  void ZplPrinterPlugin::RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar)
  {
    auto channel = std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
        registrar->messenger(), "zpl_printer",
        &flutter::StandardMethodCodec::GetInstance());

    auto plugin = std::make_unique<ZplPrinterPlugin>();

    channel->SetMethodCallHandler(
        [plugin_pointer = plugin.get()](const auto &call, auto result)
        {
          plugin_pointer->HandleMethodCall(call, std::move(result));
        });

    registrar->AddPlugin(std::move(plugin));
  }

  ZplPrinterPlugin::ZplPrinterPlugin() {}

  ZplPrinterPlugin::~ZplPrinterPlugin() {}

  void ZplPrinterPlugin::HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result)
  {
    if (method_call.method_name().compare("sendZpl") == 0)
    {
      SendZPL(method_call, std::move(result));
    }
    else
    {
      result->NotImplemented();
    }
  }

} // namespace zpl_printer

// Entry point
void ZplPrinterPluginRegisterWithRegistrar(FlutterDesktopPluginRegistrarRef registrar)
{
  zpl_printer::ZplPrinterPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
