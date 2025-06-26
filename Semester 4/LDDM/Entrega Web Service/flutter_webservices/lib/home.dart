import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

class Home extends StatefulWidget {
  const Home({super.key});

  @override
  _HomeState createState() => _HomeState();
}

class _HomeState extends State<Home> {
  String _resultado = "Aguardando dados..."; 
  final TextEditingController _controllerCity = TextEditingController();
  final TextEditingController _controllerState = TextEditingController();
  final TextEditingController _controllerCountry = TextEditingController();

  // Função assíncrona que recupera os dados de qualidade do ar
  _recuperaQualidadeAr() async {
    String city = _controllerCity.text;
    String state = _controllerState.text;
    String country = _controllerCountry.text;
    String url = "https://api.api-ninjas.com/v1/airquality?city=$city";
    
    if (state.isNotEmpty && country.isEmpty) {
      url += "&state=$state";
    }
    if (country.isNotEmpty) {
      url += "&country=$country";
    }

    var uri = Uri.parse(url);
    http.Response resposta = await http.get(uri, headers: {
      "X-Api-Key": "E6K0GIi5iZ+PzoQqKBm5Og==73wesEWBoUyHSUPz"
    });

    if (resposta.statusCode == 200) {
      Map<String, dynamic> retorno = json.decode(resposta.body);
      String resultado = "Qualidade do Ar Detalhada:\n\n";
      resultado += "CO - Concentração: ${retorno['CO']['concentration']} μg/m³, AQI: ${retorno['CO']['aqi']}\n";
      resultado += "NO2 - Concentração: ${retorno['NO2']['concentration']} μg/m³, AQI: ${retorno['NO2']['aqi']}\n";
      resultado += "O3 - Concentração: ${retorno['O3']['concentration']} μg/m³, AQI: ${retorno['O3']['aqi']}\n";
      resultado += "SO2 - Concentração: ${retorno['SO2']['concentration']} μg/m³, AQI: ${retorno['SO2']['aqi']}\n";
      resultado += "PM2.5 - Concentração: ${retorno['PM2.5']['concentration']} μg/m³, AQI: ${retorno['PM2.5']['aqi']}\n";
      resultado += "PM10 - Concentração: ${retorno['PM10']['concentration']} μg/m³, AQI: ${retorno['PM10']['aqi']}\n";
      resultado += "\nAQI Geral: ${retorno['overall_aqi']}";

      setState(() {
        _resultado = resultado;
      });
    } else {
      setState(() {
        _resultado = "Falha ao obter dados! Status code: ${resposta.statusCode}";
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Qualidade do Ar"),
      ),
      body: Container(
        padding: const EdgeInsets.all(40),
        child: Column(
          children: <Widget>[
            TextField(
              decoration: const InputDecoration(
                labelText: "Cidade:",
              ),
              controller: _controllerCity,
            ),
            TextField(
              decoration: const InputDecoration(
                labelText: "Estado (Opcional):",
              ),
              controller: _controllerState,
            ),
            TextField(
              decoration: const InputDecoration(
                labelText: "País (Opcional):",
              ),
              controller: _controllerCountry,
            ),
            const SizedBox(height: 20),
            ElevatedButton(
              onPressed: _recuperaQualidadeAr,
              child: const Text("Consultar Qualidade do Ar"),
            ),
            const SizedBox(height: 20),
            SingleChildScrollView(
              child: Text(_resultado, style: TextStyle(fontFamily: 'Monospace')),
            ),
          ],
        ),
      ),
    );
  }
}
