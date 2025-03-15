#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

enum SokobanObject
{
    wall = 0,
    space = 1,
    storekeeper = 2,
    box = 3,
    delivery_point = 4,
    storekeeper_on_delivery_point = 5,
    box_on_delivery_point = 6,
};

// Struktura stanu gry
struct SokobanState {
    unsigned points;
    SokobanObject board[10][10];
};

struct Location {
    unsigned x, y;
};

// Generowanie pierwszego poziomu
SokobanState initialize_level1() {
    SokobanState state = { 10, {
            { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall },
            { wall, space, space, space, space, space, space, space, space, wall },
            { wall, space, space, space, space, space, space, space, space, wall },
            { wall, space, space, space, delivery_point, box, space, space, space, wall },
            { wall, space, space, space, delivery_point, space, space, space, space, wall },
            { wall, space, space, space, box, space, space, space, space, wall },
            { wall, space, space, space, storekeeper, space, space, space, space, wall },
            { wall, space, space, space, space, space, space, space, space, wall },
            { wall, space, space, space, space, space, space, space, space, wall },
            { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall }
        }
    };
    return state;
}

// Generowanie drugiego poziomu
SokobanState initialize_level2() {
    SokobanState state = { 35, {
            { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall },
            { wall, storekeeper, space, wall, space, space, space, wall, delivery_point, wall },
            { wall, space, space, space, wall, space, box, wall, space, wall },
            { wall, space, wall, space, wall, space, space, wall, space, wall },
            { wall, space, wall, space, space, space, space, wall, space, wall },
            { wall, space, wall, wall, space, space, space, wall, space, wall },
            { wall, space, space, space, space, space, space, space, space, wall },
            { wall, space, space, wall, wall, space, wall, space, space, wall },
            { wall, space, space, space, space, space, wall, space, space, wall },
            { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall }
        } 
    };
    return state;
}

// Generowanie trzeciego poziomu
SokobanState initialize_level3() {
    SokobanState state = { 45, {
            { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall },
            { wall, space, wall, space, wall, space, space, space, space, wall },
            { wall, wall, wall, space, wall, space, space, space, space, wall },
            { wall, delivery_point, space, space, wall, space, wall, space, space, wall },
            { wall, wall, space, space, wall, space, box, space, wall, wall },
            { wall, wall, space, space, space, box, space, space, space, wall },
            { wall, delivery_point, space, space, wall, wall, space, space, space, wall },
            { wall, wall, wall, space, wall, space, space, wall, space, wall },
            { wall, wall, space, space, wall, space, space, space, storekeeper, wall },
            { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall }
        } 
    };
    return state;
}

// Sprzawdź czy wygrana
bool check_if_won(SokobanState &state) {
    unsigned box_count = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (state.board[i][j] == box) {
                box_count++;
            }
        }
    }
    if (box_count == 0) {
        return true;
    }
    else {
        return false;
    }
}

