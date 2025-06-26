// Arquivo: StatelessWidgetPage.dart
import 'package:flutter/material.dart';

class StatelessWidgetPage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('Stateless Widget Page')),
      body: Center(child: Text('This is a Stateless Widget')),
    );
  }
}
