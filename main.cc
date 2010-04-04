/* 
 * This is the main program for Uebung2_4 - Messdatenerfassung.
 * See COPYING for copyright information.
 */

#include <iostream>
#include "binary_tree.h"
#include "app.h"

using namespace std;

int
main(void)
{

    tree *measurements = new tree; // tree to hold the values
    unsigned int total = 0;  // total number of stored values
    unsigned int id = 0;    // ids of values
    char choice;

    /*  Main Menu loop */
    do {

        cout << "\n----- Menu -----\n"
         << "\t(a) Messwert eingeben\n"
		 << "\t(b) Messwerte ausgeben\n"
		 << "\t(c) Messwert loeschen\n"
         << "\t(d) Messwert suchen\n"
         << "\t(e) Durchschnittswert berechnen\n"
         << "\t(f) Standardabweichung berechnen\n"
		 << "\t(q) Program beenden\n   >> ";
        cin >> choice;
		
        switch (choice) {
            case 'A':
            case 'a':
                if (addValue(measurements, id))
                    total++, id++;
				break;
				
            case 'B':
            case 'b':
                showValues(measurements);
                cout << "Anzahl der Messwerte: " << total << endl;
				break;
				
            case 'C':
            case 'c':
                if (delValue(measurements))
                    total--;
				break;

            case 'D':
            case 'd':
                searchValue(measurements);
                break;

            case 'E':
            case 'e':
                avg(measurements, total);
                break;

            case 'F':
            case 'f':
                stdDev(measurements, total);
                break;

            case 'Q':
            case 'q': break;
				
            default: cout << "Fehlerhafte Wahl!\n";
        }
		
    } while (choice != 'q' && choice != 'Q');

    // Delete Tree (or destroy(measurements);)
    destroy(measurements);
    delete measurements;

    return 0;
}