// Ruch
void move(SokobanState &state, Location storekeeper_current_location, int x, int y) {
    
    SokobanObject storekeeper_current_location_object = state.board[storekeeper_current_location.x][storekeeper_current_location.y];

    Location next_location = { storekeeper_current_location.x + x, storekeeper_current_location.y + y };
    SokobanObject next_location_object = state.board[next_location.x][next_location.y];
    if (next_location_object != wall) {
        if (next_location_object == box) {
            Location box_next_location = { next_location.x + x, next_location.y + y};
            SokobanObject box_next_location_object = state.board[box_next_location.x][box_next_location.y];
            if (box_next_location_object != wall && box_next_location_object != box && box_next_location_object != box_on_delivery_point) {
                if (box_next_location_object == delivery_point) {
                    if (storekeeper_current_location_object == storekeeper) {
                        state.board[storekeeper_current_location.x][storekeeper_current_location.y] = space;
                    }
                    else {
                        state.board[storekeeper_current_location.x][storekeeper_current_location.y] = delivery_point;
                    }
                    state.board[box_next_location.x][box_next_location.y] = box_on_delivery_point;
                    state.board[next_location.x][next_location.y] = storekeeper;
                }
                else {
                    if (storekeeper_current_location_object == storekeeper) {
                        state.board[storekeeper_current_location.x][storekeeper_current_location.y] = space;
                    }
                    else {
                        state.board[storekeeper_current_location.x][storekeeper_current_location.y] = delivery_point;
                    }
                    state.board[box_next_location.x][box_next_location.y] = box;
                    state.board[next_location.x][next_location.y] = storekeeper;
                }
            }
        }
        else if (next_location_object == box_on_delivery_point) {
            Location box_next_location = { next_location.x + x, next_location.y + y };
            SokobanObject box_next_location_object = state.board[box_next_location.x][box_next_location.y];
            if (box_next_location_object != wall && box_next_location_object != box && box_next_location_object != box_on_delivery_point) {
                if (box_next_location_object == delivery_point) {
                    if (storekeeper_current_location_object == storekeeper) {
                        state.board[storekeeper_current_location.x][storekeeper_current_location.y] = space;
                    }
                    else {
                        state.board[storekeeper_current_location.x][storekeeper_current_location.y] = delivery_point;
                    }
                    state.board[box_next_location.x][box_next_location.y] = box_on_delivery_point;
                    state.board[next_location.x][next_location.y] = storekeeper_on_delivery_point;
                }
                else {
                    if (storekeeper_current_location_object == storekeeper) {
                        state.board[storekeeper_current_location.x][storekeeper_current_location.y] = space;
                    }
                    else {
                        state.board[storekeeper_current_location.x][storekeeper_current_location.y] = delivery_point;
                    }
                    state.board[box_next_location.x][box_next_location.y] = box;
                    state.board[next_location.x][next_location.y] = storekeeper_on_delivery_point;
                }
            }
        }
        else {
            if (storekeeper_current_location_object == storekeeper) {
                state.board[storekeeper_current_location.x][storekeeper_current_location.y] = space;
            }
            else {
                state.board[storekeeper_current_location.x][storekeeper_current_location.y] = delivery_point;
            }
            if (next_location_object == delivery_point) {
                state.board[next_location.x][next_location.y] = storekeeper_on_delivery_point;
            }
            else {
                state.board[next_location.x][next_location.y] = storekeeper;
            }
        }
    }
    state.points--;
}

// Znajduje magazyniera
Location find_storekeeper(SokobanState &state) {
    for (unsigned i = 0; i < 10; i++) {
        for (unsigned j = 0; j < 10; j++) {
            if (state.board[i][j] == storekeeper || state.board[i][j] == storekeeper_on_delivery_point) {
                return { i,j };
            }
        }
    }
}

// Wyświetla zawartość planszy na ekranie
void print_board(SokobanState &state) {
    cout << endl;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            switch (state.board[i][j])
            {
            case wall:
                cout << (char)176 << " ";
                break;
            case storekeeper:
                cout << (char)219 << " ";
                break;
            case box:
                cout << (char)35 << " ";
                break;
            case delivery_point:
                cout << (char)88 << " ";
                break;
            case storekeeper_on_delivery_point:
                cout << (char)219 << " ";
                break;
            case box_on_delivery_point:
                cout << (char)36 << " ";
                break;
            default:
                 cout << "  ";
                break;
            }
        }
        cout << endl;
    }
}

// Wyświetla punkty energii
void print_points(SokobanState &state) {
    cout << "Pozostala ilosc ruchow: " << state.points << endl;
}

