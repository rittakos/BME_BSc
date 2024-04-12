import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

import 'board.dart';
import 'gameOfLife.dart';

class GamePage extends StatefulWidget {

  final String title;

  GamePage(this.title);

  @override
  _GamePageState createState() => _GamePageState();
}

class _GamePageState extends State<GamePage> {
  final _game = GameOfLife();

  Size _fieldSize;

  @override
  void initState() {
    super.initState();

    _game.reset();
  }

  void _pauseClick() {
    setState(() {
      _game.pauseClick();
    });
  }

  @override
  Widget build(BuildContext contGameOfLifeext) {
    _fieldSize = Size(
        MediaQuery.of(context).size.width / GameOfLife.columns,
        (MediaQuery.of(context).size.height - 80) / (GameOfLife.filedsNum / GameOfLife.columns));

    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: StreamBuilder<double>(
        stream: _game.stateController.stream,
        builder: (context, snapshot) {
          return Board(
            _game.board,
            GameOfLife.columns,
            fieldSize: _fieldSize,
          );
        },
      ),
      floatingActionButton: FloatingActionButton(
        child: _game.paused ? Icon(Icons.play_arrow) : Icon(Icons.pause),
        onPressed: _pauseClick,
      ),
    );
  }
}