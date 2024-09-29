#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Patro de disseny d'State
class GameState {
public:
    virtual void pullTrigger() = 0;
    virtual ~GameState() = default;
};

class EstatSalvat : public GameState {
public:
    void pullTrigger() override {
        cout << "Clic! T'has salvat, per ara.\n";
    }
};

class EstatMort : public GameState {//Estat Mort
public:
    void pullTrigger() override {
        cout << "Bang! Has mort!\n";
    }
};

class Ruleta {
public:
    Ruleta() : state(new EstatSalvat()) {
        srand(static_cast<unsigned>(std::time(nullptr)));
        Posiciobala = std::rand() % 6;//Posicio random de la bala
        Posicioactual = 0;
    }

    ~Ruleta() {
        delete state;
    }

    void pullTrigger() {//Apretar Gallet
        if (Posicioactual == Posiciobala) {
            changeState(new EstatMort());
        }
        state->pullTrigger();
        Posicioactual++;
    }

private:
    void changeState(GameState* newState) {
        delete state;
        state = newState;
    }

    GameState* state;
    int Posiciobala;
    int Posicioactual;
};

//Inici del joc en si
int main() {
    Ruleta game;
    char opcio;

    cout << "Benvingut a la Ruleta Russa!\n";
    cout << "Prem 'd' per disparar o 'e' per sortir.\n";

    while (true) {
        cout << "Que vols fer?: ";
        cin >> opcio;

        if (opcio == 'd') {
            game.pullTrigger();
        }
        else if (opcio == 'e') {
            cout << "Bye Bye!\n";
            break;
        }
        else {
            cout << "ERROR. Torna a intentar-ho.\n";
        }
    }

    return 0;
}
