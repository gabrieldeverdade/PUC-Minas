import 'package:flutter/material.dart';

class RadioButtonPage extends StatefulWidget {
  @override
  _RadioButtonPageState createState() => _RadioButtonPageState();
}

class _RadioButtonPageState extends State<RadioButtonPage> {
  String _selectedRadioValue = 'Opção 1';

  void _setSelectedRadio(String? value) {
    setState(() {
      _selectedRadioValue = value!;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('RadioButton')),
      body: Column(
        children: <Widget>[
          RadioListTile<String>(
            title: const Text('Opção 1'),
            value: 'Opção 1',
            groupValue: _selectedRadioValue,
            onChanged: _setSelectedRadio,
          ),
          RadioListTile<String>(
            title: const Text('Opção 2'),
            value: 'Opção 2',
            groupValue: _selectedRadioValue,
            onChanged: _setSelectedRadio,
          ),
        ],
      ),
    );
  }
}
