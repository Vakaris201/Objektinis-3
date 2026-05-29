#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm> 
#include <cctype>
#include <ctime>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iterator>
#include <cstdlib>
#include "Zmones.h"
#include "Studentas.h"
#include "Funkcijos.h"
#include "Vector.h"

using std::string;
//using std::vector;
template<typename T>
using vector = Vector<T>;
using std::cout;
using std::cin;
using std::setw;
using std::left;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::sort;
using std::stringstream;
using std::chrono::high_resolution_clock;
using std::chrono::duration;


int main() {
    srand(time(0));
    system("dir *.txt");
    std::ios::sync_with_stdio(false);
    vector<Studentas> A;
    int temp, stud_skaicius = 0, index = 0;
    string f_choice, filename;
    cout << "Ar noretumet skaityti duomenis is failo? (t/n) ";
    f_choice = raide_choice(
        "Iveskite t arba n"
    );
    if(f_choice == "t" || f_choice == "T") {
        while(true) {
            cout << "Iveskite failo pavadinima: ";
            cin >> filename;
            try {
                ifstream test(filename);
                if(!test) {
                    throw std::runtime_error("Failas nerastas.");
                }
                break;
            }
            catch (std::exception& e) {
                cout << "Klaida: " << e.what() << " Pabandykite dar karta." << endl;
            }
        }
        A.reserve(10000000);
        string line;
        ifstream fin(filename);
        getline(fin, line);
        stringstream ss;
        auto start = high_resolution_clock::now();
        while(getline(fin, line)) {
            ss.clear();
            ss.str(line);
            Studentas S;
            ss >> S;
            A.push_back(move(S));
            stud_skaicius++;
        }
        fin.close();
        auto end = high_resolution_clock::now();
        duration<double> diff = end - start;
        outputas(A, stud_skaicius, diff.count(), filename);
        system("pause");
    }
    else {
        int eiga;
        cout << "Iveskite eiga: " << endl;
        cout << "1 - ranka " << endl;
        cout << "2 - generuoti tik pazymius " << endl;
        cout << "3 - generuoti studentu vardus, pavardes ir pazymius " << endl;
        cout << "4 - baigti darba " << endl;
        cout << "5 - failo generavimas " << endl;
        cout << "6 - konteineriu uzpildymas" << endl;
        eiga = getInput<int,1,6>(
            "Jusu pasirinkimas: ",
            "Iveskite skaiciu nuo 1 iki 6."
        );
        if(eiga == 6) {
            lyginti_perskirstymus();
            return 0;
        }
        if(eiga == 4) {
            cout << "Darbas baigtas.";
            return 0;
        }
        if(eiga == 5) {
            for(int i = 0; i < 5; i++) {
            string gen_failas;
            cout << "Iveskite kiek irasu faile noretumet: ";
            cin >> gen_failas;
            failu_generavimas(gen_failas + ".txt");
            }
            return 0;
        }
        stud_skaicius = getInput<int,1>(
            "Kiek yra studentu? ", 
            "Iveskite teigiama skaiciu."
        );
        while(true) {
            string vard, pavard;
            vector<int> paz_temp;
            int egz_temp;
            if(eiga == 1 || eiga == 2) {
                vard = getWordInput(
                    "Iveskite varda: ",
                    "Vardas turi buti sudarytas tik is raidziu."
                );
                pavard = getWordInput(
                    "Iveskite pavarde: ",
                    "Pavarde turi buti sudaryta tik is raidziu."
                );
            }
            else if(eiga == 3) {
                zmogus z = gen();
                vard = z.vardas;
                pavard = z.pavarde;
                cout << "Sugeneruotas zmogus: " << vard << " " << pavard << endl;
            }
            if(eiga == 1) {
                while(true) {
                    temp = getInput<int,0,10>(
                        "Iveskite " + std::to_string(paz_temp.size() + 1) + " semestro pazymi (0 - baigti): ",
                        "Iveskite skaiciu tarp 0 ir 10"
                    );
                    if(temp == 0) break;
                    paz_temp.push_back(temp);
                }
                egz_temp = getInput<int,1,10>(
                    "Iveskite egzamino pazymi: ", 
                    "Iveskite skaiciu tarp 1 ir 10."
                );
            }
            else if(eiga == 2 || eiga == 3) {
                int paz_kiek;
                paz_kiek = getInput<int,0>(
                    "Kiek pazymiu sugeneruoti? ",
                    "Iveskite teigiama sveika skaiciu."
                );
                for(int i = 0; i < paz_kiek; i++) {
                    temp = rand() % 10 + 1;
                    cout << i+1 << " Sugeneruotas pazymys: " << temp << endl;
                    paz_temp.push_back(temp);
                }
                egz_temp = rand() % 10 + 1;
                cout << "Sugeneruotas egzamino pazymys: " << egz_temp << endl;
            }
            stringstream ss;
            ss << vard << " " << pavard;
            for(int i = 0; i < paz_temp.size(); i++) {
                ss << " " << paz_temp[i];
            }
            ss << " " << egz_temp;
            Studentas S;
            ss >> S;
            A.push_back(move(S));
            string student_choice;
            while(true) {
                if(index < stud_skaicius - 1) break;
                else {
                    cout << "Ar noretumet ivesti dar viena studenta? (t/n) ";
                    student_choice = raide_choice(
                        "Iveskite t arba n"
                    );
                    if(student_choice == "t" || student_choice == "T") {
                        stud_skaicius++;
                    }
                    break;
                }
            }
            index++;
            if(index >= stud_skaicius) break;
        }
        outputas(A, stud_skaicius, 0, "");
        system("pause");
    }
}
void outputas(vector<Studentas>& A, int stud_skaicius, double test_time, string filename) {
    int grade_choice;
    grade_choice = getInput<int,1,2>(
        "Isvesti vidurki ar mediana? (1 - vidurkis, 2 - mediana) ",
        "Iveskite 1 arba 2."
    );
    double (*strategija)(vector<int>&);
    (grade_choice == 1)? strategija = vidurkis : strategija = mediana;
    auto s = high_resolution_clock::now();
    for(int i = 0; i < stud_skaicius; i++) {
        A[i].skaiciuotiRez(strategija);
    }
    auto e = high_resolution_clock::now();
    duration<double> t = e - s;
    cout << "Ar norite atskirti vargsiukus nuo kietiaku? (t/n) ";
    string divide_choice;
    divide_choice = raide_choice(
        "Iveskite t arba n"
    );
    int sort_choice;
    sort_choice = getInput<int,1,3>(
        "Kaip surusiuoti rezultatus? (1 - pagal varda, 2 - pagal pavarde, 3 - pagal galutini bala) ",
        "Iveskite 1, 2 arba 3."
    );
    if(divide_choice == "t" || divide_choice == "T") {
        int divide_strategy;
        cout << "Kuria skaidymo strategija norite naudoti? " << endl;
        cout << "1 - Du nauji konteineriai " << endl;
        cout << "2 - Vienas naujas konteineris " << endl;
        cout << "3 - Efektyvus darbus su konteineriais " << endl;
        divide_strategy = getInput<int,1,3>(
            "Jusu pasirinkimas: ",
            "Iveskite 1, 2 arba 3."
        );
        auto start1 = high_resolution_clock::now();
        rusiavimas(A, sort_choice);
        auto end1 = high_resolution_clock::now();
        duration<double> diff1 = end1 - start1;
        vector<Studentas> vargsiukai;
        vector<Studentas> kietiakai;
        auto start2 = high_resolution_clock::now();
        if(divide_strategy == 1) {
            vargsiukai.reserve(6000000);
            kietiakai.reserve(6000000);
            for(int i = 0; i < stud_skaicius; i++) {
                if(A[i].rez() < 5) {
                    vargsiukai.push_back(A[i]);
                }
                else {
                    kietiakai.push_back(A[i]);
                }
            }
        }
        else if(divide_strategy == 2) {
            vargsiukai.reserve(6000000);
            for(auto it = A.end(); it != A.begin();) {
                it--;
                if(it->rez() < 5) {
                    vargsiukai.push_back(*it);
                    it = A.erase(it);
                }
            }
            std::reverse(vargsiukai.begin(), vargsiukai.end());
        }
        else if(divide_strategy == 3) {
            auto split_it = std::stable_partition(A.begin(), A.end(),
                [](const Studentas& s) {
                    return s.rez() >= 5;
                }
            );
            vargsiukai.reserve(std::distance(split_it, A.end()));
            for(auto it = split_it; it != A.end(); it++) {
                vargsiukai.push_back(move(*it));
            }
            A.erase(split_it, A.end());
        }
        auto end2 = high_resolution_clock::now();
        duration<double> diff2 = end2 - start2;
        ofstream v_fout("vargsiukai.txt");
        ofstream k_fout("kietiakai.txt");
        auto start3 = high_resolution_clock::now();
        print(v_fout, grade_choice, vargsiukai, vargsiukai.size());
        auto end3 = high_resolution_clock::now();
        duration<double> diff3 = end3 - start3;
        auto start4 = high_resolution_clock::now();
        if(divide_strategy == 1) {
            print(k_fout, grade_choice, kietiakai, kietiakai.size());
        }
        else {
            print(k_fout, grade_choice, A, A.size());
        }
        auto end4 = high_resolution_clock::now();
        duration<double> diff4 = end4 - start4;
        v_fout.close();
        k_fout.close();
        cout << filename << " Failo skaitymo laikas: " << test_time << endl;
        cout << filename << " Galutiniu balu skaiciavimo laikas: " << t.count() << endl;
        cout << filename << " Rusiavimo laikas: " << diff1.count() << endl;
        cout << filename << " Vargsiuku ir kietiaku atskyrimo laikas: " << diff2.count() << endl;
        cout << filename << " Vargsiuku isvedimo i faila laikas: " << diff3.count() << endl;
        cout << filename << " Kietiaku isvedimo i faila laikas: " << diff4.count() << endl;
        cout << filename << " Testu laikas: " << test_time + diff1.count() + diff2.count() + diff3.count() + diff4.count() + t.count() << endl;
    }
    else {
        rusiavimas(A, sort_choice);
        int output_choice;
        output_choice = getInput<int,1,2>(
            "Kaip norite isvesti rezultatus? (1 - i ekrana, 2 - i faila) ",
            "Iveskite 1 arba 2."
        );
        auto start = high_resolution_clock::now();
        if(output_choice == 1) {
            print(cout, grade_choice, A, stud_skaicius);
        }
        else {
            ofstream fout("rezultatai.txt");
            print(fout, grade_choice, A, stud_skaicius);
            cout << "Rezultatai faile - rezultatai.txt" << endl;
            fout.close();
        }
        auto end = high_resolution_clock::now();
        duration<double> diff = end - start;
        cout << "Duomenu isvedimas uztruko: " << diff.count() << " sekundziu." << endl;
    }
}