#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <vector>
#include <stdio.h>

struct studentas {
    std::string name, surname;
    int egz, n;
    int nd[100000];
};

void sortByNd(std::vector<studentas> users) {
    int i, j, k;
    for (i = 0; i < users.size(); i ++)
        for (j = 0; j < users[i].n-1; j++)
            for (k = 0; k < users[i].n-j-1; k++)
                if (users[i].nd[k] > users[i].nd[k+1])
                    std::swap(users[i].nd[k],users[i].nd[k+1]);
}

studentas getUserInfo() {
    studentas stud;
    std::string name,surname;
    int egz;

    std::cout << "Iveskite varda: ";
    std::cin >> name;
    std::cout << std::endl << "Iveskite pavarde: ";
    std::cin >> surname;

    stud.name = name;
    stud.surname = surname;

    std::cout << std::endl << "Iveskite namu darbu rezultatus (iveskite 0 noredami nutraukti pildyma):" << std::endl;

    int tempn = 1;

    int n = 0;
    while(tempn != 0){
        std::cin >> tempn;
        if(tempn > 0 && tempn < 11) {
            stud.nd[n] = tempn;
            n++;
        } else if(tempn > 10 || tempn < 0)
            std::cout << std::endl << "Ivesta neteisinga reiksme. Galite testi rezultatu pildyma arba iveskite 0, jei norite baigti.";
        std::cout << std::endl;
    }

    stud.n = n;

    std::cout << "Iveskite egzamino rezultata: ";
    std::cin >> egz;
    stud.egz = egz;

    std::cout << "Ivedimas baigtas" << std::endl << std::endl;

    return stud;
}

void showResults(std::vector<studentas> users, bool median) {
    int longestName = 0, longestSurname = 0;
    for (int i = 0; i < users.size(); i++) {
        if(users[i].name.size() > longestName)
            longestName = users[i].name.size();
        if(users[i].surname.size() > longestSurname)
            longestSurname = users[i].surname.size();
    }
    if(longestSurname < 7)
        longestSurname = 7;
    if(longestName < 6)
        longestName = 6;
    std::cout << "Pavarde" << std::string(longestSurname - 6, ' ') << "Vardas" << std::string(longestName - 5, ' ');
    std::cout << "Galutinis (Vid.)" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    double galutinis = 0,imedian = 0;
    int suma = 0 ;
    for(int i = 0; i < users.size(); i++){
        suma = 0;
        std::cout << users[i].surname << std::string(longestSurname - users[i].surname.size() + 1, ' ') << users[i].name << std::string(longestName - users[i].name.size() + 1, ' ');

        if(median) {
            sortByNd(users);
            if(users.size() % 2 == 0){
                imedian = (double)(users[i].nd[users[i].n/2] + users[i].nd[users[i].n/2-1])/2;
            } else {
                imedian = floor((double)users[i].nd[users[i].n/2]);
            }
            galutinis = imedian * 0.4 + 0.6 * (double) users[i].egz;
        } else {
            for(int j = 0; j < users[i].n; j++){
                suma += users[i].nd[j];
            }
            galutinis = ((double) suma / (double) users[i].n) * 0.4 + 0.6 * (double) users[i].egz;
        }

        std::cout << std::setprecision(2) << std::fixed << galutinis;
//        std::cout << suma << " < " << users[i].nd.size() << " < " << users[i].egz << " < " << galutinis;
        std::cout << std::endl;
    }

}

int main() {
    std::vector<studentas> users;
    int selection = 1;
    while(selection == 1){
        std::cout << "Ivesta " << users.size() << " stud. Pasirinkite:" << std::endl;
        std::cout << "1. Ivesti nauja studenta;" << std::endl;
        std::cout << "2. Suskaiciuoti galutinius balus (su vidurkiu);" << std::endl;
        std::cout << "3. Suskaiciuoti galutinius balus (su mediana);" << std::endl;
        std::cin >> selection;
        switch(selection) {
            case 1:
                users.push_back(getUserInfo());
                break;
            case 2:
                showResults(users,false);
                break;
            case 3:
                showResults(users,true);
                break;
            default:
                std::cout << "Ivestas neteisingas pasirinkimas" << std::endl << std::endl;
                selection = 1;
                break;
        }
    }


    return 0;
}