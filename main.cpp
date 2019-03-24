#include "main.h"

void checkInput(){
    if(!std::cin.good()){
        std::cin.clear();
        std::cin.ignore(INT_MAX,'\n');
    }
}

std::vector<studentas> sortByNd(std::vector<studentas> users, bool chrono) {
    auto start = std::chrono::system_clock::now();
    int i, j, k;
    for (i = 0; i < users.size(); i++)
        for (j = 0; j < users[i].nd.size()-1; j++)
            for (k = 0; k < users[i].nd.size()-j-1; k++)
                if (users[i].nd[k] > users[i].nd[k+1])
                    std::swap(users[i].nd[k],users[i].nd[k+1]);
    if(chrono) {
        auto end = std::chrono::system_clock::now();
        auto elapsed = end - start;
        std::cout << "Rusiavimas uztruko: " << (double)elapsed.count()/10000000 << "s." << std::endl;
    }
    return users;
}
std::vector<studentas> sortByName(std::vector<studentas> users) {
    std::sort(std::begin(users), std::end(users), [](const studentas &a1, const studentas &a2 ){
        return a1.name.compare(a2.name) < 0;
    });
    return users;
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

    while(tempn != 0){
        std::cin >> tempn;
        checkInput();
        if(tempn > 0 && tempn < 11)
            stud.nd.push_back(tempn);
        else if(tempn > 10 || tempn < 0)
            std::cout << std::endl << "Ivesta neteisinga reiksme. Galite testi rezultatu pildyma arba iveskite 0, jei norite baigti.";
        std::cout << std::endl;
    }
    if(stud.nd.size() == 0){
        std::cout << "Neivesta jokia namu darbu reiksme. Ivedama nustatyta reiksme: 1" << std::endl;
        stud.nd.push_back(1);
    }

    std::cout << "Iveskite egzamino rezultata: ";
    std::cin >> egz;
    checkInput();
    while(egz < 1 || egz > 10){
        std::cout << std::endl << "Ivesta neteisinga reiksme. Iveskite egzamino rezultata: ";
        std::cin >> egz;
        checkInput();
    }
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
    users = sortByNd(users, true);
    auto start = std::chrono::system_clock::now();
    for(int i = 0; i < users.size(); i++){
        suma = 0;
        std::cout << users[i].surname << std::string(longestSurname - users[i].surname.size() + 1, ' ') << users[i].name << std::string(longestName - users[i].name.size() + 1, ' ');

        if(median) {
            if(users.size() % 2 == 0){
                imedian = (double)(users[i].nd[users[i].nd.size()/2] + users[i].nd[users[i].nd.size()/2-1])/2;
            } else {
                imedian = floor((double)users[i].nd[users[i].nd.size()/2]);
            }
            galutinis = imedian * 0.4 + 0.6 * (double) users[i].egz;
        } else {
            for(int j = 0; j < users[i].nd.size(); j++){
                suma += users[i].nd[j];
            }
            galutinis = ((double) suma / (double) users[i].nd.size()) * 0.4 + 0.6 * (double) users[i].egz;
        }

        std::cout << std::setprecision(2) << std::fixed << galutinis;
//        std::cout << suma << " < " << users[i].nd.size() << " < " << users[i].egz << " < " << galutinis;
        std::cout << std::endl;
    }
    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;
    std::cout << "Spausdinimas uztruko: " << (double)elapsed.count()/10000000 << "s." << std::endl;
}

double getResult(studentas stud, bool median){
    std::vector<studentas> users;
    users.push_back(stud);
    double imedian, galutinis,suma = 0;
    if(median) {
        users = sortByNd(users, false);
        if(users.size() % 2 == 0){
            imedian = (double)(users[0].nd[users[0].nd.size()/2] + users[0].nd[users[0].nd.size()/2-1])/2;
        } else {
            imedian = floor((double)users[0].nd[users[0].nd.size()/2]);
        }
        galutinis = imedian * 0.4 + 0.6 * (double) users[0].egz;
    } else {
        for(int j = 0; j < users[0].nd.size(); j++){
            suma += users[0].nd[j];
        }
        galutinis = (suma / (double) users[0].nd.size()) * 0.4 + 0.6 * (double) users[0].egz;
    }
    return galutinis;
}

std::vector<studentas> regenerateResults(std::vector<studentas> users) {
    auto start = std::chrono::system_clock::now();
    srand(time(NULL));
    for(int i = 0; i < users.size(); i++){
        for(int j = 0; j < users[i].nd.size(); j++) {
            users[i].nd[j] = 1 + (rand() % 10);
        }
    }
    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;
    std::cout << "Regeneracija uztruko: " << (double)elapsed.count()/10000000 << "s." << std::endl;
    return users;
}

