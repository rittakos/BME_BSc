import { NgModule } from '@angular/core';
import { RouterModule, Route } from '@angular/router';
import { FormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';

import { BrowserModule } from '@angular/platform-browser';
//import { CollapseModule } from 'ng2-bootstrap'
import { HousePageComponent } from "./components/house-page/house-page.component";
import { CharacterPageComponent } from "./components/character-page/character-page.component";
import { GotAppComponent } from "./components/got-app/got-app.component";
import { CharacterService } from "./service/character.service";
import { HouseService } from "./service/house.service";



let routes: Route[] = [
    { path: "houses", component: HousePageComponent },
    { path: "characters", component: CharacterPageComponent },
    { path: "houses/:id", component: HousePageComponent },
    { path: "characters/:id", component: CharacterPageComponent },
    { path: "books", component: CharacterPageComponent },
    { path: "books/:id", component: HousePageComponent },
];

@NgModule({
    imports: [BrowserModule, RouterModule.forRoot(routes), FormsModule, HttpClientModule/*, CollapseModule.forRoot()*/],
    declarations: [GotAppComponent, HousePageComponent, CharacterPageComponent],
    exports: [],
    providers: [CharacterService, HouseService],
    bootstrap: [GotAppComponent]
})
export class GotAppModule { }
