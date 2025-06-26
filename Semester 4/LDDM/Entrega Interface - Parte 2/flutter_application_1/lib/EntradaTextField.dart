import 'package:flutter/material.dart';

class TextFieldPage extends StatefulWidget {
  @override
  _TextFieldPageState createState() => _TextFieldPageState();
}

class _TextFieldPageState extends State<TextFieldPage> {
  final TextEditingController _controller = TextEditingController();

  void _showText() {
    // Mostrar o texto digitado ou realizar alguma ação com ele
    print(_controller.text);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('TextField')),
      body: Container(
        padding: EdgeInsets.all(20.0),
        child: Column(
          children: <Widget>[
            TextField(
              controller: _controller,
              decoration: InputDecoration(labelText: 'Digite algo'),
            ),
            ElevatedButton(
              onPressed: _showText,
              child: Text('Mostrar Texto'),
            ),
          ],
        ),
      ),
    );
  }
}