std::vector<studentas> generateStudentsAndLoad(std::vector<studentas> users, int amount) {
    auto start = std::chrono::system_clock::now();
    srand(time(NULL));

    std::ofstream osless("nuskriaustukai.txt");
    std::ofstream osmore("galvociai.txt");

    osless << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Pavarde";
    for(int i = 0; i < 10; i++)
        osless << "NS" << (i+1) << "   ";
    osless << "Egzaminas" << std::endl;
    osmore << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Pavarde";
    for(int i = 0; i < 10; i++)
        osmore << "NS" << (i+1) << "   ";
    osmore << "Egzaminas" << std::endl;

    for(int i = 0; i < amount; i++){
        studentas stud;
        stud.name = ("Vardas" + std::to_string(i));
        stud.surname = ("Pavarde" + std::to_string(i));
        for(int j = 0; j < 10; j++) {
            stud.nd.push_back(1 + (rand() % 10));
        }
        stud.egz = 1 + (rand() % 10);
        users.push_back(stud);
        if(getResult(stud,false) >= 5){
            osmore << std::left << std::setw(15) << stud.name << std::left << std::setw(15) << stud.surname;
            for(int j = 0; j < stud.nd.size(); j++){
                osmore << std::left << std::setw(6) << stud.nd[j];
            }
            osmore << " " << stud.egz << std::endl;
        }else {
            osless << std::left << std::setw(15) << stud.name << std::left << std::setw(15) << stud.surname;
            for(int j = 0; j < stud.nd.size(); j++){
                osless << std::left << std::setw(6) << stud.nd[j];
            }
            osless << " " << stud.egz << std::endl;
        }
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;
    std::cout << "Generacija uztruko: " << (double)elapsed.count()/10000000 << "s." << std::endl;

    return users;
}

std::vector<studentas> loadStudents(std::vector<studentas> users) {
    try {
        std::ifstream inf("kursiokai.txt");

        if (inf.fail() || inf.bad() || !inf.is_open()) {
            throw std::runtime_error("Can not load file.");
        }

        bool start = true;
        std::string entry;
        int ndcount = 0, tempnd = 0;
        while(inf >> entry) {
            if (start) {
                if (entry.find("ND") == 0) {
                    ndcount++;
                }
                if (entry == "Egzaminas") {
                    start = false;
                }
            } else {
                studentas stud;
                stud.surname = entry;
                inf >> stud.name;
                for(int i = 0; i < ndcount; i++){
                    inf >> tempnd;
                    if(tempnd < 1 || tempnd > 10){
                        tempnd = 1;
                        std::cout << "Rasta bloga namu darbu reiksme. Ji pakeista i 1." << std::endl;
                    }
                    stud.nd.push_back(tempnd);
                }
                inf >> stud.egz;
                if(stud.egz < 1 || stud.egz > 10){
                    stud.egz = 1;
                    std::cout << "Rasta bloga egzamino reiksme. Ji pakeista i 1." << std::endl;
                }
                users.push_back(stud);
            }
        }
    } catch (std::exception& e) {
        std::cout << "Klaida ikeliant failus is kursiokai.txt. Galbut failas neegzistuoja?";
    }

    return users;
}

std::vector<studentas> generationMenu(std::vector<studentas> users){
    int selection = 0;
    while(selection == 0){
        std::cout << "Pasirinkite, kiek studentu norite sugeneruoti:" << std::endl;
        std::cout << "1. 10 studentu" << std::endl;
        std::cout << "2. 100 studentu" << std::endl;
        std::cout << "3. 1000 studentu" << std::endl;
        std::cout << "4. 10 000 studentu" << std::endl;
        std::cout << "5. 100 000 studentu" << std::endl;
        std::cout << "6. Atsaukti" << std::endl;
        std::cin >> selection;
        checkInput();

        if(selection >= 1 && selection <= 5){
            auto gen = 10;
            switch (selection){
                case 2:
                    gen = 100;
                    break;
                case 3:
                    gen = 1000;
                    break;
                case 4:
                    gen = 10000;
                    break;
                case 5:
                    gen = 100000;
                    break;
            }
            users = generateStudentsAndLoad(users, gen);
            return users;
        }else if(selection == 6){
            return users;
        } else {
            std::cout << "Ivestas neteisingas pasirinkimas. Pabandykite vel." << std::endl;
            selection = 0;
        }
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
        std::cout << "4. Pergeneruoti visu ivestu studentu namu darbu balus i atsitiktinius;" << std::endl;
        std::cout << "5. Ivesti studentu informacija is kursiokai.txt failo;" << std::endl;
        std::cout << "6. Sugeneruoti tam tikra skaiciu studentu, juos ikelti i programa ir isaugoti failuose;" << std::endl;
        std::cin >> selection;


        switch(selection) {
            case 1:
                users.push_back(getUserInfo());
                break;
            case 2:
                showResults(sortByName(users),false);
                break;
            case 3:
                showResults(sortByName(users),true);
                break;
            case 4:
                users = regenerateResults(users);
                selection = 1;
                break;
            case 5:
                users = loadStudents(users);
                selection = 1;
                break;
            case 6:
                users = generationMenu(users);
                selection = 1;
                break;
            default:
                std::cout << "Ivestas neteisingas pasirinkimas" << std::endl << std::endl;
                selection = 1;
                break;
        }
    }


    return 0;
}