import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'SharedPreferences Demo',
      home: MyHomePage(),
    );
  }
}

class MyHomePage extends StatefulWidget {
  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  final TextEditingController _controller = TextEditingController();
  String _textSalvo = 'Sem Valor';

  @override
  void initState() {
    super.initState();
    _recuperarDados();
  }

  Future<void> _salvarDados() async {
    final prefs = await SharedPreferences.getInstance();
    await prefs.setString('texto', _controller.text);
  }

  Future<void> _recuperarDados() async {
    final prefs = await SharedPreferences.getInstance();
    String? valorRecuperado = prefs.getString('texto');
    setState(() {
      _textSalvo = valorRecuperado ?? 'Sem Valor';
    });
  }

  Future<void> _removerDados() async {
    final prefs = await SharedPreferences.getInstance();
    await prefs.remove('texto');
    setState(() {
      _textSalvo = 'Sem Valor';
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('SharedPreferences Demo'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            TextField(
              controller: _controller,
              decoration: InputDecoration(labelText: 'Insira algo'),
            ),
            SizedBox(height: 20),
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                ElevatedButton(
                  onPressed: _salvarDados,
                  child: Text('Salvar'),
                ),
                ElevatedButton(
                  onPressed: _recuperarDados,
                  child: Text('Recuperar'),
                ),
                ElevatedButton(
                  onPressed: _removerDados,
                  child: Text('Remover'),
                ),
              ],
            ),
            SizedBox(height: 20),
            Text(_textSalvo, style: TextStyle(fontSize: 18)),
          ],
        ),
      ),
    );
  }
}
