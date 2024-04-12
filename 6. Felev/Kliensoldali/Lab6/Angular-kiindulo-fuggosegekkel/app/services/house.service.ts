import { Injectable } from "@angular/core";
import { Observable } from "rxjs/rx";
import { Character } from "../models/character.type";
import { House } from "../models/house.type";
import * as _ from "lodash";

@Injectable()
export class HouseService {
    private companies: House[];
    constructor() {
        this.load();
    }

    getCompanies() {
        return Observable.of(this.companies)
            .delay(200);
    }

    addOrUpdateCompany(company: House) {
        if (company.id) {
            for (let i = 0; i < this.companies.length; i++) {
                if (this.companies[i].id == company.id) {
                    this.companies[i] = company;
                    break;
                }
            }
        }
        else {
            let maxCompany = _.maxBy(this.companies, c => c.id);
            company.id = ((maxCompany && maxCompany.id) || 0) + 1;
            this.companies.push(company);
        }
        return this.save();
    }

    deleteCard(company: House | number) {
        if (typeof company === 'number')
            this.companies = _.filter(this.companies, c => c.id !== company);
        else if (typeof company === 'object')
            this.companies = _.filter(this.companies, c => c.id !== company.id);
        return this.save();
    }

    private load() {
        this.companies = JSON.parse(localStorage.getItem('companies')) || [
            { id: 1, name: 'Survey Corps' },
            { id: 2, name: 'Dog Co.' },
            { id: 3, name: 'Jones&Jones' },
            { id: 4, name: 'Gepetto\'s Toy Store' },
            { id: 5, name: 'FOXHOUND' }
        ];
        this.save();
    }

    private save() {
        localStorage.setItem('companies', JSON.stringify(this.companies));
        return Observable.timer(200);
    }
}