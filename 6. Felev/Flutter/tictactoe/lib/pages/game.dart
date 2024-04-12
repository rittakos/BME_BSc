import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

import 'package:tictactoe/model/board.dart';
import 'package:tictactoe/model/controller.dart';
import 'package:tictactoe/model/coord.dart';
import 'package:tictactoe/model/logic.dart';
import 'package:tictactoe/model/player.dart';

import '../model/cell.dart';

class GamePage extends StatefulWidget {

  final String title;

  GamePage(this.title);

  @override
  GamePageState createState() => GamePageState();
}

class GamePageState extends State<GamePage> {

  Board board = new Board();
  Player _currentPlayer;

  Controller _controller;

  GamePageState() {
    this._controller = Controller(_step, _end);
  }

  void _end(Player winner) {

    String title;

    if(Logic.alone) {
      if (winner == Logic.player)
        title = "Congratulations!";
      else if (winner == Logic.computer)
        title = "Game Over!";
      else
        title = "Draw!";
    }else{
      if (winner == null)
        title = "Draw!";
      else
        title = winner.symbol + " won!";
    }

    showDialog(
        context: context,
        builder: (BuildContext context) {
          return AlertDialog(
            title: Text(title),
            actions: <Widget>[
              new TextButton(
                  onPressed: () {
                    setState(() {
                      reset();
                      Navigator.of(context).pop();
                    });
                  },
                  child: Text("Restart"))
            ],
          );
        });
  }


  void _step(Coord coord) {
    setState(() {

      board.setPlayer(coord, _currentPlayer);
      if(Logic.alone) {
        if (_currentPlayer == Logic.player) {
          _currentPlayer = Logic.computer;
          _controller.step(board);
        } else {
          _currentPlayer = Logic.player;
        }
      }else
      {
        if (_currentPlayer == Logic.player) {
          _currentPlayer = Logic.computer;
        } else {
          _currentPlayer = Logic.player;
        }
        _controller.step(board);
      }
    });
  }

  @override
  void initState() {
    super.initState();
    reset();
  }

  void reset() {
    _currentPlayer = Logic.player;
    board.init();
  }

  @override
  Widget build(BuildContext context) {

    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child:  Column(
          children: <Widget>[
            Padding(
              padding:  EdgeInsets.all(MediaQuery.of(context).size.height * 0.1),
              child: Text("Click somwhere!", style: TextStyle(fontSize: 25),),
            ),
            Expanded(
              child: new Container(
                alignment: Alignment.center,
                constraints: BoxConstraints(minWidth: 0, maxWidth: (MediaQuery.of(context).size.height * 0.9)/3),
                child: GridView.count(
                  crossAxisCount: 3,
                  children: List.generate(9, (idx) {
                    Coord c = new Coord(idx % 3, idx ~/ 3);
                    return Cell(coord: c, tap: _step, player: board.getPlayer(c));
                  }),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}