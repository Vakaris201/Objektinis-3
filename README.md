NAUDOJIMOSI INSTRUKCIJA 
1. Darbo eiga / Naudojimas

Programa paklaus: "Ar noretumet skaityti duomenis is failo? (t/n)"
Jei atsakote `t`, bus paprašyta nurodyti failo pavadinimą. Programa perskaitys visus įrašus ir apdoros rezultatus.

2. Jei atsakote `n`, matysite meniu:
```
1 - ranka: vėliau bus prašoma vardo, pavardės ir pažymių
2 - generuoti tik pažymius: programa sugeneruos nurodytą kiekį pažymių
3 - generuoti studentų vardus, pavardes ir pažymius
4 - baigti darbą
5 - failo generavimas: programa paklaus kiek įrašų faile norėtumėte, ir sukurs failus pavadinimais <skaicius>.txt
6 - palyginti kiek kartu isaugo atminti uzpildant Vector ir std::vector konteinerius
```
3. Po duomenų surinkimo programa prašys pasirinkti, kaip skaičiuoti galutinį balą:
```
1 - vidurkis
2 - mediana
```
4. Programa paklaus ar norite atskirti vargsiukus nuo kietiaku (`t/n`). Jei taip, galimi skaidymo metodai:
```
1 - du nauji konteineriai
2 - vienas naujas konteineris 
3 - efektyvus darbas su konteineriais 
```
5. Rušiavimo pasirinkimai:
```
1 - pagal vardą
2 - pagal pavardę
3 - pagal galutinį balą.
```
6. Išvedimas
```
1 - į ekraną
2 - į failą (rezultatai.txt)
Jei pasirenkate atskyrimo funkcionalumą, rezultatai bus rašomi į vargsiukai.txt ir kietiakai.txt
```

VECTOR KLASĖS FUNKCIJŲ APRAŠYMAS
1. Funkcija: `reallocate()`
     - Perskirsto atmintį į didesnį bloką ir perkelia esamus elementus.
     - Kode su `allocate(new_capacity)` sukuriamas naujas atminties blokas, tuomet ciklu per esamus elementus kviečiama `construct_at(new_data + i, std::move(data_[i]))` kad elementai būtų sukurti naujoje vietoje, po to senoje vietoje kviečiama `destroy_at()` ir galiausiai sena atmintis deallocinama su `deallocate()`. Galiausiai atnaujinami `data_` ir `capacity_` nariai.

2. Funkcija: `push_back()`
     - Prideda naują elementą į vektoriaus pabaigą.
     - Kode pirmiausia patikrinama, ar reikia padidinti talpą su `grow_if_needed()`. Jei vietos trūksta, iškviečiamas `reallocate()`, kuris sukuria didesnį masyvą ir perkelia senus elementus. Tada naujas elementas įdedamas į vietą `data_ + size_`, o `size_` padidinamas.

3. Funkcija: `resize()`
     - Pakeičia vektoriaus dydį į nurodytą reikšmę.
     - Kode, jei naujas dydis mažesnis, vyksta ciklas per perteklinius elementus ir jie sunaikinami su `destroy_at()`. Jei dydis didesnis, prireikus iškviečiamas `reallocate()`, o po to nauji elementai sukuriami su `construct_at()` ir užpildomi numatyta reikšme.

4. Funkcija: `insert()` (range overload)
     - Įterpia elementus iš intervalo `[first, last)` į nurodytą poziciją.
     - Kode apskaičiuojamas intervalo ilgis (`std::distance`), jei reikia perskirstoma atmintis, tada esami elementai yra pastumiami į dešinę, kad būtų vietos naujiems. Tada pereinama per pateiktą intervalą ir kiekvienas elementas kopijuojamas ar konstruojamas naujoje vietoje su `construct_at`. Pasibaigus įterpimui atnaujinamas `size_`.

5. Funkcija: `erase()`
     - Ištrina vieną elementą arba elementų intervalą iš vektoriaus.
     - Kode nustatomas trinamo intervalo ilgis, ištrinami tiksliniai elementai su `destroy_at()`, o likę elementai perkelti į ankstesnes pozicijas, kad vektoriaus viduje neliktų tarpų.

SPARTOS ANALIZĖ 1
```
10000
std::vector| 0.0000955  0.0000971  0.0000989  VIDURKIS: 0.0000972
     Vector| 0.0002361  0.0002378  0.0002364  VIDURKIS: 0.0002368
```
```
100000
std::vector| 0.0007214  0.0007328  0.0007481  VIDURKIS: 0.0007341
     Vector| 0.0019603  0.0019655  0.0019742  VIDURKIS: 0.0019667
```
```
1000000
std::vector| 0.0063360  0.0067428  0.0064534  VIDURKIS: 0.0065107
     Vector| 0.0177377  0.0186053  0.0173773  VIDURKIS: 0.0179068
```
```
10000000
std::vector| 0.0717720  0.0660837  0.0660015  VIDURKIS: 0.0679524
     Vector| 0.2280760  0.2284510  0.2289040  VIDURKIS: 0.228477
```
```
100000000
std::vector| 0.659925    0.634871  0.618443   VIDURKIS: 0.637746
     Vector| 1.957130    1.9552    1.93473    VIDURKIS: 1.94902
```
SPARTOS ANALIZĖ 2

