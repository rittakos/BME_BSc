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
var rx_1 = require("rxjs/rx");
var _ = require("lodash");
var HouseService = (function () {
    function HouseService() {
        this.load();
    }
    HouseService.prototype.getCompanies = function () {
        return rx_1.Observable.of(this.companies)
            .delay(200);
    };
    HouseService.prototype.addOrUpdateCompany = function (company) {
        if (company.id) {
            for (var i = 0; i < this.companies.length; i++) {
                if (this.companies[i].id == company.id) {
                    this.companies[i] = company;
                    break;
                }
            }
        }
        else {
            var maxCompany = _.maxBy(this.companies, function (c) { return c.id; });
            company.id = ((maxCompany && maxCompany.id) || 0) + 1;
            this.companies.push(company);
        }
        return this.save();
    };
    HouseService.prototype.deleteCard = function (company) {
        if (typeof company === 'number')
            this.companies = _.filter(this.companies, function (c) { return c.id !== company; });
        else if (typeof company === 'object')
            this.companies = _.filter(this.companies, function (c) { return c.id !== company.id; });
        return this.save();
    };
    HouseService.prototype.load = function () {
        this.companies = JSON.parse(localStorage.getItem('companies')) || [
            { id: 1, name: 'Survey Corps' },
            { id: 2, name: 'Dog Co.' },
            { id: 3, name: 'Jones&Jones' },
            { id: 4, name: 'Gepetto\'s Toy Store' },
            { id: 5, name: 'FOXHOUND' }
        ];
        this.save();
    };
    HouseService.prototype.save = function () {
        localStorage.setItem('companies', JSON.stringify(this.companies));
        return rx_1.Observable.timer(200);
    };
    return HouseService;
}());
HouseService = __decorate([
    core_1.Injectable(),
    __metadata("design:paramtypes", [])
], HouseService);
exports.HouseService = HouseService;
//# sourceMappingURL=house.service.js.map