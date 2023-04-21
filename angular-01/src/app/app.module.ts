import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import {HttpClientModule} from '@angular/common/http';
import { FormsModule } from '@angular/forms';

import { AppComponent } from './app.component';
import { InicioComponent } from './inicio/inicio.component';
import { AcercaComponent } from './acerca/acerca.component';
import { MenuComponent } from './menu/menu.component';
import { ContactoComponent } from './contacto/contacto.component';
import { AppRoutingModule } from './app-routing.module';
import { DatosComponent } from './datos/datos.component';
import { FormularioComponent } from './formulario/formulario.component';
import { MostrarComponent } from './mostrar/mostrar.component';


@NgModule({
  declarations: [
    AppComponent,
    InicioComponent,
    AcercaComponent,
    MenuComponent,
    ContactoComponent,
    DatosComponent,
    FormularioComponent,
    MostrarComponent,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule,
    FormsModule,
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
