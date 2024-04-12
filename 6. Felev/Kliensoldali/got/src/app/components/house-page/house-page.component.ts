import { Component, Host, OnInit } from "@angular/core";
import { Observable } from "rxjs/rx";
import { House } from "../../models/house.type";
import { CharacterService } from "../../services/character.service";
import { HouseService } from "../../services/house.service";
import { ActivatedRoute } from "@angular/router";
import { SearchResult } from "../../models/search-result.type";
import { Character } from "../../models/character.type";
import * as _ from "lodash";

@Component({
    selector: "house-page",
    templateUrl: "./house-page.component.html"
})
export class HousePageComponent implements OnInit {
    constructor(private companyService: HouseService,
        private cardService: CharacterService,
        private route: ActivatedRoute) { }

    ngOnInit(): void {
        this.getCompanies();
        this.route.params.subscribe(params => {
            let companyId = +params['id'];
            // this.companies
            //     .map(companies => companies.find( => this.selectedCompany.id == companyId));
        });
    }
    selectedCompany: House;
    cards: Character[];
    companies: Observable<House[]>;

    getCompanies() {
        this.companies = this.companyService.getCompanies();
    }

}