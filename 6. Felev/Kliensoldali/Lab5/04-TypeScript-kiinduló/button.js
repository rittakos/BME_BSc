"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var ResetButton = (function () {
    function ResetButton(element, board) {
        var _this = this;
        this.element = element;
        this.board = board;
        element.click(function () { return _this.click(); });
    }
    ResetButton.prototype.click = function () {
        alert("reset");
        this.board.restartGame();
        //this.element.click;
    };
    return ResetButton;
}());
exports.ResetButton = ResetButton;
var ClearButton = (function () {
    function ClearButton(element, board) {
        var _this = this;
        this.element = element;
        element.click(function () { return _this.click(); });
    }
    ClearButton.prototype.click = function () {
        alert("clear");
        this.element.click;
    };
    return ClearButton;
}());
exports.ClearButton = ClearButton;
//# sourceMappingURL=data:application/json;base64,eyJ2ZXJzaW9uIjozLCJmaWxlIjoiYnV0dG9uLmpzIiwic291cmNlUm9vdCI6IiIsInNvdXJjZXMiOlsiYnV0dG9uLnRzIl0sIm5hbWVzIjpbXSwibWFwcGluZ3MiOiI7O0FBRUE7SUFDSSxxQkFBbUIsT0FBZSxFQUFTLEtBQWdCO1FBQTNELGlCQUdDO1FBSGtCLFlBQU8sR0FBUCxPQUFPLENBQVE7UUFBUyxVQUFLLEdBQUwsS0FBSyxDQUFXO1FBRXZELE9BQU8sQ0FBQyxLQUFLLENBQUMsY0FBTSxPQUFBLEtBQUksQ0FBQyxLQUFLLEVBQUUsRUFBWixDQUFZLENBQUMsQ0FBQztJQUN0QyxDQUFDO0lBQ0QsMkJBQUssR0FBTDtRQUNJLEtBQUssQ0FBQyxPQUFPLENBQUMsQ0FBQztRQUNmLElBQUksQ0FBQyxLQUFLLENBQUMsV0FBVyxFQUFFLENBQUM7UUFDekIscUJBQXFCO0lBQ3pCLENBQUM7SUFDTCxrQkFBQztBQUFELENBQUMsQUFWRCxJQVVDO0FBVlksa0NBQVc7QUFZeEI7SUFDSSxxQkFBbUIsT0FBZSxFQUFFLEtBQWdCO1FBQXBELGlCQUdDO1FBSGtCLFlBQU8sR0FBUCxPQUFPLENBQVE7UUFFOUIsT0FBTyxDQUFDLEtBQUssQ0FBQyxjQUFNLE9BQUEsS0FBSSxDQUFDLEtBQUssRUFBRSxFQUFaLENBQVksQ0FBQyxDQUFDO0lBQ3RDLENBQUM7SUFDRCwyQkFBSyxHQUFMO1FBQ0ksS0FBSyxDQUFDLE9BQU8sQ0FBQyxDQUFDO1FBQ2YsSUFBSSxDQUFDLE9BQU8sQ0FBQyxLQUFLLENBQUM7SUFDdkIsQ0FBQztJQUNMLGtCQUFDO0FBQUQsQ0FBQyxBQVRELElBU0M7QUFUWSxrQ0FBVyJ9