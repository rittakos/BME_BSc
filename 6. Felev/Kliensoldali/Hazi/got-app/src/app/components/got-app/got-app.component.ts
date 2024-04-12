import { Component, OnInit } from '@angular/core';
import { Router, NavigationEnd } from '@angular/router';
import * as _ from 'lodash';
import { Observable } from "rxjs/rx";
import { CharacterService } from "../../services/character.service";
import { Character } from "../../models/character.type";

@Component({
    selector: 'got-app',
    templateUrl: './got-app.component.html'
})
export class GotAppComponent implements OnInit {
    constructor(private router: Router) { }
    ngOnInit() {
        this.currentPageTitle = this.router.events
            .filter(e => e instanceof NavigationEnd)
            .map((() => _.find(["Cards", "Companies"], t => this.router.isActive('/' + t.toLowerCase(), false))).bind(this))
    }
    
    title = "Game of Thrones Database";
    isNavbarCollapsed = true;
    currentPageTitle: Observable<string>;
}