Vector
```
100000
                 Failo skaitymo laikas:  0.113895,   0.114527,   0.116082  VIDURKIS:  0.1148346
     Galutiniu balu skaiciavimo laikas: 0.0139388,  0.0134397,  0.0137309  VIDURKIS:  0.0137031
                      Rusiavimo laikas: 0.0503581,  0.0516286,  0.0519384  VIDURKIS:  0.0513083
Vargsiuku ir kietiaku atskyrimo laikas:  0.007287,  0.0074071,  0.0069851  VIDURKIS:  0.0072264
     Vargsiuku isvedimo i faila laikas:  0.189078,    0.19023,   0.186137  VIDURKIS:  0.1884816
      Kietiaku isvedimo i faila laikas:  0.141841,   0.139969,   0.141483  VIDURKIS:  0.1410976
                          Testu laikas:  0.516398,   0.517202,   0.516356  VIDURKIS:   0.516652
``` 
``` 
1000000
                 Failo skaitymo laikas:   1.09894,    1.10397,    1.12693  VIDURKIS:  1.109946
     Galutiniu balu skaiciavimo laikas:  0.128716,   0.129094,   0.129875  VIDURKIS:  0.129228
                      Rusiavimo laikas:  0.613396,   0.615417,     0.6149  VIDURKIS:  0.614571
Vargsiuku ir kietiaku atskyrimo laikas:  0.066662,   0.066240,   0.065431  VIDURKIS:  0.066111
     Vargsiuku isvedimo i faila laikas:    1.8398,    1.79789,    1.83126  VIDURKIS:  1.822983
      Kietiaku isvedimo i faila laikas:    1.3505,    1.37154,    1.36883  VIDURKIS:  1.363623
                          Testu laikas:   5.09802,    5.08414,    5.13723  VIDURKIS:  5.106463
``` 
```
10000000
                 Failo skaitymo laikas:    11.029,    11.1691,    11.1565  VIDURKIS:   11.1182
     Galutiniu balu skaiciavimo laikas:   1.29395,    1.28416,    1.28177  VIDURKIS:  1.286626
                      Rusiavimo laikas:    7.4761,     7.5503,     7.5685  VIDURKIS:  7.531633
Vargsiuku ir kietiaku atskyrimo laikas:   0.736773,  0.642011,   0.695389  VIDURKIS:  0.691391
     Vargsiuku isvedimo i faila laikas:    20.2053,   18.8288,    18.8916  VIDURKIS:  19.30856
      Kietiaku isvedimo i faila laikas:    13.9154,   13.7182,    13.7636  VIDURKIS:  13.79906
                          Testu laikas:    54.6565,   53.1926,    53.3574  VIDURKIS:   53.7355
```

std::vector
```
100000
                 Failo skaitymo laikas:   0.139034,   0.13756,   0.137486  VIDURKIS:   0.138026
     Galutiniu balu skaiciavimo laikas:  0.0187007,  0.017131,  0.0174734  VIDURKIS:  0.0177683
                      Rusiavimo laikas:   0.107758,  0.106861,   0.107869  VIDURKIS:   0.107496
Vargsiuku ir kietiaku atskyrimo laikas:  0.0136334,  0.013666,  0.0136743  VIDURKIS:  0.0136579
     Vargsiuku isvedimo i faila laikas:   0.197243,  0.196224,    0.18892  VIDURKIS:   0.194129
      Kietiaku isvedimo i faila laikas:   0.138525,  0.143498,   0.134985  VIDURKIS:   0.139002
                          Testu laikas:   0.614894,   0.61494,   0.600407  VIDURKIS:  0.6100803
```
```
1000000
                 Failo skaitymo laikas:    1.32716,   1.33357,    1.35874  VIDURKIS:   1.339823
     Galutiniu balu skaiciavimo laikas:   0.162215,  0.164438,   0.161138  VIDURKIS:   0.162597
                      Rusiavimo laikas:    1.31561,      1.32,    1.32262  VIDURKIS:    1.31941
Vargsiuku ir kietiaku atskyrimo laikas:   0.128005,   0.12859,   0.128736  VIDURKIS:  0.1284436
     Vargsiuku isvedimo i faila laikas:    1.85742,   1.83601,    1.81732  VIDURKIS:   1.836916
      Kietiaku isvedimo i faila laikas:    1.37296,   1.35478,    1.36461  VIDURKIS:  1.3641166
                          Testu laikas:    6.16337,   6.13739,    6.15317  VIDURKIS:    6.15131
```
```
10000000
                 Failo skaitymo laikas:       13.2,   13.2082,    13.4111  VIDURKIS:   13.2731
     Galutiniu balu skaiciavimo laikas:    1.64137,   1.62551,    1.66239  VIDURKIS:   1.64309
                      Rusiavimo laikas:    16.2251,   16.2718,    16.6335  VIDURKIS:   16.3768
Vargsiuku ir kietiaku atskyrimo laikas:    1.37901,   1.35686,    1.36426  VIDURKIS:   1.36671
     Vargsiuku isvedimo i faila laikas:    18.7869,   19.3813,    20.1343  VIDURKIS:  19.43416
      Kietiaku isvedimo i faila laikas:    13.6337,   13.6769,    13.9947  VIDURKIS:  13.76843
                          Testu laikas:    64.8661,   65.5206,    67.2002  VIDURKIS:   65.8623
```
