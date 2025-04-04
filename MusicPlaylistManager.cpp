#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Song {
    string title;
    string artist;
    Song* next;

    Song(const string& t, const string& a) {
        title = t;
        artist = a;
        next = nullptr;
    }

};

class Playlist {
private:
    Song* head;  
    Song* tail;  
    int size;    

public:
    Playlist(){
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    void addSong(const string& title, const string& artist) {
        Song* newSong = new Song(title, artist);
        if (!head) {
            head = tail = newSong;
        } else {
            tail->next = newSong;
            tail = newSong;
        }
        size++;
        cout << "Added song: " << title << " by " << artist << endl;
    }

    void deleteSong(const string& title) {
        if (!head) {
            cout << "The playlist is empty. No song to delete." << endl;
            return;
        }

        Song* current = head;
        Song* prev = nullptr;

        while (current) {
            if (current->title == title) {
                if (current == head) {
                    head = head->next;
                    if (!head) tail = nullptr; 
                } else {
                    prev->next = current->next;
                    if (current == tail) tail = prev; 
                }
                delete current;
                size--;
                cout << "Deleted song: " << title << endl;
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Song not found: " << title << endl;
    }

    void display() const {
        if (!head) {
            cout << "The playlist is empty." << endl;
            return;
        }

        Song* current = head;
        cout << "Playlist:" << endl;
        while (current) {
            cout << " - " << current->title << " by " << current->artist << endl;
            current = current->next;
        }
    }

    void shuffle() {
        if (!head || !head->next) {
            cout << "Not enough songs to shuffle." << endl;
            return;
        }

        vector<Song*> songList;
        Song* current = head;

        while (current) {
            songList.push_back(current);
            current = current->next;
        }

        srand(time(nullptr));
        for (int i = songList.size() - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(songList[i], songList[j]);
        }

        head = songList[0];
        current = head;

        for (size_t i = 1; i < songList.size(); i++) {
            current->next = songList[i];
            current = current->next;
        }
        current->next = nullptr;
        tail = current;

        cout << "Playlist shuffled." << endl;
    }

    ~Playlist() {
        while (head) {
            Song* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Playlist playlist;

    playlist.addSong("Blinding Lights", "The Weeknd");
    playlist.addSong("The Nights", "Avicii");
    playlist.addSong("Say Yes To Heaven", "Lana Del Rey");

    playlist.display();

    playlist.deleteSong("The Nights");
    playlist.display();

    playlist.shuffle();
    playlist.display();

    playlist.addSong("Shape of You", "Ed Sheeran");
    playlist.display();

    return 0;
}
