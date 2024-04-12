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
var character_service_1 = require("../../services/character.service");
var house_service_1 = require("../../services/house.service");
var router_1 = require("@angular/router");
var HousePageComponent = (function () {
    function HousePageComponent(companyService, cardService, route) {
        this.companyService = companyService;
        this.cardService = cardService;
        this.route = route;
    }
    HousePageComponent.prototype.ngOnInit = function () {
        this.getCompanies();
        this.route.params.subscribe(function (params) {
            var companyId = +params['id'];
            // this.companies
            //     .map(companies => companies.find( => this.selectedCompany.id == companyId));
        });
    };
    HousePageComponent.prototype.getCompanies = function () {
        this.companies = this.companyService.getCompanies();
    };
    return HousePageComponent;
}());
HousePageComponent = __decorate([
    core_1.Component({
        selector: "house-page",
        templateUrl: "./house-page.component.html"
    }),
    __metadata("design:paramtypes", [house_service_1.HouseService,
        character_service_1.CharacterService,
        router_1.ActivatedRoute])
], HousePageComponent);
exports.HousePageComponent = HousePageComponent;
//# sourceMappingURL=house-page.component.js.map