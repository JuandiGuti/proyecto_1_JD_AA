#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//al ejecutarlo hacer scroll hacia arriba 

class Node {
public:
    string data;
    Node* next;
    Node(string data) {
        this->data = data;
        next = NULL;
    }
};
class Stack {
private:
    Node* top;
public:
    Stack() {
        top = NULL;
    }
    void push(string data) {
        Node* n = new Node(data);
        if (top == NULL) {
            top = n;
        }
        else {
            n->next = top;
            top = n;
        }
    }
    string pop() {
        if (top == NULL) {
            cout << "stack is empty" << endl;
            return "";
        }
        else {
            string temData = top->data;
            Node* temp = top;
            top = top->next;
            delete temp;
            return temData;
        }
    }
    bool isEmpty() {
        if (top == NULL) {
            return true;
        }
        else {
            return false;
        }
    }
    ~Stack() {
        Node* next;
        while (top != NULL) {
            next = top->next;
            delete top;
            top = next;
        }
    }
};

int get_song_artist_list(string list_songs[], string list_artist[]) {
    string nombreArchivo = "playlist.csv";
    ifstream archivo(nombreArchivo);
    string linea;
    char delimitador = ',';
    int contador = 0;
    getline(archivo, linea);
    while (getline(archivo, linea)) {
        stringstream stream(linea);
        string song, artist;
        while (getline(stream, song, delimitador) && getline(stream, artist, delimitador)) {
            list_songs[contador] = song;
            list_artist[contador] = artist;
        }
        contador++;
    }
    return contador;
}

void play() {

}


