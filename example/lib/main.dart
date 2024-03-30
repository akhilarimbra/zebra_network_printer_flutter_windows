import 'package:flutter/material.dart';
import 'package:zpl_printer/zpl_printer.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  final _formKey = GlobalKey<FormState>();
  final _ipAddressController = TextEditingController();
  final _portController = TextEditingController();
  final _zplTextAreaController = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("ZPL Printer Settings"),
      ),
      body: SingleChildScrollView(
        // To prevent overflow in smaller screens
        padding: const EdgeInsets.all(16.0),
        child: Form(
          key: _formKey,
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              TextFormField(
                controller: _ipAddressController,
                decoration: const InputDecoration(
                  labelText: 'IP Address',
                ),
                validator: (value) {
                  // Add IP address validation logic here if needed
                  if (value == null || value.isEmpty) {
                    return 'Please enter an IP address';
                  }
                  return null;
                },
              ),
              const SizedBox(height: 16),
              TextFormField(
                controller: _portController,
                keyboardType: TextInputType.number,
                decoration: const InputDecoration(
                  labelText: 'Port',
                ),
                validator: (value) {
                  // Add port number validation logic here if needed
                  if (value == null || value.isEmpty) {
                    return 'Please enter a port number';
                  }
                  return null;
                },
              ),
              const SizedBox(height: 16),
              TextFormField(
                controller: _zplTextAreaController,
                decoration: const InputDecoration(
                  labelText: 'ZPL Code',
                ),
                keyboardType: TextInputType.multiline,
                maxLines: 5,
              ),
              const SizedBox(height: 32),
              ElevatedButton(
                onPressed: () {
                  if (_formKey.currentState!.validate()) {
                    // Extract form data:
                    String ipAddress = _ipAddressController.text;
                    int port = int.parse(_portController.text);
                    String zplCode = _zplTextAreaController.text;

                    // Process the ZPL data with your plugin
                    // Example using the 'ZplPrinter' class from the previous examples
                    ZplPrinter.sendZPLToNetworkPrinter(
                        ipAddress, port, zplCode);
                  }
                },
                child: const Text('Send ZPL'),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
