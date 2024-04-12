import 'package:flutter/material.dart';
import 'package:tic_tac_toe/pages/home.dart';


void main() => runApp(TicTacToe());


class TicTacToe extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Tic Tac Toe',
      theme: ThemeData(
        primarySwatch: Colors.pink,
      ),
      home: HomePage(title: 'Game'),
    );
  }
}