int main() {
    string list_songs[10];
    string list_artist[10];
    string list_song_artist[10][2];

    int songs_num = get_song_artist_list(list_songs, list_artist);

    Stack pila_tem_songs;
    Stack pila_tem_artist;
    //colas de reproduccion correctas 
    Stack pila_rep_songs;
    Stack pila_rep_artists;
    //historial de reproduccion
    Stack history_song, history_artist;

start:
    for (int i = 0; i < songs_num; i++) {
        pila_tem_songs.push(list_songs[i]);
        pila_tem_artist.push(list_artist[i]);
    }
    for (int i = 0; i < songs_num; i++) {
        pila_rep_songs.push(pila_tem_songs.pop());
        pila_rep_artists.push(pila_tem_artist.pop());
    }

    for (int i = 0; i < songs_num; i++) {
        for (int j = 0; j < 2; j++) {
            if (j == 0) {
                list_song_artist[i][j] = list_songs[i];
            }
            else {
                list_song_artist[i][j] = list_artist[i];
            }
        }
    }

    string menu;
    string song = "Pulse the option num. 1 to start";
    string artist = "-";


    //op.1
    bool already_start = false;
    //op.2
    int num_song;
    //op.3 y op.4
    string prev_song;
    string prev_artist;
    //op.5
    string byartsong, ascordes;
    //op.6
    string songs_name, artist_name;

menu:
    //interface
    cout << "PARTY LOADER!" << endl;
    for (int i = 0; i < songs_num; i++) {
        cout << "num. " << i + 1 << endl;
        for (int j = 0; j < 2; j++) {
            if (j == 0) {
                cout << "song:" << list_song_artist[i][j] << endl;
            }
            else {
                if (list_song_artist[i][j] == "z") {
                    cout << "artist:" << "unknown" << endl;
                }
                else
                {
                    cout << "artist:" << list_song_artist[i][j] << endl;
                }
            }
        }
    }

    cout << endl;
    cout << "Playing now: " << song << endl;
    cout << "By: " << artist << endl;
    cout << endl;
    //options menu
    cout << "1. Play Now" << endl;
    cout << "2. Select a Song" << endl;
    cout << "3. Next Song" << endl;
    cout << "4. Previous Song" << endl;
    cout << "5. Sort List" << endl;
    cout << "6. Add Song" << endl;
    cout << "7. Delete Song" << endl;
    cout << "8. Back to the original list" << endl;
    cout << "9. Save the playlist \"in the program folder\"" << endl;
    cout << "10. End the party :(" << endl;
    cout << endl;
    cout << "Choose an option" << endl;
    cin >> menu;
    if (menu == "1") {
        system("CLS");
        if (already_start == false) {
            //desarrollo
            cout << "Option Selected: Play Option" << endl;
            song = pila_rep_songs.pop();
            artist = pila_rep_artists.pop();
            already_start = true;

            //return
            goto menu;
        }
        else {
            //return
            cout << "The party already started!" << endl;
            goto menu;
        }

    }
    else if (menu == "2") {
        system("CLS");
        already_start = true;
        bool un_artist = false;
        cout << "Option Selected: Select a Song" << endl;
        for (int i = 0; i < songs_num; i++) {
            cout << "num. " << i + 1 << endl;
            for (int j = 0; j < 2; j++) {
                if (j == 0) {
                    cout << "song:" << list_song_artist[i][j] << endl;
                }
                else {
                    cout << "artist:" << list_song_artist[i][j] << endl;
                }
            }
        }
        cout << "Pick the number of the song in the list..." << endl;
        cin >> num_song;
        num_song--;

        song = list_song_artist[num_song][0];
        artist = list_song_artist[num_song][1];

        history_song.push(song);
        history_artist.push(artist);
        system("CLS");
        cout << "Option Selected: Select a Song" << endl;
        goto menu;

    }
    else if (menu == "3") {
        system("CLS");
        if (song == "Pulse the option num. 1 to start") {
            cout << "Option Selected: Next Song Option" << endl;
            cout << "Pulse the option num. 1 to start" << endl;
            goto menu;
        }
        else if (history_song.isEmpty() && pila_rep_songs.isEmpty()) {
            cout << "Option Selected: Next Song Option" << endl;
            cout << "You have no more music... but the party does not stop so we decide to start again!" << endl;
            goto start;
        }
        else if (!pila_rep_songs.isEmpty()) {
            cout << "Option Selected: Next Song Option" << endl;
            prev_song = song;
            prev_artist = artist;

            history_song.push(prev_song);
            history_artist.push(prev_artist);

            artist = pila_rep_artists.pop();
            song = pila_rep_songs.pop();


            goto menu;
        }
        else {
            cout << "Option Selected: Next Song Option" << endl;
            cout << "Now playing history quoe..." << endl;
            song = history_song.pop();
            artist = history_artist.pop();
            goto menu;
        }

    }
    else if (menu == "4") {
        system("CLS");
        if (song == "Pulse the option num. 1 to start") {
            cout << "Option Selected: Next Song Option" << endl;
            cout << "Pulse the option num. 1 to start" << endl;
            goto menu;
        }
        else if (!history_song.isEmpty() && !pila_rep_songs.isEmpty()) {
            cout << "Option Selected: Previous Song Option" << endl;

            pila_rep_songs.push(prev_song);
            pila_rep_artists.push(prev_artist);

            prev_song = song;
            prev_artist = artist;

            song = pila_rep_songs.pop();
            artist = pila_rep_artists.pop();

            history_song.push(prev_song);
            history_artist.push(prev_artist);

            goto menu;

        }
        else if (!history_song.isEmpty() && pila_rep_songs.isEmpty()) {
            cout << "Option Selected: Previous Song Option" << endl;

            history_song.push(prev_song);
            history_artist.push(prev_artist);

            prev_song = song;
            prev_artist = artist;

            song = history_song.pop();
            artist = history_artist.pop();
            if (artist == "z") {
                artist = "Unknown";
            }
            goto menu;
        }
        else {
            cout << "Option Selected: Previous Song Option" << endl;
            cout << "There is not any previuos songs!" << endl;
            goto menu;
        }

    }
    else if (menu == "5") {
        system("CLS");
        cout << "Option Selected: Sort List" << endl;

        cout << "1. By Song" << endl;
        cout << "2. By Artist" << endl;
        cin >> byartsong;
        cout << "1. Ascendent" << endl;
        cout << "2. Descendet" << endl;
        cin >> ascordes;

        string auxsong, auxartist;

        if (byartsong == "1" && ascordes == "1") {
            cout << "Sort by. Song and Ascendent" << endl;
            for (int i = 0; i < (songs_num - 1); i++) {
                for (int j = i + 1; j < songs_num; j++) {
                    if (list_song_artist[i][0] > list_song_artist[j][0]) {

                        auxsong = list_song_artist[j][0];
                        auxartist = list_song_artist[j][1];

                        list_song_artist[j][0] = list_song_artist[i][0];
                        list_song_artist[j][1] = list_song_artist[i][1];

                        list_song_artist[i][0] = auxsong;
                        list_song_artist[i][1] = auxartist;
                    }
                }
            }
            system("CLS");
            cout << "Sort by. Song and Ascendent" << endl;
            goto menu;
        }
        else if (byartsong == "1" && ascordes == "2") {
            cout << "Sort by. Song and Descendet" << endl;
            for (int i = 0; i < (songs_num - 1); i++) {
                for (int j = i + 1; j < songs_num; j++) {
                    if (list_song_artist[i][0] < list_song_artist[j][0]) {

                        auxsong = list_song_artist[j][0];
                        auxartist = list_song_artist[j][1];

                        list_song_artist[j][0] = list_song_artist[i][0];
                        list_song_artist[j][1] = list_song_artist[i][1];

                        list_song_artist[i][0] = auxsong;
                        list_song_artist[i][1] = auxartist;
                    }
                }
            }
            system("CLS");
            cout << "Sort by. Song and Descendet" << endl;
            goto menu;
        }
        else if (byartsong == "2" && ascordes == "1") {
            cout << "Sort by. Artist and Ascendent" << endl;
            for (int i = 0; i < (songs_num - 1); i++) {
                for (int j = i + 1; j < songs_num; j++) {
                    if (list_song_artist[i][1] == "unknown") {
                        list_song_artist[i][1] = "|unknown";
                    }
                    else if (list_song_artist[i][1] > list_song_artist[j][1]) {

                        auxsong = list_song_artist[j][0];
                        auxartist = list_song_artist[j][1];

                        list_song_artist[j][0] = list_song_artist[i][0];
                        list_song_artist[j][1] = list_song_artist[i][1];

                        list_song_artist[i][0] = auxsong;
                        list_song_artist[i][1] = auxartist;
                    }
                }
            }
            system("CLS");
            cout << "Sort by. Artist and Ascendent" << endl;
            goto menu;
        }
        else if (byartsong == "2" && ascordes == "2") {
            cout << "Sort by. Artist and Descendet" << endl;
            for (int i = 0; i < (songs_num - 1); i++) {
                for (int j = i + 1; j < songs_num; j++) {
                    if (list_song_artist[i][1] == "unknown") {
                        list_song_artist[i][1] = "/unknown";
                    }
                    else if (list_song_artist[i][1] < list_song_artist[j][1]) {

                        auxsong = list_song_artist[j][0];
                        auxartist = list_song_artist[j][1];

                        list_song_artist[j][0] = list_song_artist[i][0];
                        list_song_artist[j][1] = list_song_artist[i][1];

                        list_song_artist[i][0] = auxsong;
                        list_song_artist[i][1] = auxartist;
                    }
                }
            }
            system("CLS");
            cout << "Sort by. Artist and Descendet" << endl;
            goto menu;
        }
        else {
            cout << "error" << endl;
        }
    }
    else if (menu == "6") {
        system("CLS");
        if (songs_num < 10) {
            cout << "Option Selected: Add Song" << endl;
            cout << "Insert the Songs Name..." << endl;
            cin >> songs_name;
            cout << "Insert the Artist Name..." << endl;
            cin >> artist_name;

            list_songs[songs_num] = songs_name;
            list_artist[songs_num] = artist_name;

            pila_rep_songs.push(songs_name);
            pila_rep_artists.push(artist_name);

            song = pila_rep_songs.pop();
            artist = pila_rep_artists.pop();

            for (int i = 0; i <= songs_num; i++) {
                for (int j = 0; j < 2; j++) {
                    if (list_song_artist[i][j] == "") {
                        if (j == 0) {
                            list_song_artist[i][j] = song;
                        }
                        else {
                            list_song_artist[i][j] = artist;
                        }
                    }
                }
            }

            songs_num++;
            system("CLS");
            cout << "Song Added and playing..." << endl;
            goto menu;
        }
        else {
            cout << "Option Selected: Add Song" << endl;
            cout << "Our servers free are full pay $10 per/month to get more space for songs!" << endl;
            goto menu;
        }

    }
    else if (menu == "7") {
        system("CLS");
        cout << "Option Selected: Next Song Option" << endl;
        for (int i = 0; i < songs_num; i++) {
            cout << "num. " << i + 1 << endl;
            for (int j = 0; j < 2; j++) {
                if (j == 0) {
                    cout << "song:" << list_song_artist[i][j] << endl;
                }
                else {
                    cout << "artist:" << list_song_artist[i][j] << endl;
                }
            }
        }
        cout << "Pick the number of the song in the list..." << endl;
        cin >> num_song;
        num_song--;
        for (int i = 0; i < songs_num; i++) {
            for (int j = 0; j < 2; j++) {
                if (list_song_artist[num_song][0] == list_song_artist[i][j] || list_song_artist[num_song][1] == list_song_artist[i][j]) {
                    if (j == 0) {
                        //song
                        list_song_artist[i][j] = list_song_artist[(songs_num - 1)][j];
                        list_song_artist[(songs_num - 1)][j] = "";
                    }
                    else {
                        //artist
                        list_song_artist[i][j] = list_song_artist[(songs_num - 1)][j];
                        list_song_artist[(songs_num - 1)][j] = "";
                    }
                }
            }
        }
        songs_num--;
        system("CLS");
        goto menu;
    }
    else if (menu == "8") {
        goto start;
    }
    else if (menu == "9") {
        fstream output;
        output.open("playlist_songs.csv", ios::out);
        output << "songs" << "," << "artist" << endl;
        for (int i = 0; i < songs_num; i++) {
            for (int j = 0; j < 2; j++) {
                if (j == 0) {
                    output << list_song_artist[i][j];
                }
                else {
                    output << "," << list_song_artist[i][j] << endl;
                }
            }
        }
        system("CLS");
        cout << "Playlist Saved!" << endl;
        goto menu;
    }
    else {
        system("CLS");
        cout << "Thaks for use PARTY LOADER!" << endl;
    }
}