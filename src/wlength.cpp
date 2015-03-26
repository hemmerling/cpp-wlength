/**
 *  @package   wlength
 *  @file      wlength.cpp
 *  @brief     WLength - Auswertung der in einem Text 
 *             auftretenden Wortlaengen und ihrer Haeufigkeit 
 *  @author    Rolf Hemmerling <hemmerling@gmx.net>
 *  @version   1.00, 
 *             Programmiersprache "C++",
 *             Entwicklungswerkzeug "Microsoft Visual C++ 1.52" / VC++ 8.00c
 *             ( Large Model ) und "Microsoft 8086 Assembler",
 *             Zielplattform: IBM-PC mit MS-DOS Betriebssystem
 *  @date      2015-01-01
 *  @copyright Apache License, Version 2.0
 *
 *  wlength.cpp - WLength - Auswertung der in einem Text 
 *                auftretenden Wortlaengen und ihrer Haeufigkeit 
 *                Programmieraufgabe PA7 im WS 1998 / 1999 im Fach
 *                SWT1, Prof. Lindemann, FH Hannover            
 *
 *  Copyright 1998-2015 Rolf Hemmerling
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an
 *  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 *  either express or implied.
 *  See the License for the specific language governing permissions
 *  and limitations under the License.
 *
 *  Haupt-Entwicklungszeiten
 *    1998-09 - 1998-12-14
 *    2001-01-24, 2004-07-20 ( Umstellung auf C++ )
 *    
 */

#include "wlength.h"

void WLength::GP_update(unsigned int VV_wortlaenge_minus_1, 
                        unsigned int *IV_anzeige)
{ if (VV_wortlaenge_minus_1 > MAX_WORTLAENGE) 
   { VV_wortlaenge_minus_1 = MAX_WORTLAENGE; };
  if (IV_anzeige[VV_wortlaenge_minus_1] < 
      MAX_HAEUFIGKEIT)
   { IV_anzeige[VV_wortlaenge_minus_1]++; };
#ifdef DEBUG2_VERSION
      printf("Update: Wortlaenge-1 = %d, Haeufigkeit = %d\n",
              VV_wortlaenge_minus_1, 
              IV_anzeige[VV_wortlaenge_minus_1]);
#endif          
}
                                                    

int WLength::GP_wlength2(unsigned int *IV_anzeige, 
                         char *IV_puffer,
                         unsigned int VV_laenge)
{ 
  unsigned int 
    PV_value = 0 /* Rueckgabewert */,
    PV_cx, PV_cx_anfang, PV_cx_ende /* CX-Register */,
    PV_zero /* Zero-Statusbit im Akku */;
               
  char *PV_es_di /* Zeiger auf augenblickliches Zeichen */;

  PV_es_di = IV_puffer;
  PV_cx = VV_laenge;
  
  /* Bei ASM-Routine muss DF=0 gesetzt werden (Auto-Increment) */                    

  while (PV_cx != 0)
   {
     /* Suchen nach naechsten Nicht-SPACE Zeichen */
     do { PV_zero = (*(PV_es_di++) == SPACE);
          --PV_cx;}
       while ( (PV_cx != 0) && (PV_zero != 0));    
                  
     /* Zeigerkorrektur, falls Nicht-SPACE gefunden wurde */
     if (PV_zero == 0)         
      { PV_es_di--;
        PV_cx++; };
      
     PV_cx_anfang = PV_cx;
     
     /* Suche nach dem naechsten SPACE-Zeichen */
     if (PV_cx != 0)
      {                                                                                  
        do { PV_zero = (*(PV_es_di++) == SPACE);
             --PV_cx; }
        while ( (PV_cx != 0) && (PV_zero == 0));
                                                      
        /* Zeigerkorrektur, falls SPACE Zeichen gefunden wurde */                                              
        if (PV_zero != 0)
         { PV_es_di--;
           PV_cx++; };
           
        PV_cx_ende = PV_cx;                   
        
       /* Haeufigkeitstabelle aktualisieren */
       GP_update(PV_cx_anfang-PV_cx_ende-1, IV_anzeige);
      };
    }; /* PV_cx != 0 */
  return(PV_value);
}     