// Ekran startowy (menu)
void menu(SokobanState &state) {
    system("CLS");
    // Instrukcja powitalna gry
    cout << R"(                    
| |     / (_) /_____ _  (_)  _      __   ____ __________  ___ 
| | /| / / / __/ __ `/ / /  | | /| / /  / __ `/ ___/_  / / _ \
| |/ |/ / / /_/ /_/ / / /   | |/ |/ /  / /_/ / /    / /_/  __/
|__/|__/_/\__/\__,_/_/ /    |__/|__/   \__, /_/    /___/\___/ 
                  /___/               /____/                  
   _____ ____  __ ______  ____  ___    _   __
  / ___// __ \/ //_/ __ \/ __ )/   |  / | / /
  \__ \/ / / / ,< / / / / __  / /| | /  |/ / 
 ___/ / /_/ / /| / /_/ / /_/ / ___ |/ /|  /  
/____/\____/_/ |_\____/_____/_/  |_/_/ |_/   
)" << endl << endl;
    cout << "Zostales zatrudniony jako magazynier w naszej firmie SOKOBAN, twoim zadaniem na dzis jest sprawienie," << endl;
    cout << "by wszystkie skrzynki znalazly sie w odpowiednio wyznaczonym miejscu." << endl;
    cout << "Uwazaj!" << endl;
    cout << "Skrzynki sa niestety za ciezkie, aby je poprzenosic, wiec pozostalo Ci jedynie po kolei je poprzepychac" << endl;
    cout << "Niesteyt na naszym magazynie jest duzy balagan, wiec licz sie z tym, ze bedziesz musial omijac przeszkody" << endl;
    cout << "Powodzenia!" << endl << endl;
    cout << R"(
    __  ___                
   /  |/  /__  ____  __  __
  / /|_/ / _ \/ __ \/ / / /
 / /  / /  __/ / / / /_/ / 
/_/  /_/\___/_/ /_/\__,_/     
)" << endl;
    cout << "0. Wyjdz" << endl << "1. Rozpocznij gre poziom 1" << endl << "2. Rozpocznij gre poziom 2" << endl << "3. Rozpocznij gre poziom 3 " << endl;

    char choice;
    cin >> choice;

    switch (choice)
    {
    case '0':
        exit(0);
        break;
    case '1':
        state = initialize_level1();
        break;
    case '2':
        state = initialize_level2();
        break;
    case '3':
        state = initialize_level3();
        break;
    default:
        menu(state);
    }
}


int main () {
    SokobanState state;

    menu(state);

    char key;

    do {
        system("CLS");
        print_board(state);

        // Legenda gry
        cout << "1. " << (char)219 << " - to Ty" << endl;
        cout << "2. " << (char)35 << " - Skrzynka" << endl;
        cout << "4. " << (char)88 << " - Miejsce dostarczenia" << endl;
        cout << "3. " << (char)36 << " - Skrzynka w odpowiednim miejscu" << endl << endl;

        print_points(state);
        cout << endl;
        do {
            cout << "Powrot do menu - Q" << endl;
            cout << "Nawigacja ruchu 'WSAD' (W - gora, A - lewo, S - dol, D - prawo): ";
            cin >> key;
        } while (key != 'W' && key != 'w' && key != 'S' && key != 's' && key != 'D' && key != 'd' && key != 'A' && key != 'a' && key != 'Q' && key != 'q');
        if (key == 'w' || key == 'W')
            move(state, find_storekeeper(state), -1, 0);
        else if (key == 's' || key == 'S')
            move(state, find_storekeeper(state), 1, 0);
        else if (key == 'd' || key == 'D')
            move(state, find_storekeeper(state), 0, 1);
        else if (key == 'a' || key == 'A')
            move(state, find_storekeeper(state), 0, -1);
        else if (key == 'q' || key == 'Q')
            menu(state);
    } while (state.points > 0 && !check_if_won(state));

    if (check_if_won(state)) {
        print_board(state);
        cout << endl << "Gratulacje, wygrales!" << endl;
    }
    else
        cout << endl << "Niestety przegrales." << endl;

    return 0;
}
