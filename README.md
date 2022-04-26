# Magazyn

## Cel projektu

Program symuluje działanie magazynu. Umożliwia obsługę dostarczonych mu danych, dodawanie i usuwanie klientów/produktów,tworzenie faktur oraz graficzną reprezentację magazynu. Projekt umożliwia zareprezentowanie jak produkty są rozmieszczone w magazynie.

## Podział prac

Zespół i obecny podział odpowiedzialności:
 - Arkadiusz Kojtek - podział projektu na mniejsze obiekty, utworzenie i ich obsługa, funkcje pomocniczne do obsługi bazy danych magazynu.
 - Lidia Sobońska - łączenie poszczególnych modułów projektu, obsługa działania projektu, obiekt Storehouse, menu tekstowe, weryfikacja i recenzja  kodu, graficzny interfejs użytkownika.

## GUI
Do napisania GUI wyokrzystaliśmy bibliotekę [wxWidgets](https://www.wxwidgets.org/), która umożliwia napisanie międzyplaytformowego interfejsu graficznego. 

## Struktura projektu
Na projektu składają się następujące klasy:
1. Storehouse - klasa zawierające jako pola wszystkie pozostałe obiekty, umożlwia obsługę i kontrolę całego projektu.
2. Receipt - klasa odpowiedzialna za tworzenie faktury, zawiera metody umożliwiające dodawanie produktów do faktury, wybranie użytkownika i podliczanie kosztu.
3. ProductsContainer - klasa odpowiedzialny za przechowywanie, przesyłanie, odbieranie i obsługę listy ProductInfo
4. ProductInfo - struktura odpowiedzialna za przechowywanie produktu wraz z odpowiadającym mu klientem oraz informacjami o położeniu obiektu wewnątz magazynu
5. Client - klasa odpowiedzialna za przechowywanie informacji na temat poszczególnych klientów
6. Product - klasa bazowa poszczególnych produktów, zawiera podstawowe informacje o każdym z obiektów, klasy dziedziczące po niej to:
- ShortTerm - produkty, które przechowywane mogą być tylko przez krótki czas w innym wypadku klient zobowiązany jest zapłacić karę.
- LongTerm - produkty, które przechowywane powinny być przez długi czas, jeżeli jednak klient odbierze produkty zbyt szybko powinien zapłacić karę.
- Exclusive - produkty, przy których odiorze konieczne jest podanie hasła umożliwającego rozpoznanie osoby odbierającej.
- Wholesale - produkty hurtowe, brak specjalnych zasad, dodane raczej by dać więcej różnych typów produktów. 
7. MainFrame - Klasa obsługująca GUI związane z głównym oknem
8. ExtraFrame - Klasa obsługująca GUI związane z pozostałymi oknami programu
- EntryFrame - Klasa obsługująca GUI związane z dodawaniem nowego magazynu/wybierania informacji o już istniejącym
- GetReceiptFrame - Klasa obsługująca GUI związane z odbieraniem faktury
- NewStorehouseFrame - Klasa obsługująca GUI związane z dodawaniem nowego magazynu
- NewProductFrame - Klasa obsługująca GUI związane z dodawaniem nowego produktu
- NewClientFrame - Klasa obsługująca GUI związane z klientem
## Uruchomienie i obsługa

Przy uruchomieniu programu pojawia się pierwsze okno, z niego można:
- wybrać plik zawierający informacje o już istniejącym magazynie,
- utworzyć nowy magazyn poprzez podanie informacji na jego temat,
- "Continue" uruchomiający już istniejący magazyn z pliku **storehouse.tsv**

Na podstawie tych informacji tworzony jest obiekt Storehouse. Pierwsze okno po odczytaniu danych zawiera informacje o:
- produktach, klientach i samym magazynie w postaci listy wypisanej w polu tekstowym,
- produktów i ich położeniu w magazynie w postaci mapy,
- menu umożliwiające edycję danych w magazynie (dodawanie i usuwanie obiektów z magazynu, tworzenie faktur, sortowanie magazynu)

W lewym górnym rogu znajduje się podstawowe menu umożliwiające odczyt bazy danych z pliku lub jej zapis.

Add Product oraz Add Client otwierają nowe okno, w którym można ustawić informacje o obiektach, które chcemy dodać do magazynu. Informacje to między innym data dodania dla produktów czy numer telefonu dla klientów.

Przycisk Get Receipt otwiera nowe okno zawierające dwie listy, w których umieszaczne są produkty należące do danego klienta oraz te, które już zostały przypisane do rachunku. W oknie znajdują się przyciski umożliwiające wybranie nowego klienta, dodanie i usunięcie z faktury oraz wygenerowanie pliku .txt z fakturą.

## Zamykanie programu

Zamknięcie programu zarówno przez przycisk x jak i quit powoduje zapisanie aktualnego stanu magazynu do pliku **storehouse.tsv**.

## Plik z danymi

Plik z danymi ma określoną strukturę. Każda informacja jest oddzielona tabulatorem a informacje ważne dla różnych częśći programu znajdują się w oddzielnych secjach pliku. W opisie struktury informacje opcjonalne umieszczone będą w {}, informacje, które mogą być wieloczłonowe np. nazwa klienta umieszczane są w []. Sekcje zaczynają się nazwami sekcji:
- Storehouse:
- Cost information:
- Clients:
- Products:
#### Informacje o magazynies:

|  Nazwa  |  Wymiar1  |  Wymiar2  |
|---------|-----------|-----------|
| Magazyn |    12     |    12     |

#### Informacje o kosztach:

|   Nazwa informacji    |  Wartość   |
|-----------------------|------------|
| How_Long_is_ShortTerm:|   Value    |
|  Penalty multiplier:  |   Value    |
|      LongTerm:        |   Value    |
|     ShortTerm:        |   Value    |
|     Exclusive:        |   Value    |
|     Wholesale:        |   Value    |

#### Informacje o klientach

|  ID  | [Nazwa] | [Miasto] | Numer telefonu  |
|------|---------|----------|-----------------|
|  1   | Baryka  | Kraków   | 512261772       |

#### Informacje o produktach należących do klientów

| Client_id | P1X | P1Y | P2X | P2Y | Product_type | Product_ID |[Nazwa]| Szer | Dl | Data_Pocz | {Data konc} | {Haslo} |
|-----------|-----|-----|-----|-----|--------------|------------|-------|------|----|-----------|-------------|---------|
|1          |0    |0    |3    |4    |  Exclusive   |1           |zegarek|3     |4   |13-15-2021 |13-06-2021   |Haslo123 |

## Pliki wynikowe

W trakcie działania programu pojawić się mogą pliki będące reprezentacją faktur wystawianych przez magazyn. Nazywać się będą 
"\[nazwa_klienta]_RRRR-MM-DD_hh-mm-ss.txt" 


###### Projekt realizowany w ramach przedmiotu PROI w semestrze 21L (Grupa laboratoryjna 209)
