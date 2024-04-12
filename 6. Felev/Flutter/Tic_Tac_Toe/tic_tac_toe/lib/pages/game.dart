import 'package:flutter/material.dart';
import 'package:tic_tac_toe/model/logic.dart';
import 'package:tic_tac_toe/model/board.dart';
import 'package:tic_tac_toe/model/coord.dart';
import 'package:tic_tac_toe/model/player.dart';
import 'package:tic_tac_toe/model/controller.dart';

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

    if(winner == Logic.player)
        title = "Congratulations!";
    else if(winner == Logic.computer)
        title = "Game Over!";
    else
        title = "Draw!";

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

      if (_currentPlayer == Logic.player) {
        _currentPlayer = Logic.computer;
        _controller.step(board);
      } else {
        _currentPlayer = Logic.player;
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
      body: Column(
        children: <Widget>[
          Padding(
            padding: const EdgeInsets.all(60),
            child: Text("Click somwhere!", style: TextStyle(fontSize: 25),),
          ),
           Expanded(
             child: GridView.count(
                      crossAxisCount: 3,
                      children: List.generate(9, (idx) {
                        Coord c = new Coord(idx % 3, idx ~/ 3);
                        return Cell(coord: c, tap: _step, player: board.getPlayer(c));
                      }),
                  ),
              ),
        ],
      ),
    );
  }
}