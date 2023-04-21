import { Injectable } from '@angular/core';
import {HttpClient, HttpClientModule} from '@angular/common/http';
import { map } from 'rxjs/operators';
import { Observable } from 'rxjs';


@Injectable({
  providedIn: 'root'
})
export class DataService {
  //Propiedad
  items: any[] = [];

  constructor(private http: HttpClient) { }

  guardar(saludador:String[]){
    this.http.post<any>('https://bmt-db-bc6f9-default-rtdb.firebaseio.com/saludos.json', saludador)
    .subscribe(
        response => console.log('respuesta '+ response.name),
        error => console.log('error '+ error)
    );
  }

  /*mostrarGuardado(){
    this.http.get('https://bmt-db-bc6f9-default-rtdb.firebaseio.com/saludos.json').pipe(
      map((responseData: any)=>{
        const items = [];
        for(const key in responseData){
          if(responseData.hasOwnProperty(key)){
            items.push({id:key,...responseData[key]});
          }
        }
        return items;
      })
    ).subscribe(items => {console.log(items);});
  }*/

  mostrarGuardado(): Observable<any[]>{
    return this.http.get('https://bmt-db-bc6f9-default-rtdb.firebaseio.com/saludos.json').pipe(
      map((responseData: any)=>{
        const items = [];
        for(const key in responseData){
          if(responseData.hasOwnProperty(key)){
            items.push({id:key,...responseData[key]});
          }
        }
        return items;
      })
    )
  }

}
