"use strict";
var __assign = (this && this.__assign) || Object.assign || function(t) {
    for (var s, i = 1, n = arguments.length; i < n; i++) {
        s = arguments[i];
        for (var p in s) if (Object.prototype.hasOwnProperty.call(s, p))
            t[p] = s[p];
    }
    return t;
};
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
var character_service_1 = require("../../services/character.service");
var house_service_1 = require("../../services/house.service");
var _ = require("lodash");
var CharacterPageComponent = (function () {
    function CharacterPageComponent(cardService, companyService) {
        this.cardService = cardService;
        this.companyService = companyService;
        this.editing = false;
        this.currentPage = 0;
        this.maxPages = 0;
        this.searchTerm = "";
        console.log("asfsadf");
    }
    CharacterPageComponent.prototype.ngOnInit = function () {
        var _this = this;
        //alert(this.cardService.getcharacter().name);
        this.getCards();
        this.companyService.getCompanies().subscribe(function (cmp) { return _this.companies = cmp; });
    };
    CharacterPageComponent.prototype.editCard = function () {
        this.editing = true;
        this.originalCard = this.selectedCard;
        this.selectedCard = __assign({}, this.originalCard); // make a copy of the object
    };
    CharacterPageComponent.prototype.saveCard = function (card) {
        var _this = this;
        this.cardService.addOrUpdateCard(card)
            .subscribe(function () {
            _this.editing = false;
            _this.getCards();
            _this.selectedCard = undefined;
            _this.originalCard = undefined;
        });
    };
    CharacterPageComponent.prototype.cancel = function () {
        this.editing = false;
        this.selectedCard = this.originalCard;
        this.originalCard = undefined;
    };
    CharacterPageComponent.prototype.confirmDelete = function () {
        var _this = this;
        if (confirm("Are you sure you want to delete card for\n            " + this.selectedCard.name + "?")) {
            this.cardService.deleteCard(this.selectedCard.id).subscribe(function () {
                _this.editing = false;
                _this.getCards();
                _this.selectedCard = undefined;
                _this.originalCard = undefined;
            });
        }
    };
    CharacterPageComponent.prototype.getCards = function () {
        this.cards = this.cardService.getCards({ page: this.currentPage, searchTerm: this.searchTerm });
        // this.cards.subscribe(r => {
        //     this.maxPages = Math.ceil(r.allResults / 5);
        //     this.currentPage = r.page;
        // });
    };
    CharacterPageComponent.prototype.getCompanyName = function (id) {
        var company = _.find(this.companies || [], function (c) { return c.id == id; });
        return company && company.name;
    };
    return CharacterPageComponent;
}());
CharacterPageComponent = __decorate([
    core_1.Component({
        selector: "character-page",
        templateUrl: "./character-page.component.html"
    }),
    __metadata("design:paramtypes", [character_service_1.CharacterService, house_service_1.HouseService])
], CharacterPageComponent);
exports.CharacterPageComponent = CharacterPageComponent;
//# sourceMappingURL=character-page.component.js.map