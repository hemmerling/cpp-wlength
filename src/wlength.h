#ifndef WLENGTH_H
#define WLENGTH_H
/**
 *  @package   wlength
 *  @file      wlength.h
 *  @brief     WLength - Auswertung der in einem Text 
 *             auftretenden Wortlängen und ihrer Häufigkeit 
 *  @author    Rolf Hemmerling <hemmerling@gmx.net>
 *  @version   1.00, 
 *             Programmiersprache "C++",
 *             Entwicklungswerkzeug "Microsoft Visual C++ 1.52" / VC++ 8.00c
 *             ( Large Model ) und "Microsoft 8086 Assembler",
 *             Zielplattform: IBM-PC mit MS-DOS Betriebssystem
 *  @date      2015-01-01
 *  @copyright Apache License, Version 2.0
 *
 *  wlength.h - Header-Datei fuer WLength -
 *              Auswertung der in einem Text
 *              auftretenden Wortlängen und ihrer Häufigkeit.
 *              Programmieraufgabe PA7 im WS 1998 / 1999 im Fach
 *              SWT1, Prof. Lindemann, FH Hannover            
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
 */

/**
 *   def      DEBUG_VERSION
 *  @brief    DEBUG_VERSION - zusaetzliche Ausgaben, 
              nuetzlich bei der Programm-Weiterentwicklung
 */
#undef DEBUG_VERSION  

/**
 *   def      DEBUG2_VERSION
 *  @brief    DEBUG2_VERSION - zusaetzliche Ausgaben, 
              nuetzlich bei der Programm-Weiterentwicklung
 */
#undef DEBUG2_VERSION   

/**
 *   def      DEBUG3_VERSION
 *  @brief    DEBUG3_VERSION - zusaetzliche Ausgaben, 
              nuetzlich bei der Programm-Weiterentwicklung
 */
#undef DEBUG3_VERSION

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
 
/**
 *  @var      SPACE
 *  @brief    *define SPACE 0x20 
 */
const unsigned int SPACE = 0x20;

/**
 *  @var      MAX_LINE
 *  @brief    Maximale Zeilenlaenge+1 = 2048+1 
 *            *define MAX_LINE 2049 
 */
const unsigned int MAX_LINE = 2049;

/**
 *  @var      MAX_HAEUFIGKEIT
 *  @brief    Maximal ermittelbare Haeufigkeit + 1
 *            = (2^16 - 2) + 1 
 *            *define MAX_HAEUFIGKEIT 65535
 */
const unsigned int MAX_HAEUFIGKEIT = 65535;

/**
 *  @var      MAX_WORTLAENGE
 *  @brief    *define MAX_WORTLAENGE 255
 */
const unsigned int MAX_WORTLAENGE = 255;                  
                    
/**
 *  @var      KONTROLLE_LWR
 *  @brief    Durch Aufruf mit Paramter "-k" wird eine   
 *            Auswertung in C statt in 8086 ASM vorgenommen
 *            *define KONTROLLE_LWR "-k"
 */
const char *KONTROLLE_LWR = "-k";

/**
 *  @var      KONTROLLE_UPR
 *  @brief    Durch Aufruf mit Paramter "-k" wird eine   
 *            Auswertung in C statt in 8086 ASM vorgenommen
 *            *define KONTROLLE_UPR "-K"
 */
const char *KONTROLLE_UPR = "-K";
                                               
/**       
 *  @fn       GP_wlength1(unsigned int *IV_anzeige,
 *                        char *IV_puffer,
 *                        unsigned int VV_laenge)
 *  @brief    Assembler-Version des Wortlaengenanalyse-
 *            Unterprogramms, C++ Compiler:
 *            16-bit Compiler VC++ 8.00c = VC++ 1.5.2
 *            Large Model
 *  @param IV_anzeige Das Feld nimmt die Ergebnisse auf           
 *  @param IV_puffer Die aktuelle Dateizeile                     
 *  @param VV_laenge Die Laenge der aktuellen Dateizeile          
 *  @return Fehlercode                                  
 */
#ifdef __cplusplus 
extern "C" {
#endif
int GP_wlength1(unsigned int *IV_anzeige,
                char *IV_puffer,
                unsigned int VV_laenge);
#ifdef __cplusplus 
}
#endif
                       
/**
 *  @class    WLength
 *  @brief    Wortlaengenanalyse                
 */          
class WLength

{

protected:
                                                   
/**
 *  @fn       GP_update(unsigned int VV_wortlaenge_minus_1, 
 *                      unsigned int *IV_anzeige) 
 *  @brief    Erhoehung der Haeufigkeit einer Wortlaenge
 *  @param    VV_wortlaenge_minus_1 Die Wortlaenge, 
 *            deren Haeufigkeit erhoeht werden soll, 
 *            wird um 1 veringert, als Tabellenindex benutzt
 *  @param    IV_anzeige Das Feld nimmt die Ergebnisse auf
 */                                                                         
void GP_update(unsigned int VV_wortlaenge_minus_1, 
               unsigned int *IV_anzeige);

/**
 *  @fn       GP_wlength2(unsigned int *IV_anzeige, 
 *                        char *IV_puffer,
 *                        unsigned int VV_laenge)
 *  @brief    Auswertung einer Dateizeile auf Wortlaengen 
 *            und ihre Haeufigkeit. Dies ist die C-Version, 
 *            es gibt auch noch eine Assembler-Version GP_wlength1()        
 *  @param    IV_anzeige Das Feld nimmt die Ergebnisse auf           
 *  @param    IV_puffer Die aktuelle Dateizeile                     
 *  @param    VV_laenge Die Laenge der aktuellen Dateizeile          
 *  @return   Fehlercode                                  
 */
int GP_wlength2(unsigned int *IV_anzeige, 
               char *IV_puffer,
               unsigned int VV_laenge);

/**
 *  @fn       GP_ausgabe(unsigned int *IV_anzeige)
 *  @brief    Zeilenweise Ausgabe von Wortlaengen 
 *            und zugehoerigen Haeufigkeiten                
 *  @param    IV_anzeige Das Feld enthaelt die auszugebenden Daten                                    
 */ 
void GP_ausgabe(unsigned int *IV_anzeige);


public:

/**
 *  @fn       GP_main(int VV_argc,char **IV_argv)
 *  @brief    Das "Hauptprogramm"        
 *  @param    VV_argc Anzahl der Parameter + 1   
 *  @param    IV_argv Feld von Parameter-Strings 
 *  @return   int Error-Level fuer aufrufendes Programm
 */           
int GP_main(int VV_argc,char **IV_argv);

};

/**
 *  @fn       GP_copyrightmessage
 *  @brief    Copyright-Meldung anzeigen              
 */ 
void GP_copyrightmessage(void);

/**
 *  @fn       main(int VV_argc,char **IV_argv)
 *  @brief    Das "Hauptprogramm"        
 *  @param    VV_argc Anzahl der Parameter + 1   
 *  @param    IV_argv Feld von Parameter-Strings 
 *  @return   int Error-Level fuer aufrufendes Programm
 */           
int main(int VV_argc,char **IV_argv);

#endif // WLENGTH_H

