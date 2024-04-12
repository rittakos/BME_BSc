"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
Object.defineProperty(exports, "__esModule", { value: true });
var core_1 = require("@angular/core");
var _ = require("lodash");
var Rx_1 = require("rxjs/Rx");
var http_1 = require("@angular/common/http");
var CharacterService = (function () {
    function CharacterService(http) {
        this.http = http;
        this.apiURL = "https://www.anapioficeandfire.com/api";
        this.load();
    }
    //public getcharacter(): any {
    //return this.http.get<Character>(this.apiURL + '/characters/583');
    //}
    CharacterService.prototype.getCards = function (options) {
        this.characters = [{ id: 1, name: "ddddd" }];
        var pageSize = (options && options.pageSize) || 5;
        var page = (options && options.page) || 0;
        var searchTerm = (options && options.searchTerm) || '';
        var allResults = searchTerm.length
            ? _.filter(this.characters, function (c) { return _.find([c.name], function (e) { return e && e.toLowerCase().indexOf(searchTerm.toLowerCase()) > -1; }) !== undefined; })
            : this.characters;
        return Rx_1.Observable.of(_.slice(allResults, pageSize * page, pageSize * (page + 1)))
            .map(function (results) { return ({
            allResults: allResults.length, results: results, page: page, pageSize: pageSize, searchTerm: searchTerm
        }); })
            .delay(200);
    };
    CharacterService.prototype.addOrUpdateCard = function (card) {
        if (card.id) {
            for (var i = 0; i < this.characters.length; i++) {
                if (this.characters[i].id == card.id) {
                    this.characters[i] = card;
                    break;
                }
            }
        }
        else {
            var maxCard = _.maxBy(this.characters, function (c) { return c.id; });
            card.id = ((maxCard && maxCard.id) || 0) + 1;
            this.characters.push(card);
        }
        return this.save();
    };
    CharacterService.prototype.deleteCard = function (card) {
        if (typeof card === 'number')
            this.characters = _.filter(this.characters, function (c) { return c.id !== card; });
        else if (typeof card === 'object')
            this.characters = _.filter(this.characters, function (c) { return c.id !== card.id; });
        return this.save();
    };
    CharacterService.prototype.load = function () {
        this.characters = JSON.parse(localStorage.getItem('cards')) || [
            { id: 1, name: "fasdfsa" },
        ];
        this.save();
    };
    CharacterService.prototype.save = function () {
        localStorage.setItem('cards', JSON.stringify(this.characters));
        return Rx_1.Observable.timer(200);
    };
    return CharacterService;
}());
CharacterService = __decorate([
    core_1.Injectable(),
    __metadata("design:paramtypes", [http_1.HttpClient])
], CharacterService);
exports.CharacterService = CharacterService;
//# sourceMappingURL=character.service.js.map