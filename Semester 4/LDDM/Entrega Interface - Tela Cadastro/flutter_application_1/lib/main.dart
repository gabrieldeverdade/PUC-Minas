import 'package:flutter_application_1/pages/login.pages.dart';
import 'package:flutter/material.dart';
import 'package:flutter_application_1/pages/signup.page.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'login.io',
      theme: ThemeData(primarySwatch: Colors.deepPurple),
      home: SignupPage(),
    );
  }
}