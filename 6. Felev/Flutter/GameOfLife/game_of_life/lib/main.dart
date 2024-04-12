import 'package:flutter/material.dart';

import 'data/strings.dart';
import 'package:game_of_life/home.dart';


void main() {
  runApp(GameOfLifeApp());
}

class GameOfLifeApp extends StatelessWidget
{
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: Strings.title,
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: HomePage(title: Strings.title),
    );
  }
}