void WLength::GP_ausgabe(unsigned int *IV_anzeige)
{ unsigned int LV_ii /* FOR-Schleifenzaehler */;    
  /* Ausgabe von Wortlaenge und zugehoeriger Haeufigkeit
     fuer jede *auftretende* Wortlaenge */        
  for (LV_ii=0; LV_ii<255; LV_ii++)
   { if (IV_anzeige[LV_ii] != 0)   
      { printf("%5.d\t%5.d\n", LV_ii+1, IV_anzeige[LV_ii]); };
   };                      
  /* Ausgabe der Summenhaeufigkeit aller Woerter mit einer 
     Wortlaenge > 255, falls aufgetreten */
  if (IV_anzeige[255] != 0)   
      { printf("%5s\t%5.d\n", ">255", IV_anzeige[255]); };
} 
                                   
int WLength::GP_main(int VV_argc,char **IV_argv)
{ 
  unsigned int 
    PV_eof /* EOF-Statusvariable */,
    LV_ii /* FOR-Laufvariable */, 
    PV_value=0 /* Rueckgabewert */,
    PV_anzeige[256] /* Feld mit Haeufigkeiten von Wortlaengen */, 
    PV_kontrolle =0 /* 1 = Hochsprachen-Version */,
    PV_laenge /* Laenge einer eingelesenen Dateizeile */;  
  char 
    *PV_puffer /* Zeiger auf Dateizeilenpuffer */;
    
  PV_puffer = (char *)calloc(MAX_LINE,sizeof(char));
  for (LV_ii=0; LV_ii<256; LV_ii++)
   { PV_anzeige[LV_ii] = 0; }; 
    
  /* Eigenen Buffer in geforderter Groesse anmelden */
  PV_value = setvbuf(stdin,PV_puffer,_IOFBF,(sizeof(char))*MAX_LINE);

  PV_kontrolle = (((VV_argc-1) == 1) && 
                  (
                   (strcmp(IV_argv[1],KONTROLLE_LWR) == 0) ||
                    (strcmp(IV_argv[1],KONTROLLE_UPR) == 0) 
                  )  
                 );
  /* Standard-Eingabe lesen bis EOF */
  do {                      
       /* Die Standard-Bibliotheksfunktion gets vernichtet */ 
       /* Dateiendezeichen und fuegt \00 am Zeilenende an  */
       PV_eof = (gets(PV_puffer) == NULL);             
       PV_laenge = strlen(PV_puffer);       
        
       if (!PV_eof)
        {
          if ( PV_kontrolle ) 
           {                       
#ifdef DEBUG_VERSION 
             printf ("Laenge der Dateizeile = %d\n",PV_laenge);
#endif                                                    
             /* Wortlaengen und ihre Haeufigkeit ermitteln */
             /* C-Version des Unterprogramms */
             PV_value = GP_wlength2(PV_anzeige,PV_puffer,PV_laenge); 
           }
          else
           {
             /* Wortlaengen und ihre Haeufigkeit ermitteln */
             /* Assemble-Version des Unterprogramms */
#ifdef DEBUG_VERSION      
             printf ("Laenge der Dateizeile = %d\n",PV_laenge);      
#endif
             PV_value = GP_wlength1(PV_anzeige,PV_puffer,PV_laenge);
#ifdef DEBUG_VERSION  
             printf("Rueckgabewert %d\n",PV_value);
#endif
            };
        
#ifdef DEBUG3_VERSION       
          printf("Zeile = <%s>\n",PV_puffer); 
          GP_ausgabe(PV_anzeige);   
#endif                     
        };
     }while ((!PV_eof) && (PV_value == 0));
#ifdef DEBUG_VERSION 
  printf("Endergebnis: \n");
#endif  
  /* Zeilenweise Ausgabe von Wortlaengen und  */
  /* zugehoerigen Haeufigkeiten               */   
  GP_ausgabe(PV_anzeige);    
  
  /* Ausgabe des Fehlercodes zur weiteren Auswertung durch das
     aufrufende Programm */
  return(PV_value);
}                                  

void GP_copyrightmessage(void)
{
    printf("WLength - Auswertung der in einem Text auftretende\n");
    printf("          Wortlaengen und ihre Haeufigkeit\n");
    printf("Copyright 1998-2015 Rolf Hemmerling\n");
    printf("Licensed under the Apache License, Version 2.0\n");

}

int main(int VV_argc,char **IV_argv){
  if (VV_argc == 0)
   {
     GP_copyrightmessage();
   }
  WLength *x = new WLength;
  return ( x->GP_main(VV_argc, IV_argv) ); 
  
}
