import { Injectable } from "@angular/core";
import { Character } from "../models/character.type";
import { House } from "../models/house.type";
import * as _ from "lodash";
import { SearchResult } from "../models/search-result.type";
import { Observable } from "rxjs/Rx";
import {HttpClient} from "@angular/common/http"

@Injectable()
export class CharacterService {
    private characters: Character[];
    private apiURL: string = "https://www.anapioficeandfire.com/api";
    constructor(private http: HttpClient) {
        this.load();
    }

    //public getcharacter(): any {
        //return this.http.get<Character>(this.apiURL + '/characters/583');
    //}

    getCards(options?: { searchTerm?: string, pageSize?: number, page?: number }) {
        this.characters = [{id: 1, name: "ddddd"}]
        let pageSize = (options && options.pageSize) || 5;
        let page = (options && options.page) || 0;
        let searchTerm = (options && options.searchTerm) || '';
        let allResults = searchTerm.length
            ? _.filter(this.characters, c => _.find([c.name], e => e && e.toLowerCase().indexOf(searchTerm.toLowerCase()) > -1) !== undefined)
            : this.characters;
        

        return Observable.of(_.slice(allResults, pageSize * page, pageSize * (page + 1)))
            .map(results => <SearchResult<Character>>{
                allResults: allResults.length, results, page, pageSize, searchTerm
            })
            .delay(200);

    }

    addOrUpdateCard(card: Character) {
        if (card.id) {
            for (let i = 0; i < this.characters.length; i++) {
                if (this.characters[i].id == card.id) {
                    this.characters[i] = card;
                    break;
                }
            }
        }
        else {
            let maxCard = _.maxBy(this.characters, c => c.id);
            card.id = ((maxCard && maxCard.id) || 0) + 1;
            this.characters.push(card);
        }
        return this.save();
    }

    deleteCard(card: Character | number) {
        if (typeof card === 'number')
            this.characters = _.filter(this.characters, c => c.id !== card);
        else if (typeof card === 'object')
            this.characters = _.filter(this.characters, c => c.id !== card.id);
        return this.save();
    }

    private load() {
        this.characters = JSON.parse(localStorage.getItem('cards')) || [
            {id: 1, name: "fasdfsa"},
            
            //{ id: 583, name: this.http.get(this.apiURL + '/characters/583')["name"] }
            //{ companyId: 1, firstName: 'Levi', lastName: 'Ackermann', id: 1, motto: "Humanity's strongest soldier", role: 'Captain', imageUrl: 'http://vignette3.wikia.nocookie.net/shingekinokyojin/images/9/94/Levi_Ackerman_character_image.png/revision/latest?cb\x3d20151125005625' },
            // { companyId: 2, firstName: 'Rhonda', lastName: 'Dumas', id: 2, motto: "Accounting for fun", role: 'Accountant', imageUrl: 'http://img2.stockfresh.com/files/k/kurhan/m/64/431783_76810602.jpg' },
            // { companyId: 3, firstName: 'Davey', lastName: 'Jones', id: 3, motto: "Analyzing business for the future", role: 'Business Analyst', imageUrl: 'https://s3.eu-central-1.amazonaws.com/artistarea.gallereplay.com/production/user_9/picture_2405201614728.jpg' },
            // { companyId: 4, firstName: 'Pinocchio', lastName: '', id: 4, motto: "I'm no puppet", role: 'Puppet', imageUrl: 'https://images-na.ssl-images-amazon.com/images/G/01/dvd/disney/pinocchio/Pinocchio2.jpg' },
            // { companyId: 5, firstName: 'Solid', lastName: 'Snake', id: 5, motto: "LIQUID!", role: 'Super Soldier', imageUrl: 'https://pbs.twimg.com/profile_images/34087792/Immagine_1_400x400.jpg' }
        ];
        this.save();
    }

    private save() {
        localStorage.setItem('cards', JSON.stringify(this.characters));
        return Observable.timer(200);
    }
}