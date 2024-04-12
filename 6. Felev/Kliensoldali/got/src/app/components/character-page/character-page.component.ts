import { Component, OnInit } from "@angular/core";
import { Observable } from "rxjs/rx";
import { Character } from "../../models/character.type";
import { CharacterService } from "../../services/character.service";
import { SearchResult } from "../../models/search-result.type";
import { HouseService } from "../../services/house.service";
import { House } from "../../models/house.type";
import * as _ from "lodash";

@Component({
    selector: "character-page",
    templateUrl: "./character-page.component.html"
})
export class CharacterPageComponent implements OnInit {
    constructor(private cardService: CharacterService, private companyService: HouseService) { console.log("asfsadf"); }
    ngOnInit() {
        
        //alert(this.cardService.getcharacter().name);
        this.getCards();
        this.companyService.getCompanies().subscribe(cmp => this.companies = cmp);
    }

    selectedCard: Character;
    originalCard: Character;
    editing: boolean = false;
    cards: Observable<SearchResult<Character>>;
    companies: House[];
    currentPage: number = 0;
    maxPages: number = 0;
    searchTerm: string = "";


    editCard() {
        this.editing = true;
        this.originalCard = this.selectedCard;
        this.selectedCard = { ...this.originalCard }; // make a copy of the object
    }

    saveCard(card: Character) {
        this.cardService.addOrUpdateCard(card)
            .subscribe(() => {
                this.editing = false;
                this.getCards();
                this.selectedCard = undefined;
                this.originalCard = undefined;
            });
    }

    cancel() {
        this.editing = false;
        this.selectedCard = this.originalCard;
        this.originalCard = undefined;
    }

    confirmDelete() {
        if (confirm(`Are you sure you want to delete card for
            ${this.selectedCard.name}?`)) {
            this.cardService.deleteCard(this.selectedCard.id).subscribe(() => {
                this.editing = false;
                this.getCards();
                this.selectedCard = undefined;
                this.originalCard = undefined;
            });
        }
    }

    getCards() {
        this.cards = this.cardService.getCards({ page: this.currentPage, searchTerm: this.searchTerm });
        // this.cards.subscribe(r => {
        //     this.maxPages = Math.ceil(r.allResults / 5);
        //     this.currentPage = r.page;
        // });
    }

    getCompanyName(id: number) {
        let company = _.find(this.companies || [], c => c.id == id);
        return company && company.name;
    }
}