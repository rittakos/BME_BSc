import 'package:flutter/material.dart';
import 'package:tictactoe/model/logic.dart';

import 'game.dart';

class HomePage extends StatefulWidget {
  HomePage({Key key, this.title = ""}) : super(key: key);

  final String title;

  @override
  _HomePageState createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  @override
  Widget build(BuildContext context) {

    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Column(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        children: <Widget>[
          Text("Tic Tac Toe", style: TextStyle(fontSize: 40),),
          Center(
            child: ButtonTheme(
              minWidth: 200,
              height: 80,
              child: ElevatedButton(
                style: ButtonStyle(
                  overlayColor: MaterialStateProperty.all<Color>(Colors.green),
                ),
                onPressed: () {
                  Logic.alone = true;
                  Navigator.push(
                      context,
                      MaterialPageRoute(builder: (context) => GamePage(widget.title))
                  );
                },
                child: Text("I'm alone!", style: TextStyle(fontSize: 30, fontWeight: FontWeight.bold),),
              ),
            ),
          ),
          Center(
            child: ButtonTheme(
              minWidth: 200,
              height: 80,
              child: ElevatedButton(
                style: ButtonStyle(
                  overlayColor: MaterialStateProperty.all<Color>(Colors.green),
                ),
                onPressed: () {
                  Logic.alone = false;
                  Navigator.push(
                      context,
                      MaterialPageRoute(builder: (context) => GamePage(widget.title))
                  );
                },
                child: Text("I'm with a friend!", style: TextStyle(fontSize: 30, fontWeight: FontWeight.bold),),
              ),
            ),
          ),
        ],
      ),
    );
  }
}