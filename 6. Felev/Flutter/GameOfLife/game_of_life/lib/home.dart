import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:game_of_life/data/strings.dart';

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
          Center(
            child: ButtonTheme(
              child: ElevatedButton(
                child: Text(
                  Strings.start,
                ),
                onPressed: () {
                  Navigator.push(
                      context,
                      MaterialPageRoute(builder: (context) => GamePage(widget.title))
                  );
                },
              ),
            ),
          ),
        ],
      ),
    );
  }
}